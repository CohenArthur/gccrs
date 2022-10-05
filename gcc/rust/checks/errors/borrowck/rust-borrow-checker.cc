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
  : polonius (Polonius ()), resolver (*Resolver::Resolver::get ()),
    mappings (*Analysis::Mappings::get ())
{}

void
BorrowChecker::go (HIR::Crate &crate)
{
  for (auto &item : crate.items)
    item->accept_vis (*this);

  polonius.compute ();
}

void
BorrowChecker::visit (HIR::Lifetime &lifetime)
{}

void
BorrowChecker::visit (HIR::LifetimeParam &lifetime_param)
{}

void
BorrowChecker::visit (HIR::PathInExpression &path)
{
  NodeId ast_node_id = path.get_mappings ().get_nodeid ();
  NodeId ref_node_id;
  HirId definition_id;

  if (!resolver.lookup_resolved_name (ast_node_id, &ref_node_id))
    return;

  rust_assert (mappings.lookup_node_to_hir (ref_node_id, &definition_id));

  polonius.var_used_at (definition_id, current_point);
}

void
BorrowChecker::visit (HIR::TypePathSegment &segment)
{}

void
BorrowChecker::visit (HIR::TypePathSegmentGeneric &segment)
{}

void
BorrowChecker::visit (HIR::TypePathSegmentFunction &segment)
{}

void
BorrowChecker::visit (HIR::TypePath &path)
{}

void
BorrowChecker::visit (HIR::QualifiedPathInExpression &path)
{}

void
BorrowChecker::visit (HIR::QualifiedPathInType &path)
{}

void
BorrowChecker::visit (HIR::LiteralExpr &expr)
{}

void
BorrowChecker::visit (HIR::BorrowExpr &expr)
{
  expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::DereferenceExpr &expr)
{
  // FIXME: Do we do anything for dereferencing?
  //  TyTy::BaseType *to_deref_type;
  //  auto to_deref = expr.get_expr ()->get_mappings ().get_hirid ();
  //
  //  rust_assert (context.lookup_type (to_deref, &to_deref_type));
  //
  //  if (to_deref_type->get_kind () == TyTy::TypeKind::POINTER
  //      && !unsafe_context.is_in_context ())
  //    rust_error_at (expr.get_locus (), "dereference of raw pointer requires "
  //				      "unsafe function or block");
}

void
BorrowChecker::visit (HIR::ErrorPropagationExpr &expr)
{
  expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::NegationExpr &expr)
{
  expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ArithmeticOrLogicalExpr &expr)
{
  expr.get_lhs ()->accept_vis (*this);
  expr.get_rhs ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ComparisonExpr &expr)
{
  expr.get_lhs ()->accept_vis (*this);
  expr.get_rhs ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::LazyBooleanExpr &expr)
{
  expr.get_lhs ()->accept_vis (*this);
  expr.get_rhs ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TypeCastExpr &expr)
{
  expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::AssignmentExpr &expr)
{
  expr.get_lhs ()->accept_vis (*this);
  expr.get_rhs ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::CompoundAssignmentExpr &expr)
{
  expr.get_left_expr ()->accept_vis (*this);
  expr.get_right_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::GroupedExpr &expr)
{
  expr.get_expr_in_parens ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ArrayElemsValues &elems)
{
  for (auto &elem : elems.get_values ())
    elem->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ArrayElemsCopied &elems)
{
  elems.get_elem_to_copy ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ArrayExpr &expr)
{
  expr.get_internal_elements ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ArrayIndexExpr &expr)
{
  expr.get_array_expr ()->accept_vis (*this);
  expr.get_index_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TupleExpr &expr)
{
  for (auto &elem : expr.get_tuple_elems ())
    elem->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TupleIndexExpr &expr)
{
  expr.get_tuple_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::StructExprStruct &expr)
{}

void
BorrowChecker::visit (HIR::StructExprFieldIdentifier &field)
{}

void
BorrowChecker::visit (HIR::StructExprFieldIdentifierValue &field)
{
  field.get_value ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::StructExprFieldIndexValue &field)
{
  field.get_value ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::StructExprStructFields &expr)
{
  for (auto &field : expr.get_fields ())
    field->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::StructExprStructBase &expr)
{}

void
BorrowChecker::visit (HIR::CallExpr &expr)
{
  if (expr.has_params ())
    for (auto &arg : expr.get_arguments ())
      arg->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::MethodCallExpr &expr)
{}

