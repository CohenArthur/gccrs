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

#include "rust-hir-borrow-checker.h"

namespace Rust {
namespace Resolver {
void
BorrowChecker::resolve (HIR::Crate &crate)
{
  for (auto &item : crate.items)
    item->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::AssignmentExpr &assignment)
{
  polonius.define_var (assignment, assignment.get_expr ());
}
} // namespace Resolver
} // namespace Rust
