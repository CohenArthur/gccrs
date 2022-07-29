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

#include "rust-borrow-checker.h"
#include "rust-hir-stmt.h"

namespace Rust {
namespace Resolver {

BorrowChecker::BorrowChecker ()
  : polonius (Polonius ()), resolver (*Resolver::Resolver::get ())
{}

void
BorrowChecker::go (HIR::Crate &crate)
{
  for (auto &item : crate.items)
    item->accept_vis (*this);

  polonius.compute ();
}

void
BorrowChecker::visit (HIR::Lifetime &)
{}

void
BorrowChecker::visit (HIR::LifetimeParam &)
{}

void
BorrowChecker::visit (HIR::PathInExpression &)
{}

void
BorrowChecker::visit (HIR::TypePathSegment &)
{}

void
BorrowChecker::visit (HIR::TypePathSegmentGeneric &)
{}

void
BorrowChecker::visit (HIR::TypePathSegmentFunction &)
{}

void
BorrowChecker::visit (HIR::TypePath &)
{}

void
BorrowChecker::visit (HIR::QualifiedPathInExpression &)
{}

void
BorrowChecker::visit (HIR::QualifiedPathInType &)
{}

void
BorrowChecker::visit (HIR::LiteralExpr &)
{}

void
BorrowChecker::visit (HIR::BorrowExpr &)
{}

void
BorrowChecker::visit (HIR::DereferenceExpr &)
{}

void
BorrowChecker::visit (HIR::ErrorPropagationExpr &)
{}

void
BorrowChecker::visit (HIR::NegationExpr &)
{}

void
BorrowChecker::visit (HIR::ArithmeticOrLogicalExpr &)
{}

void
BorrowChecker::visit (HIR::ComparisonExpr &)
{}

void
BorrowChecker::visit (HIR::LazyBooleanExpr &)
{}

void
BorrowChecker::visit (HIR::TypeCastExpr &)
{}

void
BorrowChecker::visit (HIR::CompoundAssignmentExpr &)
{}

void
BorrowChecker::visit (HIR::GroupedExpr &)
{}

void
BorrowChecker::visit (HIR::ArrayElemsValues &)
{}

void
BorrowChecker::visit (HIR::ArrayElemsCopied &)
{}

void
BorrowChecker::visit (HIR::ArrayExpr &)
{}

void
BorrowChecker::visit (HIR::ArrayIndexExpr &)
{}

void
BorrowChecker::visit (HIR::TupleExpr &)
{}

void
BorrowChecker::visit (HIR::TupleIndexExpr &)
{}

void
BorrowChecker::visit (HIR::StructExprStruct &)
{}

void
BorrowChecker::visit (HIR::StructExprFieldIdentifier &)
{}

void
BorrowChecker::visit (HIR::StructExprFieldIdentifierValue &)
{}

void
BorrowChecker::visit (HIR::StructExprFieldIndexValue &)
{}

void
BorrowChecker::visit (HIR::StructExprStructFields &)
{}

void
BorrowChecker::visit (HIR::StructExprStructBase &)
{}

void
BorrowChecker::visit (HIR::CallExpr &)
{}

void
BorrowChecker::visit (HIR::MethodCallExpr &)
{}

void
BorrowChecker::visit (HIR::FieldAccessExpr &)
{}

void
BorrowChecker::visit (HIR::ClosureExprInner &)
{}

void
BorrowChecker::visit (HIR::ClosureExprInnerTyped &)
{}

void
BorrowChecker::visit (HIR::ContinueExpr &)
{}

void
BorrowChecker::visit (HIR::BreakExpr &)
{}

void
BorrowChecker::visit (HIR::RangeFromToExpr &)
{}

void
BorrowChecker::visit (HIR::RangeFromExpr &)
{}

void
BorrowChecker::visit (HIR::RangeToExpr &)
{}

void
BorrowChecker::visit (HIR::RangeFullExpr &)
{}

void
BorrowChecker::visit (HIR::RangeFromToInclExpr &)
{}

void
BorrowChecker::visit (HIR::RangeToInclExpr &)
{}

void
BorrowChecker::visit (HIR::ReturnExpr &)
{}

void
BorrowChecker::visit (HIR::UnsafeBlockExpr &)
{}

void
BorrowChecker::visit (HIR::LoopExpr &)
{}

void
BorrowChecker::visit (HIR::WhileLoopExpr &)
{}

void
BorrowChecker::visit (HIR::WhileLetLoopExpr &)
{}

void
BorrowChecker::visit (HIR::ForLoopExpr &)
{}

void
BorrowChecker::visit (HIR::IfExpr &)
{}

void
BorrowChecker::visit (HIR::IfExprConseqElse &)
{}

void
BorrowChecker::visit (HIR::IfExprConseqIf &)
{}

void
BorrowChecker::visit (HIR::IfExprConseqIfLet &)
{}

void
BorrowChecker::visit (HIR::IfLetExpr &)
{}

void
BorrowChecker::visit (HIR::IfLetExprConseqElse &)
{}

void
BorrowChecker::visit (HIR::IfLetExprConseqIf &)
{}

void
BorrowChecker::visit (HIR::IfLetExprConseqIfLet &)
{}

void
BorrowChecker::visit (HIR::MatchExpr &)
{}

void
BorrowChecker::visit (HIR::AwaitExpr &)
{}

void
BorrowChecker::visit (HIR::AsyncBlockExpr &)
{}

void
BorrowChecker::visit (HIR::TypeParam &)
{}

void
BorrowChecker::visit (HIR::ConstGenericParam &param)
{}

void
BorrowChecker::visit (HIR::LifetimeWhereClauseItem &)
{}

void
BorrowChecker::visit (HIR::TypeBoundWhereClauseItem &)
{}

void
BorrowChecker::visit (HIR::Module &)
{}

void
BorrowChecker::visit (HIR::ExternCrate &)
{}

void
BorrowChecker::visit (HIR::UseTreeGlob &)
{}

void
BorrowChecker::visit (HIR::UseTreeList &)
{}

void
BorrowChecker::visit (HIR::UseTreeRebind &)
{}

void
BorrowChecker::visit (HIR::UseDeclaration &)
{}

void
BorrowChecker::visit (HIR::TypeAlias &)
{}

void
BorrowChecker::visit (HIR::StructStruct &)
{}

void
BorrowChecker::visit (HIR::TupleStruct &)
{}

void
BorrowChecker::visit (HIR::EnumItem &)
{}

void
BorrowChecker::visit (HIR::EnumItemTuple &)
{}

void
BorrowChecker::visit (HIR::EnumItemStruct &)
{}

void
BorrowChecker::visit (HIR::EnumItemDiscriminant &)
{}

void
BorrowChecker::visit (HIR::Enum &)
{}

void
BorrowChecker::visit (HIR::Union &)
{}

void
BorrowChecker::visit (HIR::ConstantItem &)
{}

void
BorrowChecker::visit (HIR::StaticItem &)
{}

void
BorrowChecker::visit (HIR::TraitItemFunc &)
{}

void
BorrowChecker::visit (HIR::TraitItemConst &)
{}

void
BorrowChecker::visit (HIR::TraitItemType &)
{}

void
BorrowChecker::visit (HIR::Trait &)
{}

void
BorrowChecker::visit (HIR::ImplBlock &)
{}

void
BorrowChecker::visit (HIR::ExternalStaticItem &)
{}

void
BorrowChecker::visit (HIR::ExternalFunctionItem &)
{}

void
BorrowChecker::visit (HIR::ExternBlock &)
{}

void
BorrowChecker::visit (HIR::LiteralPattern &)
{}

void
BorrowChecker::visit (HIR::IdentifierPattern &)
{}

void
BorrowChecker::visit (HIR::WildcardPattern &)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundLiteral &)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundPath &)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundQualPath &)
{}

