// Copyright (C) 2020-2024 Free Software Foundation, Inc.

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

#ifndef RUST_COMPILE_VAR_DECL
#define RUST_COMPILE_VAR_DECL

#include "rust-compile-base.h"
#include "rust-hir-visitor.h"

namespace Rust {
namespace Compile {

class CompilePatternVarDecl : public HIRCompileBase,
			      public HIR::HIRPatternVisitor
{
  using HIR::HIRPatternVisitor::visit;

public:
  static std::vector<Bvariable *> compile (tree fndecl, tree translated_type,
					   HIR::Pattern *pattern, Context *ctx);

  void visit (HIR::IdentifierPattern &pattern) override;
  void visit (HIR::TuplePattern &pattern) override;

  // Empty visit for unused Pattern HIR nodes.
  void visit (HIR::AltPattern &) override {}
  void visit (HIR::LiteralPattern &) override {}
  void visit (HIR::PathInExpression &) override {}
  void visit (HIR::QualifiedPathInExpression &) override {}
  void visit (HIR::RangePattern &) override {}
  void visit (HIR::ReferencePattern &) override {}
  void visit (HIR::SlicePattern &) override {}
  void visit (HIR::StructPattern &) override {}
  void visit (HIR::TupleStructPattern &) override {}
  void visit (HIR::WildcardPattern &) override {}

private:
  CompilePatternVarDecl (Context *ctx, tree fndecl, tree translated_type)
    : HIRCompileBase (ctx), fndecl (fndecl), translated_type (translated_type)
  {}

  tree fndecl;
  tree translated_type;

  std::vector<Bvariable *> vars;
};

} // namespace Compile
} // namespace Rust

#endif // RUST_COMPILE_VAR_DECL
