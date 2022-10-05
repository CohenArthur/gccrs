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
#include "rust-name-resolver.h"
#include "rust-hir-map.h"

namespace Rust {
namespace Resolver {
class BorrowChecker : public HIR::HIRFullVisitor
{
public:
  BorrowChecker ();

  /**
   * Perform borrow-checking using polonius on an entire crate
   */
  void go (HIR::Crate &crate);

private:
  /**
   * The current "point" where we are borrow-checking. This can be considered
   * the "statement" or "parent" at which an instruction to polonius might
   * occur.
   *
   * For example, when resolving usages of a variable in blocks like so:
   *
   * ```
   * let x = 15;
   *
   * {
   *     foo();
   *     bar();
   *
   *     let y = x + 15;
   *
   *     15
   * }
   * ```
   *
   * We want the current point to point to the last statement of the block,
   * before the final expression.
   *
   * Use `set_current_point` to set it in a generic and easy way
   */
  HirId current_point;

  /**
   * Set the current point for any node which contains mappings. This simply
   * avoids typing the long `.get_mappings().get_hirid()` all the time
   */
  template <typename T> void set_current_point (const T &node)
  {
    current_point = node.get_mappings ().get_hirid ();
  }

  /**
   * Same as `set_current_point`, but specified/overloaded for smart pointers
   */
  template <typename T> void set_current_point (const std::unique_ptr<T> &node)
  {
    current_point = node->get_mappings ().get_hirid ();
  }

  Polonius polonius;
  Rust::Resolver::Resolver &resolver;
  Analysis::Mappings &mappings;

