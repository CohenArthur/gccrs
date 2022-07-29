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
BorrowChecker::go (HIR::Crate &crate)
{
  for (auto &item : crate.items)
    item->accept_vis (*this);

  polonius.compute ();
}

void
visit (HIR::Lifetime &)
{}

void
visit (HIR::LifetimeParam &)
{}

void
visit (HIR::PathInExpression &)
{}

void
visit (HIR::TypePathSegment &)
{}

void
visit (HIR::TypePathSegmentGeneric &)
{}

void
visit (HIR::TypePathSegmentFunction &)
{}

void
visit (HIR::TypePath &)
{}

void
visit (HIR::QualifiedPathInExpression &)
{}

void
visit (HIR::QualifiedPathInType &)
{}

void
visit (HIR::LiteralExpr &)
{}

void
visit (HIR::BorrowExpr &)
{}

void
visit (HIR::DereferenceExpr &)
{}

void
visit (HIR::ErrorPropagationExpr &)
{}

void
visit (HIR::NegationExpr &)
{}

void
visit (HIR::ArithmeticOrLogicalExpr &)
{}

void
visit (HIR::ComparisonExpr &)
{}

void
visit (HIR::LazyBooleanExpr &)
{}

void
visit (HIR::TypeCastExpr &)
{}

void
visit (HIR::CompoundAssignmentExpr &)
{}

void
visit (HIR::GroupedExpr &)
{}

void
visit (HIR::ArrayElemsValues &)
{}

void
visit (HIR::ArrayElemsCopied &)
{}

void
visit (HIR::ArrayExpr &)
{}

void
visit (HIR::ArrayIndexExpr &)
{}

void
visit (HIR::TupleExpr &)
{}

void
visit (HIR::TupleIndexExpr &)
{}

void
visit (HIR::StructExprStruct &)
{}

void
visit (HIR::StructExprFieldIdentifier &)
{}

void
visit (HIR::StructExprFieldIdentifierValue &)
{}

void
visit (HIR::StructExprFieldIndexValue &)
{}

void
visit (HIR::StructExprStructFields &)
{}

void
visit (HIR::StructExprStructBase &)
{}

void
visit (HIR::CallExpr &)
{}

void
visit (HIR::MethodCallExpr &)
{}

void
visit (HIR::FieldAccessExpr &)
{}

void
visit (HIR::ClosureExprInner &)
{}

void
visit (HIR::ClosureExprInnerTyped &)
{}

void
visit (HIR::ContinueExpr &)
{}

void
visit (HIR::BreakExpr &)
{}

void
visit (HIR::RangeFromToExpr &)
{}

void
visit (HIR::RangeFromExpr &)
{}

void
visit (HIR::RangeToExpr &)
{}

void
visit (HIR::RangeFullExpr &)
{}

void
visit (HIR::RangeFromToInclExpr &)
{}

void
visit (HIR::RangeToInclExpr &)
{}

void
visit (HIR::ReturnExpr &)
{}

void
visit (HIR::UnsafeBlockExpr &)
{}

void
visit (HIR::LoopExpr &)
{}

void
visit (HIR::WhileLoopExpr &)
{}

void
visit (HIR::WhileLetLoopExpr &)
{}

void
visit (HIR::ForLoopExpr &)
{}

void
visit (HIR::IfExpr &)
{}

void
visit (HIR::IfExprConseqElse &)
{}

void
visit (HIR::IfExprConseqIf &)
{}

void
visit (HIR::IfExprConseqIfLet &)
{}

void
visit (HIR::IfLetExpr &)
{}

void
visit (HIR::IfLetExprConseqElse &)
{}

void
visit (HIR::IfLetExprConseqIf &)
{}

void
visit (HIR::IfLetExprConseqIfLet &)
{}

void
visit (HIR::MatchExpr &)
{}

void
visit (HIR::AwaitExpr &)
{}

void
visit (HIR::AsyncBlockExpr &)
{}

