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

#include "rust-polonius.h"
#include "rust-name-resolver.h"

// Raw declarations from the rust compatibility layer
extern "C" void *
polonius_init (void);
extern "C" void
polonius_deinit (void *handle);
extern "C" void
polonius_define_var (void *handle, size_t var_id, size_t expr_id);
extern "C" void
polonius_var_used_at (void *handle, size_t var_id, size_t point_id);
extern "C" void
polonius_compute (void *handle);

namespace Rust {
namespace HIR {
Polonius::Polonius ()
{
  raw_handle = polonius_init ();
  resolver = Rust::Resolver::Resolver::get ();
}

Polonius::~Polonius () { polonius_deinit (raw_handle); }

void
Polonius::define_var (HIR::Stmt &assignment, HIR::Expr *expr)
{
  auto var_node_id = UNKNOWN_NODEID;
  auto expr_node_id = UNKNOWN_NODEID;

  resolver->lookup_resolved_name (assignment.get_mappings ().get_nodeid (),
				  &var_node_id);
  resolver->lookup_resolved_name (expr->get_mappings ().get_nodeid (),
				  &var_node_id);

  // polonius_define_var (raw_handle, var_node_id, expr_node_id);
  polonius_define_var (raw_handle, assignment.get_mappings ().get_nodeid (),
		       expr->get_mappings ().get_nodeid ());
}

void
Polonius::var_used_at (HIR::Expr &expr)
{
  //  Resolver::CanonicalPath path;
  //  resolver->lookup_canonical_path(expr.get_mappings().get_nodeid(), &path);
  //
  //  auto ref_node_id = UNKNOWN_NODEID;
  //  resolver->lookup_resolved_name (expr.get_mappings ().get_nodeid (),
  //				  &ref_node_id);
  //
  //  auto resolved_node = UNKNOWN_NODEID;
  //
  //  resolver->get_name_scope ().lookup (
  //    Resolver::CanonicalPath::new_seg (expr.get_mappings ().get_nodeid (),
  //				      expr.as_string ()),
  //    &resolved_node);
  //
  //  rust_debug ("[ARTHUR] Used at %d", resolved_node);
  //
  //  polonius_var_used_at (raw_handle, expr.get_mappings ().get_hirid (),
  //			ref_node_id);

  auto ast_node_id = expr.get_mappings ().get_nodeid ();

  // then lookup the reference_node_id
  auto ref_node_id = UNKNOWN_NODEID;
  if (resolver->lookup_resolved_name (ast_node_id, &ref_node_id))
    {
      // these ref_node_ids will resolve to a pattern declaration but we are
      // interested in the definition that this refers to get the parent id
      Resolver::Definition def;
      if (!resolver->lookup_definition (ref_node_id, &def))
	{
	  // FIXME
	  // this is an internal error
	  rust_error_at (expr.get_locus (),
			 "unknown reference for resolved name");
	  return;
	}
      ref_node_id = def.parent;
    }

  rust_debug ("[ARTHUR] var %d used at %d", ref_node_id, ast_node_id);

  polonius_var_used_at (raw_handle, ref_node_id, ast_node_id);
}

void
Polonius::compute ()
{
  polonius_compute (raw_handle);
}
} // namespace HIR
} // namespace Rust
