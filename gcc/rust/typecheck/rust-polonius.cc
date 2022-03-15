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

// Raw declarations from the rust compatibility layer
extern "C" void *
polonius_init (void);
extern "C" void
polonius_deinit (void *handle);
extern "C" void
polonius_define_var (void *handle, size_t var_id, size_t expr_id);

namespace Rust {
namespace HIR {
Polonius::Polonius () { raw_handle = polonius_init (); }

Polonius::~Polonius () { polonius_deinit (raw_handle); }

void
Polonius::define_var (HIR::Expr &assignment, HIR::Expr &expr)
{
  polonius_define_var (raw_handle, assignment.get_mappings ().get_hirid (),
		       expr.get_mappings ().get_hirid ());
}
} // namespace HIR
} // namespace Rust
