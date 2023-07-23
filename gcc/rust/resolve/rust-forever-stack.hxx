// Copyright (C) 2020-2023 Free Software Foundation, Inc.

// This file is part of GCC.

// GCC is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3, or (at your option) any later
// version.

// GCC is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License
// along with GCC; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include "expected.h"
#include "rust-ast.h"
#include "rust-diagnostics.h"
#include "rust-forever-stack.h"
#include "rust-rib.h"
#include "optional.h"

namespace Rust {
namespace Resolver2_0 {

template <Namespace N>
bool
ForeverStack<N>::Node::is_root () const
{
  return !parent.has_value ();
}

template <Namespace N>
bool
ForeverStack<N>::Node::is_leaf () const
{
  return children.empty ();
}

template <Namespace N>
void
ForeverStack<N>::Node::insert_child (Link link, Node child)
{
  auto res = children.insert ({link, child});

  // Do we want to error if the child already exists? Probably not, right?
  // That's kinda the point, isn't it. So this method always succeeds, right?
}

// FIXME: Add correct implementation
template <Namespace N>
void
ForeverStack<N>::push (Rib rib, NodeId id, tl::optional<Identifier> path)
{
  push_inner (rib, Link (id, path));
}

template <Namespace N>
void
ForeverStack<N>::push_inner (Rib rib, Link link)
{
  // If the link does not exist, we create it and emplace a new `Node` with the
  // current node as its parent. `unordered_map::emplace` returns a pair with
  // the iterator and a boolean. If the value already exists, the iterator
  // points to it. Otherwise, it points to the newly emplaced value, so we can
  // just update our cursor().
  auto emplace
    = cursor ().children.emplace (std::make_pair (link, Node (rib, cursor ())));

  auto it = emplace.first;
  auto existed = !emplace.second;

  rust_debug ("inserting link: Link(%d [%s]): existed? %s", link.id,
	      link.path.has_value () ? link.path.value ().as_string ().c_str ()
				     : "<anon>",
	      existed ? "yes" : "no");

  // We update the cursor
  update_cursor (it->second);
}

template <Namespace N>
void
ForeverStack<N>::pop ()
{
  assert (!cursor ().is_root ());

  rust_debug ("popping link");

  for (const auto &kv : cursor ().rib.get_values ())
    rust_debug ("current_rib: k: %s, v: %d", kv.first.c_str (), kv.second);

  if (cursor ().parent.has_value ())
    for (const auto &kv : cursor ().parent.value ().rib.get_values ())
      rust_debug ("new cursor: k: %s, v: %d", kv.first.c_str (), kv.second);

  update_cursor (cursor ().parent.value ());
}

static tl::expected<NodeId, DuplicateNameError>
insert_inner (Rib &rib, std::string name, NodeId node, bool can_shadow)
{
  return rib.insert (name, node, can_shadow);
}

template <Namespace N>
tl::expected<NodeId, DuplicateNameError>
ForeverStack<N>::insert (Identifier name, NodeId node)
{
  auto &innermost_rib = peek ();

  // So what do we do here - if the Rib has already been pushed in an earlier
  // pass, we might end up in a situation where it is okay to re-add new names.
  // Do we just ignore that here? Do we keep track of if the Rib is new or not?
  // should our cursor have info on the current node like "is it newly pushed"?
  return insert_inner (innermost_rib, name.as_string (), node, false);
}

// Specialization for Macros and Labels - where we are allowed to shadow
// existing definitions
template <>
inline tl::expected<NodeId, DuplicateNameError>
ForeverStack<Namespace::Macros>::insert (Identifier name, NodeId node)
{
  return insert_inner (peek (), name.as_string (), node, true);
}

template <>
inline tl::expected<NodeId, DuplicateNameError>
ForeverStack<Namespace::Labels>::insert (Identifier name, NodeId node)
{
  return insert_inner (peek (), name.as_string (), node, true);
}

template <Namespace N>
Rib &
ForeverStack<N>::peek ()
{
  return cursor ().rib;
}

template <Namespace N>
const Rib &
ForeverStack<N>::peek () const
{
  return cursor ().rib;
}

template <Namespace N>
void
ForeverStack<N>::reverse_iter (std::function<KeepGoing (Node &)> lambda)
{
  return reverse_iter (cursor (), lambda);
}

template <Namespace N>
void
ForeverStack<N>::reverse_iter (Node &start,
			       std::function<KeepGoing (Node &)> lambda)
{
  auto *tmp = &start;

  while (true)
    {
      auto keep_going = lambda (*tmp);
      if (keep_going == KeepGoing::No)
	return;

      if (tmp->is_root ())
	return;

      tmp = &tmp->parent.value ();
    }
}

template <Namespace N>
typename ForeverStack<N>::Node &
ForeverStack<N>::cursor ()
{
  return cursor_reference;
}

template <Namespace N>
const typename ForeverStack<N>::Node &
ForeverStack<N>::cursor () const
{
  return cursor_reference;
}

template <Namespace N>
void
ForeverStack<N>::update_cursor (Node &new_cursor)
{
  cursor_reference = new_cursor;
}

template <Namespace N>
tl::optional<NodeId>
ForeverStack<N>::get (const Identifier &name)
{
  return tl::nullopt;
}

template <>
inline tl::optional<NodeId>
ForeverStack<Namespace::Macros>::get (const Identifier &name)
{
  tl::optional<NodeId> resolved_node = tl::nullopt;

  // TODO: Can we improve the API? have `reverse_iter` return an optional?
  reverse_iter ([&resolved_node, &name] (Node &current) {
    auto candidate = current.rib.get (name.as_string ());

    return candidate.map_or (
      [&resolved_node] (NodeId found) {
	// macro resolving does not need to care about various ribs - they are
	// available from all contexts if defined in the current scope, or an
	// outermore one. so if we do have a candidate, we can return it
	// directly and stop iterating
	resolved_node = found;

	return KeepGoing::No;
      },
      // if there was no candidate, we keep iterating
      KeepGoing::Yes);
  });

  return resolved_node;
}

/* Check if an iterator points to the last element */
template <typename I, typename C>
static bool
is_last (const I &iterator, const C &collection)
{
  return iterator + 1 == collection.end ();
}

template <Namespace N>
typename ForeverStack<N>::Node &
ForeverStack<N>::find_closest_module (Node &starting_point)
{
  auto *closest_module = &starting_point;

  reverse_iter (starting_point, [&closest_module] (Node &current) {
    if (current.rib.kind == Rib::Kind::Module || current.is_root ())
      {
	closest_module = &current;
	return KeepGoing::No;
      }

    return KeepGoing::Yes;
  });

  return *closest_module;
}

template <Namespace N>
tl::optional<std::vector<AST::SimplePathSegment>::const_iterator>
ForeverStack<N>::find_starting_point (
  const std::vector<AST::SimplePathSegment> &segments, Node &starting_point)
{
  auto iterator = segments.begin ();

  // TODO: Similarly, if we just start looking from where we are, we might be
  // inside of a function with no modules defined we need to go back up to the
  // parent module. not sure how to do that properly.

  // let's clean this up first

  for (; !is_last (iterator, segments); iterator++)
    {
      auto seg = *iterator;

      if (seg.is_crate_path_seg ())
	{
	  starting_point = root;
	  iterator++;
	  break;
	}
      if (seg.is_lower_self ())
	{
	  // do nothing and exit
	  iterator++;
	  break;
	}
      if (seg.is_super_path_seg ())
	{
	  if (starting_point.is_root ())
	    {
	      rust_error_at (seg.get_locus (), ErrorCode ("E0433"),
			     "there are too many leading keywords and you're a "
			     "dumbass. count them. sigh");
	      return tl::nullopt;
	    }

	  // this line is invalid - we need to go up to the previous module, not
	  // just the previous scope
	  // TODO: How do we identify a module scope?
	  // Is it those modules which have links? Like if there is a link
	  // between parent and `starting_point`? is that valid or not really?
	  // should we have "module links"?
	  starting_point = find_closest_module (starting_point.parent.value ());
	  continue;
	}

      // now we've gone through the allowed `crate`, `self` or leading `super`
      // segments. we can start resolving each segment itself.
      // if we do see another leading segment, then we can error out.
      break;
    }

  return iterator;
}

template <Namespace N>
tl::optional<typename ForeverStack<N>::Node &>
ForeverStack<N>::resolve_segments (
  Node &starting_point, const std::vector<AST::SimplePathSegment> &segments,
  std::vector<AST::SimplePathSegment>::const_iterator iterator)
{
  auto *current_node = &starting_point;
  for (; !is_last (iterator, segments); iterator++)
    {
      auto &seg = *iterator;
      auto str = seg.as_string ();
      rust_debug ("[ARTHUR]: resolving segment part: %s", str.c_str ());

      if (seg.is_crate_path_seg () || seg.is_super_path_seg ()
	  || seg.is_lower_self ())
	{
	  rust_error_at (
	    seg.get_locus (), ErrorCode ("E0433"),
	    "leading keyword %qs can only be used at the beginning of a path",
	    str.c_str ());
	  return tl::nullopt;
	}

      tl::optional<typename ForeverStack<N>::Node &> child = tl::nullopt;

      rust_debug ("[ARTHUR] how many children: %lu",
		  current_node->children.size ());
      for (auto &kv : current_node->children)
	rust_debug ("[ARTHUR] child link: `%s`",
		    kv.first.path.has_value ()
		      ? kv.first.path.value ().as_string ().c_str ()
		      : "<anon>");

      for (auto &kv : current_node->children)
	{
	  auto &link = kv.first;

	  if (link.path.map_or (
		[&str] (Identifier path) {
		  auto &path_str = path.as_string ();
		  return str == path_str;
		},
		false))
	    {
	      child = kv.second;
	      break;
	    }
	}

      if (!child.has_value ())
	{
	  rust_error_at (seg.get_locus (), ErrorCode ("E0433"),
			 "failed to resolve path segment %qs", str.c_str ());
	  return tl::nullopt;
	}

      current_node = &child.value ();
    }

  return *current_node;
}

template <Namespace N>
tl::optional<NodeId>
ForeverStack<N>::resolve_path (const AST::SimplePath &path)
{
  // we first need to handle the "starting" segments - `super`, `self` or
  // `crate`. we don't need to do anything for `self` and can just skip it. for
  // `crate`, we need to go back to the root of the current stack. for each
  // `super` segment, we go back to the cursor's parent until we reach the
  // correct one or the root.
  auto starting_point = find_closest_module (cursor ());
  auto &segments = path.get_segments ();

  return find_starting_point (segments, starting_point)
    .and_then ([this, &segments, &starting_point] (auto iterator) {
      rust_debug_loc (iterator->get_locus (),
		      "[ARTHUR] starting point is now here: id");

      return resolve_segments (starting_point, segments, iterator);
    })
    .and_then ([&path] (Node node) {
      return node.rib.get (path.get_final_segment ().as_string ());
    });

  // TODO: Similarly, if we just start looking from where we are, we might be
  // inside of a function with no modules defined we need to go back up to the
  // parent module. not sure how to do that properly.

  // TODO: Can we go back up until we find a Rib::Module?
}

template <Namespace N>
void
ForeverStack<N>::stream_rib (std::stringstream &stream, const Rib &rib,
			     const std::string &next,
			     const std::string &next_next)
{
  if (rib.get_values ().empty ())
    {
      stream << next << "rib: {},\n";
      return;
    }

  stream << next << "rib: {\n";

  for (const auto &kv : rib.get_values ())
    stream << next_next << kv.first << ": " << kv.second << "\n";

  stream << next << "},\n";
}

template <Namespace N>
void
ForeverStack<N>::stream_node (std::stringstream &stream, unsigned indentation,
			      const ForeverStack<N>::Node &node)
{
  auto indent = std::string (indentation, ' ');
  auto next = std::string (indentation + 4, ' ');
  auto next_next = std::string (indentation + 8, ' ');

  stream << indent << "Node {\n"
	 << next << "is_root: " << (node.is_root () ? "true" : "false") << ",\n"
	 << next << "is_leaf: " << (node.is_leaf () ? "true" : "false")
	 << ",\n";

  stream_rib (stream, node.rib, next, next_next);

  stream << indent << "}\n";

  for (auto &kv : node.children)
    {
      auto link = kv.first;
      auto child = kv.second;
      stream << indent << "Link (" << link.id << ", "
	     << (link.path.has_value () ? link.path.value ().as_string ()
					: "<anon>")
	     << "):\n";

      stream_node (stream, indentation + 4, child);

      stream << '\n';
    }
}

template <Namespace N>
std::string
ForeverStack<N>::as_debug_string ()
{
  std::stringstream stream;

  stream_node (stream, 0, root);

  return stream.str ();
}

// FIXME: Can we add selftests?

} // namespace Resolver2_0
} // namespace Rust