void
visit (HIR::TypeParam &)
{}

void
visit (HIR::LifetimeWhereClauseItem &)
{}

void
visit (HIR::TypeBoundWhereClauseItem &)
{}

void
visit (HIR::Module &)
{}

void
visit (HIR::ExternCrate &)
{}

void
visit (HIR::UseTreeGlob &)
{}

void
visit (HIR::UseTreeList &)
{}

void
visit (HIR::UseTreeRebind &)
{}

void
visit (HIR::UseDeclaration &)
{}

void
visit (HIR::TypeAlias &)
{}

void
visit (HIR::StructStruct &)
{}

void
visit (HIR::TupleStruct &)
{}

void
visit (HIR::EnumItem &)
{}

void
visit (HIR::EnumItemTuple &)
{}

void
visit (HIR::EnumItemStruct &)
{}

void
visit (HIR::EnumItemDiscriminant &)
{}

void
visit (HIR::Enum &)
{}

void
visit (HIR::Union &)
{}

void
visit (HIR::ConstantItem &)
{}

void
visit (HIR::StaticItem &)
{}

void
visit (HIR::TraitItemFunc &)
{}

void
visit (HIR::TraitItemConst &)
{}

void
visit (HIR::TraitItemType &)
{}

void
visit (HIR::Trait &)
{}

void
visit (HIR::ImplBlock &)
{}

void
visit (HIR::ExternalStaticItem &)
{}

void
visit (HIR::ExternalFunctionItem &)
{}

void
visit (HIR::ExternBlock &)
{}

void
visit (HIR::LiteralPattern &)
{}

void
visit (HIR::IdentifierPattern &)
{}

void
visit (HIR::WildcardPattern &)
{}

void
visit (HIR::RangePatternBoundLiteral &)
{}

void
visit (HIR::RangePatternBoundPath &)
{}

void
visit (HIR::RangePatternBoundQualPath &)
{}

void
visit (HIR::RangePattern &)
{}

void
visit (HIR::ReferencePattern &)
{}

void
visit (HIR::StructPatternFieldTuplePat &)
{}

void
visit (HIR::StructPatternFieldIdentPat &)
{}

void
visit (HIR::StructPatternFieldIdent &)
{}

void
visit (HIR::StructPattern &)
{}

void
visit (HIR::TupleStructItemsNoRange &)
{}

void
visit (HIR::TupleStructItemsRange &)
{}

void
visit (HIR::TupleStructPattern &)
{}

void
visit (HIR::TuplePatternItemsMultiple &)
{}

void
visit (HIR::TuplePatternItemsRanged &)
{}

void
visit (HIR::TuplePattern &)
{}

void
visit (HIR::GroupedPattern &)
{}

void
visit (HIR::SlicePattern &)
{}

void
visit (HIR::EmptyStmt &)
{}

void
visit (HIR::TraitBound &)
{}

void
visit (HIR::ImplTraitType &)
{}

void
visit (HIR::TraitObjectType &)
{}

void
visit (HIR::ParenthesisedType &)
{}

void
visit (HIR::ImplTraitTypeOneBound &)
{}

void
visit (HIR::TupleType &)
{}

void
visit (HIR::NeverType &)
{}

void
visit (HIR::RawPointerType &)
{}

void
visit (HIR::ReferenceType &)
{}

void
visit (HIR::ArrayType &)
{}

void
visit (HIR::SliceType &)
{}

void
visit (HIR::InferredType &)
{}

void
visit (HIR::BareFunctionType &)
{}

void
visit (HIR::AssignmentExpr &expr)
{}

void
visit (HIR::LetStmt &let)
{}

void
visit (HIR::BlockExpr &block)
{}

void
visit (HIR::Function &function)
{}

void
visit (HIR::IdentifierExpr &expr)
{}

void
visit (HIR::ExprStmtWithoutBlock &expr)
{}

void
visit (HIR::ExprStmtWithBlock &expr)
{}

} // namespace Resolver
} // namespace Rust
