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
#include "rust-hir-stmt.h"

namespace Rust {
namespace Resolver {
void
BorrowChecker::resolve (HIR::Crate &crate)
{
  for (auto &item : crate.items)
    {
      rust_debug ("[ARTHUR] %s", item->as_string ().c_str ());
      item->accept_vis (*this);
    }

  polonius.compute ();
}

void
BorrowChecker::visit (HIR::AssignmentExpr &assignment)
{}

void
BorrowChecker::visit (HIR::LetStmt &let)
{
  polonius.define_var (let, let.get_init_expr ());
}

void
BorrowChecker::visit (HIR::IdentifierExpr &expr)
{
  polonius.var_used_at (expr);
}

void
BorrowChecker::visit (HIR::BlockExpr &block)
{
  for (auto &stmt : block.get_statements ())
    stmt->accept_vis (*this);

  block.get_final_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::Function &function)
{
  function.get_definition ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ExprStmtWithoutBlock &expr)
{
  expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ExprStmtWithBlock &expr)
{
  expr.get_expr ()->accept_vis (*this);
}
} // namespace Resolver
} // namespace Rust