void
BorrowChecker::visit (HIR::FieldAccessExpr &expr)
{
  // FIXME: Do we do anything with field accesses?
  // expr.get_receiver_expr ()->accept_vis (*this);

  // if (unsafe_context.is_in_context ())
  //   return;

  // TyTy::BaseType *receiver_ty;
  // auto ok = context.lookup_type (
  //   expr.get_receiver_expr ()->get_mappings ().get_hirid (), &receiver_ty);
  // rust_assert (ok);

  // if (receiver_ty->get_kind () == TyTy::TypeKind::ADT)
  //   {
  //     auto maybe_union = static_cast<TyTy::ADTType *> (receiver_ty);
  //     if (maybe_union->is_union ())
  //     rust_error_at (
  //       expr.get_locus (),
  //       "access to union field requires unsafe function or block");
  //   }
}

void
BorrowChecker::visit (HIR::ClosureExprInner &expr)
{}

void
BorrowChecker::visit (HIR::BlockExpr &expr)
{
  for (auto &stmt : expr.get_statements ())
    {
      set_current_point (stmt);
      stmt->accept_vis (*this);
    }

  if (expr.has_expr ())
    {
      set_current_point (expr);
      expr.get_final_expr ()->accept_vis (*this);
    }
}

void
BorrowChecker::visit (HIR::ClosureExprInnerTyped &expr)
{}

void
BorrowChecker::visit (HIR::ContinueExpr &expr)
{}

void
BorrowChecker::visit (HIR::BreakExpr &expr)
{
  if (expr.has_break_expr ())
    expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::RangeFromToExpr &expr)
{
  expr.get_from_expr ()->accept_vis (*this);
  expr.get_to_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::RangeFromExpr &expr)
{
  expr.get_from_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::RangeToExpr &expr)
{
  expr.get_to_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::RangeFullExpr &expr)
{}

void
BorrowChecker::visit (HIR::RangeFromToInclExpr &expr)
{
  expr.get_from_expr ()->accept_vis (*this);
  expr.get_to_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::RangeToInclExpr &expr)
{
  expr.get_to_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ReturnExpr &expr)
{
  if (expr.has_return_expr ())
    expr.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::UnsafeBlockExpr &expr)
{
  expr.get_block_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::LoopExpr &expr)
{
  expr.get_loop_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::WhileLoopExpr &expr)
{
  expr.get_predicate_expr ()->accept_vis (*this);
  expr.get_loop_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::WhileLetLoopExpr &expr)
{
  expr.get_cond ()->accept_vis (*this);
  expr.get_loop_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ForLoopExpr &expr)
{
  expr.get_iterator_expr ()->accept_vis (*this);
  expr.get_loop_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfExpr &expr)
{
  expr.get_if_condition ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfExprConseqElse &expr)
{
  expr.get_if_condition ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);
  expr.get_else_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfExprConseqIf &expr)
{
  expr.get_if_condition ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);
  expr.get_conseq_if_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfExprConseqIfLet &expr)
{
  expr.get_if_condition ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);

  // TODO: Visit conseq if let expression
}

void
BorrowChecker::visit (HIR::IfLetExpr &expr)
{
  expr.get_scrutinee_expr ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfLetExprConseqElse &expr)
{
  expr.get_scrutinee_expr ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);

  // TODO: Visit else expression
}

void
BorrowChecker::visit (HIR::IfLetExprConseqIf &expr)
{
  expr.get_scrutinee_expr ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::IfLetExprConseqIfLet &expr)
{
  expr.get_scrutinee_expr ()->accept_vis (*this);
  expr.get_if_block ()->accept_vis (*this);

  // TODO: Visit conseq if let expression
}

void
BorrowChecker::visit (HIR::MatchExpr &expr)
{
  expr.get_scrutinee_expr ()->accept_vis (*this);

  for (auto &match_arm : expr.get_match_cases ())
    match_arm.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::AwaitExpr &expr)
{
  // TODO: Visit expression
}

void
BorrowChecker::visit (HIR::AsyncBlockExpr &expr)
{
  // TODO: Visit block expression
}

void
BorrowChecker::visit (HIR::TypeParam &param)
{}

void
BorrowChecker::visit (HIR::ConstGenericParam &param)
{}

void
BorrowChecker::visit (HIR::LifetimeWhereClauseItem &item)
{}

void
BorrowChecker::visit (HIR::TypeBoundWhereClauseItem &item)
{}

void
BorrowChecker::visit (HIR::Module &module)
{
  for (auto &item : module.get_items ())
    item->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ExternCrate &crate)
{}

void
BorrowChecker::visit (HIR::UseTreeGlob &use_tree)
{}

void
BorrowChecker::visit (HIR::UseTreeList &use_tree)
{}

void
BorrowChecker::visit (HIR::UseTreeRebind &use_tree)
{}

void
BorrowChecker::visit (HIR::UseDeclaration &use_decl)
{}

void
BorrowChecker::visit (HIR::Function &function)
{
  function.get_definition ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TypeAlias &type_alias)
{
  // FIXME: What do we need to do to handle type aliasing? Is it possible to
  // have unsafe types? Type aliases on unsafe functions?
}