  virtual void visit (HIR::Lifetime &lifetime) override;
  virtual void visit (HIR::LifetimeParam &lifetime_param) override;
  virtual void visit (HIR::PathInExpression &path) override;
  virtual void visit (HIR::TypePathSegment &segment) override;
  virtual void visit (HIR::TypePathSegmentGeneric &segment) override;
  virtual void visit (HIR::TypePathSegmentFunction &segment) override;
  virtual void visit (HIR::TypePath &path) override;
  virtual void visit (HIR::QualifiedPathInExpression &path) override;
  virtual void visit (HIR::QualifiedPathInType &path) override;
  virtual void visit (HIR::LiteralExpr &expr) override;
  virtual void visit (HIR::BorrowExpr &expr) override;
  virtual void visit (HIR::DereferenceExpr &expr) override;
  virtual void visit (HIR::ErrorPropagationExpr &expr) override;
  virtual void visit (HIR::NegationExpr &expr) override;
  virtual void visit (HIR::ArithmeticOrLogicalExpr &expr) override;
  virtual void visit (HIR::ComparisonExpr &expr) override;
  virtual void visit (HIR::LazyBooleanExpr &expr) override;
  virtual void visit (HIR::TypeCastExpr &expr) override;
  virtual void visit (HIR::AssignmentExpr &expr) override;
  virtual void visit (HIR::CompoundAssignmentExpr &expr) override;
  virtual void visit (HIR::GroupedExpr &expr) override;
  virtual void visit (HIR::ArrayElemsValues &elems) override;
  virtual void visit (HIR::ArrayElemsCopied &elems) override;
  virtual void visit (HIR::ArrayExpr &expr) override;
  virtual void visit (HIR::ArrayIndexExpr &expr) override;
  virtual void visit (HIR::TupleExpr &expr) override;
  virtual void visit (HIR::TupleIndexExpr &expr) override;
  virtual void visit (HIR::StructExprStruct &expr) override;
  virtual void visit (HIR::StructExprFieldIdentifier &field) override;
  virtual void visit (HIR::StructExprFieldIdentifierValue &field) override;
  virtual void visit (HIR::StructExprFieldIndexValue &field) override;
  virtual void visit (HIR::StructExprStructFields &expr) override;
  virtual void visit (HIR::StructExprStructBase &expr) override;
  virtual void visit (HIR::CallExpr &expr) override;
  virtual void visit (HIR::MethodCallExpr &expr) override;
  virtual void visit (HIR::FieldAccessExpr &expr) override;
  virtual void visit (HIR::ClosureExprInner &expr) override;
  virtual void visit (HIR::BlockExpr &expr) override;
  virtual void visit (HIR::ClosureExprInnerTyped &expr) override;
  virtual void visit (HIR::ContinueExpr &expr) override;
  virtual void visit (HIR::BreakExpr &expr) override;
  virtual void visit (HIR::RangeFromToExpr &expr) override;
  virtual void visit (HIR::RangeFromExpr &expr) override;
  virtual void visit (HIR::RangeToExpr &expr) override;
  virtual void visit (HIR::RangeFullExpr &expr) override;
  virtual void visit (HIR::RangeFromToInclExpr &expr) override;
  virtual void visit (HIR::RangeToInclExpr &expr) override;
  virtual void visit (HIR::ReturnExpr &expr) override;
  virtual void visit (HIR::UnsafeBlockExpr &expr) override;
  virtual void visit (HIR::LoopExpr &expr) override;
  virtual void visit (HIR::WhileLoopExpr &expr) override;
  virtual void visit (HIR::WhileLetLoopExpr &expr) override;
  virtual void visit (HIR::ForLoopExpr &expr) override;
  virtual void visit (HIR::IfExpr &expr) override;
  virtual void visit (HIR::IfExprConseqElse &expr) override;
  virtual void visit (HIR::IfExprConseqIf &expr) override;
  virtual void visit (HIR::IfExprConseqIfLet &expr) override;
  virtual void visit (HIR::IfLetExpr &expr) override;
  virtual void visit (HIR::IfLetExprConseqElse &expr) override;
  virtual void visit (HIR::IfLetExprConseqIf &expr) override;
  virtual void visit (HIR::IfLetExprConseqIfLet &expr) override;
  virtual void visit (HIR::MatchExpr &expr) override;
  virtual void visit (HIR::AwaitExpr &expr) override;
  virtual void visit (HIR::AsyncBlockExpr &expr) override;
  virtual void visit (HIR::TypeParam &param) override;
  virtual void visit (HIR::ConstGenericParam &param) override;
  virtual void visit (HIR::LifetimeWhereClauseItem &item) override;
  virtual void visit (HIR::TypeBoundWhereClauseItem &item) override;
  virtual void visit (HIR::Module &module) override;
  virtual void visit (HIR::ExternCrate &crate) override;
  virtual void visit (HIR::UseTreeGlob &use_tree) override;
  virtual void visit (HIR::UseTreeList &use_tree) override;
  virtual void visit (HIR::UseTreeRebind &use_tree) override;
  virtual void visit (HIR::UseDeclaration &use_decl) override;
  virtual void visit (HIR::Function &function) override;
  virtual void visit (HIR::TypeAlias &type_alias) override;
  virtual void visit (HIR::StructStruct &struct_item) override;
  virtual void visit (HIR::TupleStruct &tuple_struct) override;
  virtual void visit (HIR::EnumItem &item) override;
  virtual void visit (HIR::EnumItemTuple &item) override;
  virtual void visit (HIR::EnumItemStruct &item) override;
  virtual void visit (HIR::EnumItemDiscriminant &item) override;
  virtual void visit (HIR::Enum &enum_item) override;
  virtual void visit (HIR::Union &union_item) override;
  virtual void visit (HIR::ConstantItem &const_item) override;
  virtual void visit (HIR::StaticItem &static_item) override;
  virtual void visit (HIR::TraitItemFunc &item) override;
  virtual void visit (HIR::TraitItemConst &item) override;
  virtual void visit (HIR::TraitItemType &item) override;
  virtual void visit (HIR::Trait &trait) override;
  virtual void visit (HIR::ImplBlock &impl) override;
  virtual void visit (HIR::ExternalStaticItem &item) override;
  virtual void visit (HIR::ExternalFunctionItem &item) override;
  virtual void visit (HIR::ExternBlock &block) override;
  virtual void visit (HIR::LiteralPattern &pattern) override;
  virtual void visit (HIR::IdentifierPattern &pattern) override;
  virtual void visit (HIR::WildcardPattern &pattern) override;
  virtual void visit (HIR::RangePatternBoundLiteral &bound) override;
  virtual void visit (HIR::RangePatternBoundPath &bound) override;
  virtual void visit (HIR::RangePatternBoundQualPath &bound) override;
  virtual void visit (HIR::RangePattern &pattern) override;
  virtual void visit (HIR::ReferencePattern &pattern) override;
  virtual void visit (HIR::StructPatternFieldTuplePat &field) override;
  virtual void visit (HIR::StructPatternFieldIdentPat &field) override;
  virtual void visit (HIR::StructPatternFieldIdent &field) override;
  virtual void visit (HIR::StructPattern &pattern) override;
  virtual void visit (HIR::TupleStructItemsNoRange &tuple_items) override;
  virtual void visit (HIR::TupleStructItemsRange &tuple_items) override;
  virtual void visit (HIR::TupleStructPattern &pattern) override;
  virtual void visit (HIR::TuplePatternItemsMultiple &tuple_items) override;
  virtual void visit (HIR::TuplePatternItemsRanged &tuple_items) override;
  virtual void visit (HIR::TuplePattern &pattern) override;
  virtual void visit (HIR::GroupedPattern &pattern) override;
  virtual void visit (HIR::SlicePattern &pattern) override;
  virtual void visit (HIR::EmptyStmt &stmt) override;
  virtual void visit (HIR::LetStmt &stmt) override;
  virtual void visit (HIR::ExprStmtWithoutBlock &stmt) override;
  virtual void visit (HIR::ExprStmtWithBlock &stmt) override;
  virtual void visit (HIR::TraitBound &bound) override;
  virtual void visit (HIR::ImplTraitType &type) override;
  virtual void visit (HIR::TraitObjectType &type) override;
  virtual void visit (HIR::ParenthesisedType &type) override;
  virtual void visit (HIR::ImplTraitTypeOneBound &type) override;
  virtual void visit (HIR::TupleType &type) override;
  virtual void visit (HIR::NeverType &type) override;
  virtual void visit (HIR::RawPointerType &type) override;
  virtual void visit (HIR::ReferenceType &type) override;
  virtual void visit (HIR::ArrayType &type) override;
  virtual void visit (HIR::SliceType &type) override;
  virtual void visit (HIR::InferredType &type) override;
  virtual void visit (HIR::BareFunctionType &type) override;
};

/**
 *

void
BorrowChecker::visit (HIR::AssignmentExpr &expr)
{
  // FIXME: Check if the variable already exists? Or if we're assigning it?
}

void
BorrowChecker::visit (HIR::LetStmt &let)
{
  if (let.has_init_expr ())
    polonius.define_var (let.get_mappings ().get_hirid (),
			 let.has_init_expr ());

  // FIXME: How do we handle variables declared but defined later on?
  //
  // ```
  // let x;
  //
  // if foo()
  //     x = 15;
  // else
  //     x = 14;
  // ```
}
 */

} // namespace Resolver
} // namespace Rust

#endif // !RUST_HIR_BORROW_CHECK_H
