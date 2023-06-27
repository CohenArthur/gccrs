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

#ifndef RUST_FOREVER_STACK_H
#define RUST_FOREVER_STACK_H

#include "rust-system.h"
#include "rust-rib.h"
#include "rust-ast.h"
#include "rust-path.h"
#include "optional.h"
#include "expected.h"

namespace Rust {
namespace Resolver2_0 {

template <Namespace N> class ForeverStack
{
  // we then need to traverse the stack based on what we are looking for - if we
  // are looking for a type, a variable... and each rib we traverse indicates
  // certain rules to enforce. for example, if we traverse a Rib::Function, then
  // we cannot access generic types or simple variables (`let` variables)
  // defined in innermore rings

public:
  ForeverStack () : root (Node (Rib (Rib::Kind::Normal))), cursor (&root)
  {
    rust_assert (root.is_root ());
    rust_assert (root.is_leaf ());
  }

  // FIXME: Documentation
  void push (Rib rib, NodeId id, tl::optional<Identifier> path = {});

  void pop ();

  // FIXME: Not void and string
  /**
   * Insert a new definition in the innermost `Rib` in this map
   *
   * @param name FIXME
   * @param id FIXME
   *
   * @return FIXME
   *
   * @aborts if there are no `Rib`s inserted in the current map FIXME
   */
  tl::expected<void, std::string> insert (Identifier name, NodeId id);

  /* Access the innermost `Rib` in this map */
  Rib &peek ();
  const Rib &peek () const;

  /**
   * Reverse iter on all ribs from the innermost one to the outermost one,
   * trying to find a name. This is the default algorithm.
   * This function gets specialized based on the Rib::Kind
   * this way, we ensure a proper resolution algorithm at the type level
   *
   * @param name Name of the identifier to locate in this scope or an outermore
   * scope
   *
   * @return a valid option with the NodeId if the identifier is present in the
   * current map, an empty one otherwise.
   */
  inline tl::optional<NodeId> get (const Identifier &name);

  // FIXME: Should we dump to a file instead, like the other dumps?
  std::string debug_str ();

private:
  class Link
  {
  public:
    Link (NodeId id, tl::optional<Identifier> path) : id (id), path (path) {}

    bool compare (const Link &other) const
    {
      // FIXME: Do we need to do something with the path?
      // Can they be equal?
      return id < other.id;
    }

    NodeId id;
    tl::optional<Identifier> path;
  };

  class LinkCmp
  {
  public:
    bool operator() (const Link &lhs, const Link &rhs) const
    {
      return lhs.compare (rhs);
    }
  };

  // TODO: Rename? This would be a trie or other kind of tree
  // How do we make that data structure?
  // it's a tree, so each node can point to any number (n) nodes
  // these nodes are linked by a PathSegment (FIXME: Is that valid? What do we
  // want to use here?)
  // Each node is a NodeId
  // do we make it generic over the Segment type and Value type? to reuse it
  // easily?
  // Do we keep NodeIds as values or Ribs?
  class Node
  {
  public:
    Node (Rib rib) : rib (rib) {}
    Node (Rib rib, Node &parent) : rib (rib), parent (parent) {}

    bool is_root () const;
    bool is_leaf () const;

    // FIXME: Use proper error type
    tl::expected<void, std::string> insert_child (Link link, Node child);

    Rib rib; // this is the "value" of the node
    std::map<Link, Node /* FIXME: unique_ptr<Node>? */, LinkCmp> children;

    tl::optional<Node &> parent; // None only if root node
  };

  // TODO: Documentation
  void push_inner (Rib rib, Link link);

  /**
   * Reverse iterate on all Ribs from the current one, in an outwards fashion
   */
  void reverse_iter ();

  Node root;
  // this needs to go from a vector to a trie or tree
  // or simply a vector of hashmap at first, but urgh
  // std::vector<Rib> stack;
  Node *cursor; // mmmh... is that valid? How do we then get its parent?
		// do we do a doubly linked list as a node? - yes?

  // FIXME: Should we dump to a file instead, like the other dumps?
  std::string node_str (unsigned indentation, const Node &node);
};

} // namespace Resolver2_0
} // namespace Rust

#include "rust-forever-stack.hxx"

#endif // !RUST_FOREVER_STACK_H
