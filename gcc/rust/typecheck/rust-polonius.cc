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
polonius_var_used_at (void *handle, size_t var_id, size_t expr_id);
extern "C" void
polonius_compute (void *handle);

namespace Rust {
namespace HIR {
Polonius::Polonius () { raw_handle = polonius_init (); }

Polonius::~Polonius () { polonius_deinit (raw_handle); }

void
Polonius::define_var (HIR::Stmt &assignment, HIR::Expr *expr)
{
  polonius_define_var (raw_handle, assignment.get_mappings ().get_hirid (),
		       expr->get_mappings ().get_hirid ());
}

void
Polonius::var_used_at (HIR::Expr &expr)
{
  auto resolver = Resolver::Resolver::get ();
  auto ref_node_id = UNKNOWN_NODEID;
  resolver->lookup_resolved_name (expr.get_mappings ().get_nodeid (),
				  &ref_node_id);

  polonius_var_used_at (raw_handle, expr.get_mappings ().get_hirid (),
			ref_node_id);
}

void
Polonius::compute ()
{
  polonius_compute (raw_handle);
}
} // namespace HIR
} // namespace Rust
