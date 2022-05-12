// Copyright (C) 2020-2022 Free Software Foundation, Inc.

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

#ifndef RUST_AST_RESOLVE_PATH_H
#define RUST_AST_RESOLVE_PATH_H

#include "rust-ast-resolve-base.h"

namespace Rust {
namespace Resolver {

class ResolvePath : public ResolverBase
{
  using Rust::Resolver::ResolverBase::visit;

public:
  static void go (AST::PathInExpression *expr, NodeId parent, NodeId self_id);
  static void go (AST::QualifiedPathInExpression *expr, NodeId parent,
		  NodeId self_id);
  static void go (AST::SimplePath *expr, NodeId parent, NodeId self_id);

private:
  ResolvePath (NodeId parent, NodeId self_id)
    : ResolverBase (parent), self_id (self_id)
  {}

  /**
   * Resolve the relative root(s) of a given path. This function takes care
   * of resolving the `self`, `crate` or `super` paths to proper NodeIds and
   * inserting them properly in the current scope.
   */
  // FIXME: Figure out the API so that we can resolve *multiple* roots: This is
  // important for `super::super::super...`
  // FIXME: Add more documentation
  void resolve_relative_root (const CanonicalPath &root, NodeId id,
			      Location locus);

  void resolve_path (AST::PathInExpression *expr);
  void resolve_path (AST::QualifiedPathInExpression *expr);
  void resolve_path (AST::SimplePath *expr);

  void resolve_segments (CanonicalPath prefix, size_t offs,
			 std::vector<AST::PathExprSegment> &segs,
			 NodeId expr_node_id, Location expr_locus);

  NodeId self_id;
};

class ResolveSimplePathSegmentToCanonicalPath
{
public:
  static CanonicalPath resolve (const AST::SimplePathSegment &seg)
  {
    // FIXME: Since this is so simple, maybe it can simply be a tiny function?
    return CanonicalPath::new_seg (seg.get_node_id (), seg.get_segment_name ());
  }
};

} // namespace Resolver
} // namespace Rust

#endif // !RUST_AST_RESOLVE_PATH_H
