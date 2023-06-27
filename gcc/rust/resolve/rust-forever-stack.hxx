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
tl::expected<void, std::string>
ForeverStack<N>::Node::insert_child (Link link, Node child)
{
  auto res = children.insert ({link, child});

  if (!res.second)
    return tl::make_unexpected ("wrong");

  return {};
}

// FIXME: Add correct implementation
template <Namespace N>
void
ForeverStack<N>::push (Rib rib, NodeId id, tl::optional<Identifier> path)
{
  push_inner (rib, Link (id, path));

  // That's WRONG! (now it's good tho)
  // this would mean that pushing an anonymous scope, popping it and then
  // pushing it again would cause the same scope to be used cursor.children.find
  // so for this code:
  //
  // ```rust
  // fn f() {
  //   {
  //     let a = 15;
  //   }
  //   {
  //     foo (a); // would work!
  //   }
  // }
  // ```
  // so we need anonymous paths, or some path/NodId sum type as the link
  // TODO: Maybe we always have the NodeId, and keep an extra
  // optional<Identifier> for the path segment? when building the canonical
  // path, we'll error out if there's a "none" when we try and get the path
  // segment.
  // cursor.children.find ({} /* No path */);

  // Or like - one constructor which takes no path and is a default constructor
  // for "anonymous scopes" like blocks etc
  // and one which takes a path for Modules? The module's path?

  // if the rib already exists, just move the cursor to it
  // if rib in cursor.children () { cursor = rib; }

  // otherwise, create a new Node with this rib, a new "link" from the parent
  // one, and get going!
}

template <Namespace N>
void
ForeverStack<N>::push_inner (Rib rib, Link link)
{
  // If the link does not exist, we create it and emplace a new `Node` with the
  // current node as its parent. `unordered_map::emplace` returns a pair with
  // the iterator and a boolean. If the value already exists, the iterator
  // points to it. Otherwise, it points to the newly emplaced value, so we can
  // just update our cursor.
  auto emplace
    = cursor->children.emplace (std::make_pair (link, Node (rib, *cursor)));

  auto it = emplace.first;
  auto didnt_exist = emplace.second;

  rust_debug ("inserting link: Link(%d [%s]): existed? %s", link.id,
	      link.path.has_value () ? link.path.value ().c_str () : "<anon>",
	      didnt_exist ? "no" : "yes");

  cursor = &it->second;

  // Or like - one constructor which takes no path and is a default constructor
  // for "anonymous scopes" like blocks etc
  // and one which takes a path for Modules? The module's path?

  // if the rib already exists, just move the cursor to it
  // if rib in cursor.children () { cursor = rib; }

  // otherwise, create a new Node with this rib, a new "link" from the parent
  // one, and get going!
}

template <Namespace N>
void
ForeverStack<N>::pop ()
{
  assert (!cursor->is_root ());

  cursor = &cursor->parent.value ();
}

template <Namespace N>
tl::expected<void, std::string>
ForeverStack<N>::insert (Identifier name, NodeId node)
{
  auto &innermost_rib = peek ();

  return innermost_rib.insert (name, node);
}

template <Namespace N>
Rib &
ForeverStack<N>::peek ()
{
  return cursor->rib;
}

template <Namespace N>
const Rib &
ForeverStack<N>::peek () const
{
  return cursor->rib;
}

template <Namespace N>
void
ForeverStack<N>::reverse_iter () /* FIXME: Should take a lambda, right? */
{
  auto &tmp = *cursor;

  while (!tmp.is_root ())
    tmp = tmp.parent.value ();
}

template <Namespace N>
tl::optional<NodeId>
ForeverStack<N>::get (const Identifier &name)
{}

// TODO: Are there different fetching behavior for different namespaces?
// inline template <>
// tl::optional<NodeId>
// ForeverStack<Namespace::Values>::get (const Identifier &name)
// {
//   return {};
// }

static std::string
rib_str (const Rib &rib, const std::string &next, const std::string &next_next)
{
  if (rib.get_values ().empty ())
    {
      std::cerr << next << "rib: {},\n";
      return "";
    }

  std::cerr << next << "rib: {\n";

  for (const auto &kv : rib.get_values ())
    std::cerr << next_next << kv.first << ": " << kv.second << "\n";

  std::cerr << next << "},\n";

  return "";
}

template <Namespace N>
std::string
ForeverStack<N>::node_str (unsigned indentation,
			   const ForeverStack<N>::Node &node)
{
  auto indent = std::string (indentation, ' ');
  auto next = std::string (indentation + 4, ' ');
  auto next_next = std::string (indentation + 8, ' ');

  std::cerr << indent << "Node {\n"
	    << next << "is_root: " << (node.is_root () ? "true" : "false")
	    << ",\n"
	    << next << "is_leaf: " << (node.is_leaf () ? "true" : "false")
	    << ",\n";

  rib_str (node.rib, next, next_next);

  std::cerr << indent << "}\n";

  for (auto &kv : node.children)
    {
      auto link = kv.first;
      auto child = kv.second;
      std::cerr << indent << "Link (" << link.id << ", "
		<< (link.path.has_value () ? link.path.value () : "<anon>")
		<< "):\n";

      std::cerr << node_str (indentation + 4, child) << '\n';
    }

  return "";
}

template <Namespace N>
std::string
ForeverStack<N>::debug_str ()
{
  return node_str (0, root);
}

// FIXME: Can we add selftests?

} // namespace Resolver2_0
} // namespace Rust
