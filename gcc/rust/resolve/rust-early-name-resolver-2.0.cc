// Copyright (C) 2020-2023 Free Software Foundation, Inc.

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

#include "rust-early-name-resolver-2.0.h"
#include "rust-ast-full.h"
#include "rust-toplevel-name-resolver-2.0.h"

namespace Rust {
namespace Resolver2_0 {

Early::Early (Resolver &resolver) : resolver (resolver) {}

void
Early::go (AST::Crate &crate)
{
  // First we go through TopLevel resolution to get all our declared items
  auto toplevel = TopLevel (resolver);
  toplevel.go (crate);

  // Then we proceed to the proper "early" name resolution: Import and macro
  // name resolution
  for (auto &item : crate.items)
    item->accept_vis (*this);

  resolver.values.debug_str ();
}

void
Early::visit (AST::Token &tok)
{}

void
Early::visit (AST::DelimTokenTree &delim_tok_tree)
{}

void
Early::visit (AST::AttrInputMetaItemContainer &input)
{}

void
Early::visit (AST::IdentifierExpr &ident_expr)
{}

void
Early::visit (AST::Lifetime &lifetime)
{}

void
Early::visit (AST::LifetimeParam &lifetime_param)
{}

void
Early::visit (AST::ConstGenericParam &const_param)
{}

void
Early::visit (AST::PathInExpression &path)
{}

void
Early::visit (AST::TypePathSegment &segment)
{}

void
Early::visit (AST::TypePathSegmentGeneric &segment)
{}

void
Early::visit (AST::TypePathSegmentFunction &segment)
{}

void
Early::visit (AST::TypePath &path)
{}

void
Early::visit (AST::QualifiedPathInExpression &path)
{}

void
Early::visit (AST::QualifiedPathInType &path)
{}

void
Early::visit (AST::LiteralExpr &expr)
{}

void
Early::visit (AST::AttrInputLiteral &attr_input)
{}

void
Early::visit (AST::AttrInputMacro &attr_input)
{}

void
Early::visit (AST::MetaItemLitExpr &meta_item)
{}

void
Early::visit (AST::MetaItemPathLit &meta_item)
{}

void
Early::visit (AST::BorrowExpr &expr)
{}

void
Early::visit (AST::DereferenceExpr &expr)
{}

void
Early::visit (AST::ErrorPropagationExpr &expr)
{}

void
Early::visit (AST::NegationExpr &expr)
{}

void
Early::visit (AST::ArithmeticOrLogicalExpr &expr)
{}

void
Early::visit (AST::ComparisonExpr &expr)
{}

void
Early::visit (AST::LazyBooleanExpr &expr)
{}

void
Early::visit (AST::TypeCastExpr &expr)
{}

void
Early::visit (AST::AssignmentExpr &expr)
{}

void
Early::visit (AST::CompoundAssignmentExpr &expr)
{}

void
Early::visit (AST::GroupedExpr &expr)
{}

void
Early::visit (AST::ArrayElemsValues &elems)
{}

void
Early::visit (AST::ArrayElemsCopied &elems)
{}

void
Early::visit (AST::ArrayExpr &expr)
{}

void
Early::visit (AST::ArrayIndexExpr &expr)
{}

void
Early::visit (AST::TupleExpr &expr)
{}

void
Early::visit (AST::TupleIndexExpr &expr)
{}

void
Early::visit (AST::StructExprStruct &expr)
{}

void
Early::visit (AST::StructExprFieldIdentifier &field)
{}

void
Early::visit (AST::StructExprFieldIdentifierValue &field)
{}

void
Early::visit (AST::StructExprFieldIndexValue &field)
{}

void
Early::visit (AST::StructExprStructFields &expr)
{}

void
Early::visit (AST::StructExprStructBase &expr)
{}

void
Early::visit (AST::CallExpr &expr)
{}

void
Early::visit (AST::MethodCallExpr &expr)
{}

void
Early::visit (AST::FieldAccessExpr &expr)
{}

void
Early::visit (AST::ClosureExprInner &expr)
{}

void
Early::visit (AST::BlockExpr &expr)
{
  resolver.scoped (Rib (Rib::Kind::Normal), Namespace::Values,
		   expr.get_node_id (), [this, &expr] () {
		     for (auto &stmt : expr.get_statements ())
		       stmt->accept_vis (*this);

		     if (expr.has_tail_expr ())
		       expr.get_tail_expr ()->accept_vis (*this);
		   });
}

void
Early::visit (AST::ClosureExprInnerTyped &expr)
{}

void
Early::visit (AST::ContinueExpr &expr)
{}

void
Early::visit (AST::BreakExpr &expr)
{}

void
Early::visit (AST::RangeFromToExpr &expr)
{}

void
Early::visit (AST::RangeFromExpr &expr)
{}

void
Early::visit (AST::RangeToExpr &expr)
{}

void
Early::visit (AST::RangeFullExpr &expr)
{}

void
Early::visit (AST::RangeFromToInclExpr &expr)
{}

void
Early::visit (AST::RangeToInclExpr &expr)
{}

void
Early::visit (AST::ReturnExpr &expr)
{}

void
Early::visit (AST::UnsafeBlockExpr &expr)
{}

void
Early::visit (AST::LoopExpr &expr)
{}

void
Early::visit (AST::WhileLoopExpr &expr)
{}

void
Early::visit (AST::WhileLetLoopExpr &expr)
{}

void
Early::visit (AST::ForLoopExpr &expr)
{}

void
Early::visit (AST::IfExpr &expr)
{}

void
Early::visit (AST::IfExprConseqElse &expr)
{}

void
Early::visit (AST::IfLetExpr &expr)
{}

void
Early::visit (AST::IfLetExprConseqElse &expr)
{}

void
Early::visit (AST::MatchExpr &expr)
{}

void
Early::visit (AST::AwaitExpr &expr)
{}

void
Early::visit (AST::AsyncBlockExpr &expr)
{}

void
Early::visit (AST::TypeParam &param)
{}

void
Early::visit (AST::LifetimeWhereClauseItem &item)
{}

void
Early::visit (AST::TypeBoundWhereClauseItem &item)
{}

void
Early::visit (AST::Method &method)
{}

void
Early::visit (AST::Module &module)
{
  resolver.scoped (
    Rib (Rib::Kind::Module), Namespace::Values, module.get_node_id (),
    [this, &module] () {
      for (auto &item : module.get_items ())
	item->accept_vis (*this);
    },
    module.get_name ());
}

void
Early::visit (AST::ExternCrate &crate)
{}

void
Early::visit (AST::UseTreeGlob &use_tree)
{}

void
Early::visit (AST::UseTreeList &use_tree)
{}

void
Early::visit (AST::UseTreeRebind &use_tree)
{}

void
Early::visit (AST::UseDeclaration &use_decl)
{}

void
Early::visit (AST::Function &function)
{
  resolver.insert (function.get_function_name (), function.get_node_id (),
		   Namespace::Values);

  resolver.scoped (Rib (Rib::Kind::Function), Namespace::Values,
		   function.get_node_id (), [this, &function] () {
		     /* FIXME: go through parameters here too */
		     /* FIXME: and generic parameters too */

		     function.get_definition ()->accept_vis (*this);
		   });
}

void
Early::visit (AST::TypeAlias &type_alias)
{}

void
Early::visit (AST::StructStruct &struct_item)
{}

void
Early::visit (AST::TupleStruct &tuple_struct)
{}

void
Early::visit (AST::EnumItem &item)
{}

void
Early::visit (AST::EnumItemTuple &item)
{}

void
Early::visit (AST::EnumItemStruct &item)
{}

void
Early::visit (AST::EnumItemDiscriminant &item)
{}

void
Early::visit (AST::Enum &enum_item)
{}

void
Early::visit (AST::Union &union_item)
{}

void
Early::visit (AST::ConstantItem &const_item)
{}

void
Early::visit (AST::StaticItem &static_item)
{}

void
Early::visit (AST::TraitItemFunc &item)
{}

void
Early::visit (AST::TraitItemMethod &item)
{}

void
Early::visit (AST::TraitItemConst &item)
{}

void
Early::visit (AST::TraitItemType &item)
{}

void
Early::visit (AST::Trait &trait)
{}

void
Early::visit (AST::InherentImpl &impl)
{}

void
Early::visit (AST::TraitImpl &impl)
{}

void
Early::visit (AST::ExternalTypeItem &type)
{}

void
Early::visit (AST::ExternalStaticItem &item)
{}

void
Early::visit (AST::ExternalFunctionItem &item)
{}

void
Early::visit (AST::ExternBlock &block)
{}

void
Early::visit (AST::MacroMatchFragment &match)
{}

void
Early::visit (AST::MacroMatchRepetition &match)
{}

void
Early::visit (AST::MacroMatcher &matcher)
{}

void
Early::visit (AST::MacroRulesDefinition &rules_def)
{}

void
Early::visit (AST::MacroInvocation &macro_invoc)
{}

void
Early::visit (AST::MetaItemPath &meta_item)
{}

void
Early::visit (AST::MetaItemSeq &meta_item)
{}

void
Early::visit (AST::MetaWord &meta_item)
{}

void
Early::visit (AST::MetaNameValueStr &meta_item)
{}

void
Early::visit (AST::MetaListPaths &meta_item)
{}

void
Early::visit (AST::MetaListNameValueStr &meta_item)
{}

void
Early::visit (AST::LiteralPattern &pattern)
{}

void
Early::visit (AST::IdentifierPattern &pattern)
{}

void
Early::visit (AST::WildcardPattern &pattern)
{}

void
Early::visit (AST::RestPattern &pattern)
{}

void
Early::visit (AST::RangePatternBoundLiteral &bound)
{}

void
Early::visit (AST::RangePatternBoundPath &bound)
{}

void
Early::visit (AST::RangePatternBoundQualPath &bound)
{}

void
Early::visit (AST::RangePattern &pattern)
{}

void
Early::visit (AST::ReferencePattern &pattern)
{}

void
Early::visit (AST::StructPatternFieldTuplePat &field)
{}

void
Early::visit (AST::StructPatternFieldIdentPat &field)
{}

void
Early::visit (AST::StructPatternFieldIdent &field)
{}

void
Early::visit (AST::StructPattern &pattern)
{}

void
Early::visit (AST::TupleStructItemsNoRange &tuple_items)
{}

void
Early::visit (AST::TupleStructItemsRange &tuple_items)
{}

void
Early::visit (AST::TupleStructPattern &pattern)
{}

void
Early::visit (AST::TuplePatternItemsMultiple &tuple_items)
{}

void
Early::visit (AST::TuplePatternItemsRanged &tuple_items)
{}

void
Early::visit (AST::TuplePattern &pattern)
{}

void
Early::visit (AST::GroupedPattern &pattern)
{}

void
Early::visit (AST::SlicePattern &pattern)
{}

void
Early::visit (AST::AltPattern &pattern)
{}

void
Early::visit (AST::EmptyStmt &stmt)
{}

void
Early::visit (AST::LetStmt &stmt)
{}

void
Early::visit (AST::ExprStmt &stmt)
{}

void
Early::visit (AST::TraitBound &bound)
{}

void
Early::visit (AST::ImplTraitType &type)
{}

void
Early::visit (AST::TraitObjectType &type)
{}

void
Early::visit (AST::ParenthesisedType &type)
{}

void
Early::visit (AST::ImplTraitTypeOneBound &type)
{}

void
Early::visit (AST::TraitObjectTypeOneBound &type)
{}

void
Early::visit (AST::TupleType &type)
{}

void
Early::visit (AST::NeverType &type)
{}

void
Early::visit (AST::RawPointerType &type)
{}

void
Early::visit (AST::ReferenceType &type)
{}

void
Early::visit (AST::ArrayType &type)
{}

void
Early::visit (AST::SliceType &type)
{}

void
Early::visit (AST::InferredType &type)
{}

void
Early::visit (AST::BareFunctionType &type)
{}

} // namespace Resolver2_0
} // namespace Rust
