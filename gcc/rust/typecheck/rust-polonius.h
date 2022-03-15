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

#include "rust-hir-expr.h"
#include "rust-hir-item.h"
#include "rust-name-resolver.h"

namespace Rust {
namespace HIR {
class Polonius
{
public:
  Polonius ();
  ~Polonius ();

  /**
   * Define a new variable to the polonius engine
   *
   * @param var Variable to define
   * @param init Initialization point
   */
  void define_var (HIR::Stmt &assignment, HIR::Expr *init);

  /**
   * Define a use-site for an existing variable
   */
  void var_used_at (HIR::Expr &expr);

  /**
   * Compute polonius results using the handle
   */
  void compute ();

private:
  void *raw_handle;
  Rust::Resolver::Resolver *resolver;
};
} // namespace HIR
} // namespace Rust