void
BorrowChecker::visit (HIR::StructStruct &struct_item)
{}

void
BorrowChecker::visit (HIR::TupleStruct &tuple_struct)
{}

void
BorrowChecker::visit (HIR::EnumItem &item)
{}

void
BorrowChecker::visit (HIR::EnumItemTuple &item)
{}

void
BorrowChecker::visit (HIR::EnumItemStruct &item)
{}

void
BorrowChecker::visit (HIR::EnumItemDiscriminant &item)
{}

void
BorrowChecker::visit (HIR::Enum &enum_item)
{}

void
BorrowChecker::visit (HIR::Union &union_item)
{}

void
BorrowChecker::visit (HIR::ConstantItem &const_item)
{
  const_item.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::StaticItem &static_item)
{
  static_item.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TraitItemFunc &item)
{
  if (item.has_block_defined ())
    item.get_block_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TraitItemConst &item)
{
  if (item.has_expr ())
    item.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TraitItemType &item)
{}

void
BorrowChecker::visit (HIR::Trait &trait)
{
  // FIXME: Handle unsafe traits
  for (auto &item : trait.get_trait_items ())
    item->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ImplBlock &impl)
{
  // FIXME: Handle unsafe impls
  for (auto &item : impl.get_impl_items ())
    item->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ExternalStaticItem &item)
{}

void
BorrowChecker::visit (HIR::ExternalFunctionItem &item)
{}

void
BorrowChecker::visit (HIR::ExternBlock &block)
{
  // FIXME: Do we need to do this?
  for (auto &item : block.get_extern_items ())
    item->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::LiteralPattern &pattern)
{}

void
BorrowChecker::visit (HIR::IdentifierPattern &pattern)
{}

void
BorrowChecker::visit (HIR::WildcardPattern &pattern)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundLiteral &bound)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundPath &bound)
{}

void
BorrowChecker::visit (HIR::RangePatternBoundQualPath &bound)
{}

void
BorrowChecker::visit (HIR::RangePattern &pattern)
{}

void
BorrowChecker::visit (HIR::ReferencePattern &pattern)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldTuplePat &field)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldIdentPat &field)
{}

void
BorrowChecker::visit (HIR::StructPatternFieldIdent &field)
{}

void
BorrowChecker::visit (HIR::StructPattern &pattern)
{}

void
BorrowChecker::visit (HIR::TupleStructItemsNoRange &tuple_items)
{}

void
BorrowChecker::visit (HIR::TupleStructItemsRange &tuple_items)
{}

void
BorrowChecker::visit (HIR::TupleStructPattern &pattern)
{}

void
BorrowChecker::visit (HIR::TuplePatternItemsMultiple &tuple_items)
{}

void
BorrowChecker::visit (HIR::TuplePatternItemsRanged &tuple_items)
{}

void
BorrowChecker::visit (HIR::TuplePattern &pattern)
{}

void
BorrowChecker::visit (HIR::GroupedPattern &pattern)
{}

void
BorrowChecker::visit (HIR::SlicePattern &pattern)
{}

void
BorrowChecker::visit (HIR::EmptyStmt &stmt)
{}

void
BorrowChecker::visit (HIR::LetStmt &stmt)
{
  set_current_point (stmt);

  if (stmt.has_init_expr ())
    {
      // FIXME: Is it correct to use the pattern ID for this?
      polonius.define_var (
	current_point,
	stmt.get_pattern ()->get_pattern_mappings ().get_hirid ());

      stmt.get_init_expr ()->accept_vis (*this);
    }
}

void
BorrowChecker::visit (HIR::ExprStmtWithoutBlock &stmt)
{
  stmt.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::ExprStmtWithBlock &stmt)
{
  stmt.get_expr ()->accept_vis (*this);
}

void
BorrowChecker::visit (HIR::TraitBound &bound)
{}

void
BorrowChecker::visit (HIR::ImplTraitType &type)
{}

void
BorrowChecker::visit (HIR::TraitObjectType &type)
{}

void
BorrowChecker::visit (HIR::ParenthesisedType &type)
{}

void
BorrowChecker::visit (HIR::ImplTraitTypeOneBound &type)
{}

void
BorrowChecker::visit (HIR::TupleType &type)
{}

void
BorrowChecker::visit (HIR::NeverType &type)
{}

void
BorrowChecker::visit (HIR::RawPointerType &type)
{}

void
BorrowChecker::visit (HIR::ReferenceType &type)
{}

void
BorrowChecker::visit (HIR::ArrayType &type)
{}

void
BorrowChecker::visit (HIR::SliceType &type)
{}

void
BorrowChecker::visit (HIR::InferredType &type)
{}

void
BorrowChecker::visit (HIR::BareFunctionType &type)
{}

} // namespace Resolver
} // namespace Rust