void
BorrowChecker::visit (HIR::RangePattern &)
{}

void
BorrowChecker::visit (HIR::ReferencePattern &)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldTuplePat &)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldIdentPat &)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldIdent &)
{}

void
BorrowChecker::visit (HIR::StructPattern &)
{}

void
BorrowChecker::visit (HIR::TupleStructItemsNoRange &)
{}

void
BorrowChecker::visit (HIR::TupleStructItemsRange &)
{}

void
BorrowChecker::visit (HIR::TupleStructPattern &)
{}

void
BorrowChecker::visit (HIR::TuplePatternItemsMultiple &)
{}

void
BorrowChecker::visit (HIR::TuplePatternItemsRanged &)
{}

void
BorrowChecker::visit (HIR::TuplePattern &)
{}

void
BorrowChecker::visit (HIR::GroupedPattern &)
{}

void
BorrowChecker::visit (HIR::SlicePattern &)
{}

void
BorrowChecker::visit (HIR::EmptyStmt &)
{}

void
BorrowChecker::visit (HIR::TraitBound &)
{}

void
BorrowChecker::visit (HIR::ImplTraitType &)
{}

void
BorrowChecker::visit (HIR::TraitObjectType &)
{}

void
BorrowChecker::visit (HIR::ParenthesisedType &)
{}

void
BorrowChecker::visit (HIR::ImplTraitTypeOneBound &)
{}

void
BorrowChecker::visit (HIR::TupleType &)
{}

void
BorrowChecker::visit (HIR::NeverType &)
{}

void
BorrowChecker::visit (HIR::RawPointerType &)
{}

void
BorrowChecker::visit (HIR::ReferenceType &)
{}

void
BorrowChecker::visit (HIR::ArrayType &)
{}

void
BorrowChecker::visit (HIR::SliceType &)
{}

void
BorrowChecker::visit (HIR::InferredType &)
{}

void
BorrowChecker::visit (HIR::BareFunctionType &)
{}

void
BorrowChecker::visit (HIR::AssignmentExpr &expr)
{}

void
BorrowChecker::visit (HIR::LetStmt &let)
{
  polonius.define_var ();
}

void
BorrowChecker::visit (HIR::BlockExpr &block)
{}

void
BorrowChecker::visit (HIR::Function &function)
{}

void
BorrowChecker::visit (HIR::IdentifierExpr &expr)
{}

void
BorrowChecker::visit (HIR::ExprStmtWithoutBlock &expr)
{}

void
BorrowChecker::visit (HIR::ExprStmtWithBlock &expr)
{}

} // namespace Resolver
} // namespace Rust
