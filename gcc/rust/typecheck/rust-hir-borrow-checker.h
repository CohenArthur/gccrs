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

#ifndef RUST_HIR_BORROW_CHECK_H
#define RUST_HIR_BORROW_CHECK_H

#include "rust-hir-visitor.h"
#include "rust-hir.h"
#include "rust-polonius.h"

namespace Rust {
namespace Resolver {
class BorrowChecker : public HIR::HIRFullVisitor
{
public:
  BorrowChecker () : polonius (HIR::Polonius ()){};

  /**
   * Perform borrow-checking using polonius on an entire crate
   */
  void resolve (HIR::Crate &crate);

  void visit (HIR::Lifetime &) override {}
  void visit (HIR::LifetimeParam &) override {}
  void visit (HIR::PathInExpression &) override {}
  void visit (HIR::TypePathSegment &) override {}
  void visit (HIR::TypePathSegmentGeneric &) override {}
  void visit (HIR::TypePathSegmentFunction &) override {}
  void visit (HIR::TypePath &) override {}
  void visit (HIR::QualifiedPathInExpression &) override {}
  void visit (HIR::QualifiedPathInType &) override {}
  void visit (HIR::LiteralExpr &) override {}
  void visit (HIR::BorrowExpr &) override {}
  void visit (HIR::DereferenceExpr &) override {}
  void visit (HIR::ErrorPropagationExpr &) override {}
  void visit (HIR::NegationExpr &) override {}
  void visit (HIR::ArithmeticOrLogicalExpr &) override {}
  void visit (HIR::ComparisonExpr &) override {}
  void visit (HIR::LazyBooleanExpr &) override {}
  void visit (HIR::TypeCastExpr &) override {}
  void visit (HIR::CompoundAssignmentExpr &) override {}
  void visit (HIR::GroupedExpr &) override {}
  void visit (HIR::ArrayElemsValues &) override {}
  void visit (HIR::ArrayElemsCopied &) override {}
  void visit (HIR::ArrayExpr &) override {}
  void visit (HIR::ArrayIndexExpr &) override {}
  void visit (HIR::TupleExpr &) override {}
  void visit (HIR::TupleIndexExpr &) override {}
  void visit (HIR::StructExprStruct &) override {}
  void visit (HIR::StructExprFieldIdentifier &) override {}
  void visit (HIR::StructExprFieldIdentifierValue &) override {}
  void visit (HIR::StructExprFieldIndexValue &) override {}
  void visit (HIR::StructExprStructFields &) override {}
  void visit (HIR::StructExprStructBase &) override {}
  void visit (HIR::CallExpr &) override {}
  void visit (HIR::MethodCallExpr &) override {}
  void visit (HIR::FieldAccessExpr &) override {}
  void visit (HIR::ClosureExprInner &) override {}
  void visit (HIR::ClosureExprInnerTyped &) override {}
  void visit (HIR::ContinueExpr &) override {}
  void visit (HIR::BreakExpr &) override {}
  void visit (HIR::RangeFromToExpr &) override {}
  void visit (HIR::RangeFromExpr &) override {}
  void visit (HIR::RangeToExpr &) override {}
  void visit (HIR::RangeFullExpr &) override {}
  void visit (HIR::RangeFromToInclExpr &) override {}
  void visit (HIR::RangeToInclExpr &) override {}
  void visit (HIR::ReturnExpr &) override {}
  void visit (HIR::UnsafeBlockExpr &) override {}
  void visit (HIR::LoopExpr &) override {}
  void visit (HIR::WhileLoopExpr &) override {}
  void visit (HIR::WhileLetLoopExpr &) override {}
  void visit (HIR::ForLoopExpr &) override {}
  void visit (HIR::IfExpr &) override {}
  void visit (HIR::IfExprConseqElse &) override {}
  void visit (HIR::IfExprConseqIf &) override {}
  void visit (HIR::IfExprConseqIfLet &) override {}
  void visit (HIR::IfLetExpr &) override {}
  void visit (HIR::IfLetExprConseqElse &) override {}
  void visit (HIR::IfLetExprConseqIf &) override {}
  void visit (HIR::IfLetExprConseqIfLet &) override {}
  void visit (HIR::MatchExpr &) override {}
  void visit (HIR::AwaitExpr &) override {}
  void visit (HIR::AsyncBlockExpr &) override {}
  void visit (HIR::TypeParam &) override {}
  void visit (HIR::LifetimeWhereClauseItem &) override {}
  void visit (HIR::TypeBoundWhereClauseItem &) override {}
  void visit (HIR::Module &) override {}
  void visit (HIR::ExternCrate &) override {}
  void visit (HIR::UseTreeGlob &) override {}
  void visit (HIR::UseTreeList &) override {}
  void visit (HIR::UseTreeRebind &) override {}
  void visit (HIR::UseDeclaration &) override {}
  void visit (HIR::TypeAlias &) override {}
  void visit (HIR::StructStruct &) override {}
  void visit (HIR::TupleStruct &) override {}
  void visit (HIR::EnumItem &) override {}
  void visit (HIR::EnumItemTuple &) override {}
  void visit (HIR::EnumItemStruct &) override {}
  void visit (HIR::EnumItemDiscriminant &) override {}
  void visit (HIR::Enum &) override {}
  void visit (HIR::Union &) override {}
  void visit (HIR::ConstantItem &) override {}
  void visit (HIR::StaticItem &) override {}
  void visit (HIR::TraitItemFunc &) override {}
  void visit (HIR::TraitItemConst &) override {}
  void visit (HIR::TraitItemType &) override {}
  void visit (HIR::Trait &) override {}
  void visit (HIR::ImplBlock &) override {}
  void visit (HIR::ExternalStaticItem &) override {}
  void visit (HIR::ExternalFunctionItem &) override {}
  void visit (HIR::ExternBlock &) override {}
  void visit (HIR::LiteralPattern &) override {}
  void visit (HIR::IdentifierPattern &) override {}
  void visit (HIR::WildcardPattern &) override {}
  void visit (HIR::RangePatternBoundLiteral &) override {}
  void visit (HIR::RangePatternBoundPath &) override {}
  void visit (HIR::RangePatternBoundQualPath &) override {}
  void visit (HIR::RangePattern &) override {}
  void visit (HIR::ReferencePattern &) override {}
  void visit (HIR::StructPatternFieldTuplePat &) override {}
  void visit (HIR::StructPatternFieldIdentPat &) override {}
  void visit (HIR::StructPatternFieldIdent &) override {}
  void visit (HIR::StructPattern &) override {}
  void visit (HIR::TupleStructItemsNoRange &) override {}
  void visit (HIR::TupleStructItemsRange &) override {}
  void visit (HIR::TupleStructPattern &) override {}
  void visit (HIR::TuplePatternItemsMultiple &) override {}
  void visit (HIR::TuplePatternItemsRanged &) override {}
  void visit (HIR::TuplePattern &) override {}
  void visit (HIR::GroupedPattern &) override {}
  void visit (HIR::SlicePattern &) override {}
  void visit (HIR::EmptyStmt &) override {}
  void visit (HIR::TraitBound &) override {}
  void visit (HIR::ImplTraitType &) override {}
  void visit (HIR::TraitObjectType &) override {}
  void visit (HIR::ParenthesisedType &) override {}
  void visit (HIR::ImplTraitTypeOneBound &) override {}
  void visit (HIR::TupleType &) override {}
  void visit (HIR::NeverType &) override {}
  void visit (HIR::RawPointerType &) override {}
  void visit (HIR::ReferenceType &) override {}
  void visit (HIR::ArrayType &) override {}
  void visit (HIR::SliceType &) override {}
  void visit (HIR::InferredType &) override {}
  void visit (HIR::BareFunctionType &) override {}

  void visit (HIR::AssignmentExpr &expr) override;
  void visit (HIR::LetStmt &let) override;
  void visit (HIR::BlockExpr &block) override;
  void visit (HIR::Function &function) override;
  void visit (HIR::IdentifierExpr &expr) override;
  void visit (HIR::ExprStmtWithoutBlock &expr) override;
  void visit (HIR::ExprStmtWithBlock &expr) override;

private:
  HIR::Polonius polonius;
};
} // namespace Resolver
} // namespace Rust

#endif // !RUST_HIR_BORROW_CHECK_H
