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

#include "rust-toplevel-name-resolver-2.0.h"
#include "rust-ast-full.h"

namespace Rust {
namespace Resolver2_0 {

TopLevel::TopLevel (Resolver &resolver) : resolver (resolver) {}

void
TopLevel::go (AST::Crate &crate)
{
  for (auto &item : crate.items)
    item->accept_vis (*this);
}

void
TopLevel::visit (AST::Token &tok)
{}

void
TopLevel::visit (AST::DelimTokenTree &delim_tok_tree)
{}

void
TopLevel::visit (AST::AttrInputMetaItemContainer &input)
{}

void
TopLevel::visit (AST::IdentifierExpr &ident_expr)
{}

void
TopLevel::visit (AST::Lifetime &lifetime)
{}

void
TopLevel::visit (AST::LifetimeParam &lifetime_param)
{}

void
TopLevel::visit (AST::ConstGenericParam &const_param)
{}

void
TopLevel::visit (AST::PathInExpression &path)
{}

void
TopLevel::visit (AST::TypePathSegment &segment)
{}

void
TopLevel::visit (AST::TypePathSegmentGeneric &segment)
{}

void
TopLevel::visit (AST::TypePathSegmentFunction &segment)
{}

void
TopLevel::visit (AST::TypePath &path)
{}

void
TopLevel::visit (AST::QualifiedPathInExpression &path)
{}

void
TopLevel::visit (AST::QualifiedPathInType &path)
{}

void
TopLevel::visit (AST::LiteralExpr &expr)
{}

void
TopLevel::visit (AST::AttrInputLiteral &attr_input)
{}

void
TopLevel::visit (AST::AttrInputMacro &attr_input)
{}

void
TopLevel::visit (AST::MetaItemLitExpr &meta_item)
{}

void
TopLevel::visit (AST::MetaItemPathLit &meta_item)
{}

void
TopLevel::visit (AST::BorrowExpr &expr)
{}

void
TopLevel::visit (AST::DereferenceExpr &expr)
{}

void
TopLevel::visit (AST::ErrorPropagationExpr &expr)
{}

void
TopLevel::visit (AST::NegationExpr &expr)
{}

void
TopLevel::visit (AST::ArithmeticOrLogicalExpr &expr)
{}

void
TopLevel::visit (AST::ComparisonExpr &expr)
{}

void
TopLevel::visit (AST::LazyBooleanExpr &expr)
{}

void
TopLevel::visit (AST::TypeCastExpr &expr)
{}

void
TopLevel::visit (AST::AssignmentExpr &expr)
{}

void
TopLevel::visit (AST::CompoundAssignmentExpr &expr)
{}

void
TopLevel::visit (AST::GroupedExpr &expr)
{}

void
TopLevel::visit (AST::ArrayElemsValues &elems)
{}

void
TopLevel::visit (AST::ArrayElemsCopied &elems)
{}

void
TopLevel::visit (AST::ArrayExpr &expr)
{}

void
TopLevel::visit (AST::ArrayIndexExpr &expr)
{}

void
TopLevel::visit (AST::TupleExpr &expr)
{}

void
TopLevel::visit (AST::TupleIndexExpr &expr)
{}

void
TopLevel::visit (AST::StructExprStruct &expr)
{}

void
TopLevel::visit (AST::StructExprFieldIdentifier &field)
{}

void
TopLevel::visit (AST::StructExprFieldIdentifierValue &field)
{}

void
TopLevel::visit (AST::StructExprFieldIndexValue &field)
{}

void
TopLevel::visit (AST::StructExprStructFields &expr)
{}

void
TopLevel::visit (AST::StructExprStructBase &expr)
{}

void
TopLevel::visit (AST::CallExpr &expr)
{}

void
TopLevel::visit (AST::MethodCallExpr &expr)
{}

void
TopLevel::visit (AST::FieldAccessExpr &expr)
{}

void
TopLevel::visit (AST::ClosureExprInner &expr)
{}

void
TopLevel::visit (AST::BlockExpr &expr)
{}

void
TopLevel::visit (AST::ClosureExprInnerTyped &expr)
{}

void
TopLevel::visit (AST::ContinueExpr &expr)
{}

void
TopLevel::visit (AST::BreakExpr &expr)
{}

void
TopLevel::visit (AST::RangeFromToExpr &expr)
{}

void
TopLevel::visit (AST::RangeFromExpr &expr)
{}

void
TopLevel::visit (AST::RangeToExpr &expr)
{}

void
TopLevel::visit (AST::RangeFullExpr &expr)
{}

void
TopLevel::visit (AST::RangeFromToInclExpr &expr)
{}

void
TopLevel::visit (AST::RangeToInclExpr &expr)
{}

void
TopLevel::visit (AST::ReturnExpr &expr)
{}

void
TopLevel::visit (AST::UnsafeBlockExpr &expr)
{}

void
TopLevel::visit (AST::LoopExpr &expr)
{}

void
TopLevel::visit (AST::WhileLoopExpr &expr)
{}

void
TopLevel::visit (AST::WhileLetLoopExpr &expr)
{}

void
TopLevel::visit (AST::ForLoopExpr &expr)
{}

void
TopLevel::visit (AST::IfExpr &expr)
{}

void
TopLevel::visit (AST::IfExprConseqElse &expr)
{}

void
TopLevel::visit (AST::IfLetExpr &expr)
{}

void
TopLevel::visit (AST::IfLetExprConseqElse &expr)
{}

void
TopLevel::visit (AST::MatchExpr &expr)
{}

void
TopLevel::visit (AST::AwaitExpr &expr)
{}

void
TopLevel::visit (AST::AsyncBlockExpr &expr)
{}

void
TopLevel::visit (AST::TypeParam &param)
{}

void
TopLevel::visit (AST::LifetimeWhereClauseItem &item)
{}

void
TopLevel::visit (AST::TypeBoundWhereClauseItem &item)
{}

void
TopLevel::visit (AST::Method &method)
{}

void
TopLevel::visit (AST::Module &module)
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
TopLevel::visit (AST::ExternCrate &crate)
{}

void
TopLevel::visit (AST::UseTreeGlob &use_tree)
{}

void
TopLevel::visit (AST::UseTreeList &use_tree)
{}

void
TopLevel::visit (AST::UseTreeRebind &use_tree)
{}

void
TopLevel::visit (AST::UseDeclaration &use_decl)
{}

void
TopLevel::visit (AST::Function &function)
{
  resolver.insert (function.get_function_name (), function.get_node_id (),
		   Namespace::Values);
}

void
TopLevel::visit (AST::TypeAlias &type_alias)
{}

void
TopLevel::visit (AST::StructStruct &struct_item)
{}

void
TopLevel::visit (AST::TupleStruct &tuple_struct)
{}

void
TopLevel::visit (AST::EnumItem &item)
{}

void
TopLevel::visit (AST::EnumItemTuple &item)
{}

void
TopLevel::visit (AST::EnumItemStruct &item)
{}

void
TopLevel::visit (AST::EnumItemDiscriminant &item)
{}

void
TopLevel::visit (AST::Enum &enum_item)
{}

void
TopLevel::visit (AST::Union &union_item)
{}

void
TopLevel::visit (AST::ConstantItem &const_item)
{}

void
TopLevel::visit (AST::StaticItem &static_item)
{}

void
TopLevel::visit (AST::TraitItemFunc &item)
{}

void
TopLevel::visit (AST::TraitItemMethod &item)
{}

void
TopLevel::visit (AST::TraitItemConst &item)
{}

void
TopLevel::visit (AST::TraitItemType &item)
{}

void
TopLevel::visit (AST::Trait &trait)
{}

void
TopLevel::visit (AST::InherentImpl &impl)
{}

void
TopLevel::visit (AST::TraitImpl &impl)
{}

void
TopLevel::visit (AST::ExternalTypeItem &type)
{}

void
TopLevel::visit (AST::ExternalStaticItem &item)
{}

void
TopLevel::visit (AST::ExternalFunctionItem &item)
{}

void
TopLevel::visit (AST::ExternBlock &block)
{}

void
TopLevel::visit (AST::MacroMatchFragment &match)
{}

void
TopLevel::visit (AST::MacroMatchRepetition &match)
{}

void
TopLevel::visit (AST::MacroMatcher &matcher)
{}

void
TopLevel::visit (AST::MacroRulesDefinition &rules_def)
{}

void
TopLevel::visit (AST::MacroInvocation &macro_invoc)
{}

void
TopLevel::visit (AST::MetaItemPath &meta_item)
{}

void
TopLevel::visit (AST::MetaItemSeq &meta_item)
{}

void
TopLevel::visit (AST::MetaWord &meta_item)
{}

void
TopLevel::visit (AST::MetaNameValueStr &meta_item)
{}

void
TopLevel::visit (AST::MetaListPaths &meta_item)
{}

void
TopLevel::visit (AST::MetaListNameValueStr &meta_item)
{}

void
TopLevel::visit (AST::LiteralPattern &pattern)
{}

void
TopLevel::visit (AST::IdentifierPattern &pattern)
{}

void
TopLevel::visit (AST::WildcardPattern &pattern)
{}

void
TopLevel::visit (AST::RestPattern &pattern)
{}

void
TopLevel::visit (AST::RangePatternBoundLiteral &bound)
{}

void
TopLevel::visit (AST::RangePatternBoundPath &bound)
{}

void
TopLevel::visit (AST::RangePatternBoundQualPath &bound)
{}

void
TopLevel::visit (AST::RangePattern &pattern)
{}

void
TopLevel::visit (AST::ReferencePattern &pattern)
{}

void
TopLevel::visit (AST::StructPatternFieldTuplePat &field)
{}

void
TopLevel::visit (AST::StructPatternFieldIdentPat &field)
{}

void
TopLevel::visit (AST::StructPatternFieldIdent &field)
{}

void
TopLevel::visit (AST::StructPattern &pattern)
{}

void
TopLevel::visit (AST::TupleStructItemsNoRange &tuple_items)
{}

void
TopLevel::visit (AST::TupleStructItemsRange &tuple_items)
{}

void
TopLevel::visit (AST::TupleStructPattern &pattern)
{}

void
TopLevel::visit (AST::TuplePatternItemsMultiple &tuple_items)
{}

void
TopLevel::visit (AST::TuplePatternItemsRanged &tuple_items)
{}

void
TopLevel::visit (AST::TuplePattern &pattern)
{}

void
TopLevel::visit (AST::GroupedPattern &pattern)
{}

void
TopLevel::visit (AST::SlicePattern &pattern)
{}

void
TopLevel::visit (AST::AltPattern &pattern)
{}

void
TopLevel::visit (AST::EmptyStmt &stmt)
{}

void
TopLevel::visit (AST::LetStmt &stmt)
{}

void
TopLevel::visit (AST::ExprStmt &stmt)
{}

void
TopLevel::visit (AST::TraitBound &bound)
{}

void
TopLevel::visit (AST::ImplTraitType &type)
{}

void
TopLevel::visit (AST::TraitObjectType &type)
{}

void
TopLevel::visit (AST::ParenthesisedType &type)
{}

void
TopLevel::visit (AST::ImplTraitTypeOneBound &type)
{}

void
TopLevel::visit (AST::TraitObjectTypeOneBound &type)
{}

void
TopLevel::visit (AST::TupleType &type)
{}

void
TopLevel::visit (AST::NeverType &type)
{}

void
TopLevel::visit (AST::RawPointerType &type)
{}

void
TopLevel::visit (AST::ReferenceType &type)
{}

void
TopLevel::visit (AST::ArrayType &type)
{}

void
TopLevel::visit (AST::SliceType &type)
{}

void
TopLevel::visit (AST::InferredType &type)
{}

void
TopLevel::visit (AST::BareFunctionType &type)
{}

} // namespace Resolver2_0
} // namespace Rust
