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

#include "rust-default-resolver.h"

namespace Rust {
namespace Resolver2_0 {

void
DefaultResolver::visit (AST::Token &)
{}

void
DefaultResolver::visit (AST::DelimTokenTree &)
{}

void
DefaultResolver::visit (AST::AttrInputMetaItemContainer &)
{}

void
DefaultResolver::visit (AST::IdentifierExpr &)
{}

void
DefaultResolver::visit (AST::Lifetime &)
{}

void
DefaultResolver::visit (AST::LifetimeParam &)
{}

void
DefaultResolver::visit (AST::ConstGenericParam &)
{}

void
DefaultResolver::visit (AST::PathInExpression &)
{}

void
DefaultResolver::visit (AST::TypePathSegment &)
{}

void
DefaultResolver::visit (AST::TypePathSegmentGeneric &)
{}

void
DefaultResolver::visit (AST::TypePathSegmentFunction &)
{}

void
DefaultResolver::visit (AST::TypePath &)
{}

void
DefaultResolver::visit (AST::QualifiedPathInExpression &)
{}

void
DefaultResolver::visit (AST::QualifiedPathInType &)
{}

void
DefaultResolver::visit (AST::LiteralExpr &)
{}

void
DefaultResolver::visit (AST::AttrInputLiteral &)
{}

void
DefaultResolver::visit (AST::AttrInputMacro &)
{}

void
DefaultResolver::visit (AST::MetaItemLitExpr &)
{}

void
DefaultResolver::visit (AST::MetaItemPathLit &)
{}

void
DefaultResolver::visit (AST::BorrowExpr &)
{}

void
DefaultResolver::visit (AST::DereferenceExpr &)
{}

void
DefaultResolver::visit (AST::ErrorPropagationExpr &)
{}

void
DefaultResolver::visit (AST::NegationExpr &)
{}

void
DefaultResolver::visit (AST::ArithmeticOrLogicalExpr &)
{}

void
DefaultResolver::visit (AST::ComparisonExpr &)
{}

void
DefaultResolver::visit (AST::LazyBooleanExpr &)
{}

void
DefaultResolver::visit (AST::TypeCastExpr &)
{}

void
DefaultResolver::visit (AST::AssignmentExpr &)
{}

void
DefaultResolver::visit (AST::CompoundAssignmentExpr &)
{}

void
DefaultResolver::visit (AST::GroupedExpr &)
{}

void
DefaultResolver::visit (AST::ArrayElemsValues &)
{}

void
DefaultResolver::visit (AST::ArrayElemsCopied &)
{}

void
DefaultResolver::visit (AST::ArrayExpr &)
{}

void
DefaultResolver::visit (AST::ArrayIndexExpr &)
{}

void
DefaultResolver::visit (AST::TupleExpr &)
{}

void
DefaultResolver::visit (AST::TupleIndexExpr &)
{}

void
DefaultResolver::visit (AST::StructExprStruct &)
{}

void
DefaultResolver::visit (AST::StructExprFieldIdentifier &)
{}

void
DefaultResolver::visit (AST::StructExprFieldIdentifierValue &)
{}

void
DefaultResolver::visit (AST::StructExprFieldIndexValue &)
{}

void
DefaultResolver::visit (AST::StructExprStructFields &)
{}

void
DefaultResolver::visit (AST::StructExprStructBase &)
{}

void
DefaultResolver::visit (AST::CallExpr &)
{}

void
DefaultResolver::visit (AST::MethodCallExpr &)
{}

void
DefaultResolver::visit (AST::FieldAccessExpr &)
{}

void
DefaultResolver::visit (AST::ClosureExprInner &)
{}

void
DefaultResolver::visit (AST::BlockExpr &)
{}

void
DefaultResolver::visit (AST::ClosureExprInnerTyped &)
{}

void
DefaultResolver::visit (AST::ContinueExpr &)
{}

void
DefaultResolver::visit (AST::BreakExpr &)
{}

void
DefaultResolver::visit (AST::RangeFromToExpr &)
{}

void
DefaultResolver::visit (AST::RangeFromExpr &)
{}

void
DefaultResolver::visit (AST::RangeToExpr &)
{}

void
DefaultResolver::visit (AST::RangeFullExpr &)
{}

void
DefaultResolver::visit (AST::RangeFromToInclExpr &)
{}

void
DefaultResolver::visit (AST::RangeToInclExpr &)
{}

void
DefaultResolver::visit (AST::ReturnExpr &)
{}

void
DefaultResolver::visit (AST::UnsafeBlockExpr &)
{}

void
DefaultResolver::visit (AST::LoopExpr &)
{}

void
DefaultResolver::visit (AST::WhileLoopExpr &)
{}

void
DefaultResolver::visit (AST::WhileLetLoopExpr &)
{}

void
DefaultResolver::visit (AST::ForLoopExpr &)
{}

void
DefaultResolver::visit (AST::IfExpr &)
{}

void
DefaultResolver::visit (AST::IfExprConseqElse &)
{}

void
DefaultResolver::visit (AST::IfLetExpr &)
{}

void
DefaultResolver::visit (AST::IfLetExprConseqElse &)
{}

void
DefaultResolver::visit (AST::MatchExpr &)
{}

void
DefaultResolver::visit (AST::AwaitExpr &)
{}

void
DefaultResolver::visit (AST::AsyncBlockExpr &)
{}

void
DefaultResolver::visit (AST::TypeParam &)
{}

void
DefaultResolver::visit (AST::LifetimeWhereClauseItem &)
{}

void
DefaultResolver::visit (AST::TypeBoundWhereClauseItem &)
{}

void
DefaultResolver::visit (AST::Method &)
{}

void
DefaultResolver::visit (AST::Module &)
{}

void
DefaultResolver::visit (AST::ExternCrate &)
{}

void
DefaultResolver::visit (AST::UseTreeGlob &)
{}

void
DefaultResolver::visit (AST::UseTreeList &)
{}

void
DefaultResolver::visit (AST::UseTreeRebind &)
{}

void
DefaultResolver::visit (AST::UseDeclaration &)
{}

void
DefaultResolver::visit (AST::Function &)
{}

void
DefaultResolver::visit (AST::TypeAlias &)
{}

void
DefaultResolver::visit (AST::StructStruct &)
{}

void
DefaultResolver::visit (AST::TupleStruct &)
{}

void
DefaultResolver::visit (AST::EnumItem &)
{}

void
DefaultResolver::visit (AST::EnumItemTuple &)
{}

void
DefaultResolver::visit (AST::EnumItemStruct &)
{}

void
DefaultResolver::visit (AST::EnumItemDiscriminant &)
{}

void
DefaultResolver::visit (AST::Enum &)
{}

void
DefaultResolver::visit (AST::Union &)
{}

void
DefaultResolver::visit (AST::ConstantItem &)
{}

void
DefaultResolver::visit (AST::StaticItem &)
{}

void
DefaultResolver::visit (AST::TraitItemFunc &)
{}

void
DefaultResolver::visit (AST::TraitItemMethod &)
{}

void
DefaultResolver::visit (AST::TraitItemConst &)
{}

void
DefaultResolver::visit (AST::TraitItemType &)
{}

void
DefaultResolver::visit (AST::Trait &)
{}

void
DefaultResolver::visit (AST::InherentImpl &)
{}

void
DefaultResolver::visit (AST::TraitImpl &)
{}

void
DefaultResolver::visit (AST::ExternalTypeItem &)
{}

void
DefaultResolver::visit (AST::ExternalStaticItem &)
{}

void
DefaultResolver::visit (AST::ExternalFunctionItem &)
{}

void
DefaultResolver::visit (AST::ExternBlock &)
{}

void
DefaultResolver::visit (AST::MacroMatchFragment &)
{}

void
DefaultResolver::visit (AST::MacroMatchRepetition &)
{}

void
DefaultResolver::visit (AST::MacroMatcher &)
{}

void
DefaultResolver::visit (AST::MacroRulesDefinition &)
{}

void
DefaultResolver::visit (AST::MacroInvocation &)
{}

void
DefaultResolver::visit (AST::MetaItemPath &)
{}

void
DefaultResolver::visit (AST::MetaItemSeq &)
{}

void
DefaultResolver::visit (AST::MetaWord &)
{}

void
DefaultResolver::visit (AST::MetaNameValueStr &)
{}

void
DefaultResolver::visit (AST::MetaListPaths &)
{}

void
DefaultResolver::visit (AST::MetaListNameValueStr &)
{}

void
DefaultResolver::visit (AST::LiteralPattern &)
{}

void
DefaultResolver::visit (AST::IdentifierPattern &)
{}

void
DefaultResolver::visit (AST::WildcardPattern &)
{}

void
DefaultResolver::visit (AST::RestPattern &)
{}

void
DefaultResolver::visit (AST::RangePatternBoundLiteral &)
{}

void
DefaultResolver::visit (AST::RangePatternBoundPath &)
{}

void
DefaultResolver::visit (AST::RangePatternBoundQualPath &)
{}

void
DefaultResolver::visit (AST::RangePattern &)
{}

void
DefaultResolver::visit (AST::ReferencePattern &)
{}

void
DefaultResolver::visit (AST::StructPatternFieldTuplePat &)
{}

void
DefaultResolver::visit (AST::StructPatternFieldIdentPat &)
{}

void
DefaultResolver::visit (AST::StructPatternFieldIdent &)
{}

void
DefaultResolver::visit (AST::StructPattern &)
{}

void
DefaultResolver::visit (AST::TupleStructItemsNoRange &)
{}

void
DefaultResolver::visit (AST::TupleStructItemsRange &)
{}

void
DefaultResolver::visit (AST::TupleStructPattern &)
{}

void
DefaultResolver::visit (AST::TuplePatternItemsMultiple &)
{}

void
DefaultResolver::visit (AST::TuplePatternItemsRanged &)
{}

void
DefaultResolver::visit (AST::TuplePattern &)
{}

void
DefaultResolver::visit (AST::GroupedPattern &)
{}

void
DefaultResolver::visit (AST::SlicePattern &)
{}

void
DefaultResolver::visit (AST::AltPattern &)
{}

void
DefaultResolver::visit (AST::EmptyStmt &)
{}

void
DefaultResolver::visit (AST::LetStmt &)
{}

void
DefaultResolver::visit (AST::ExprStmt &)
{}

void
DefaultResolver::visit (AST::TraitBound &)
{}

void
DefaultResolver::visit (AST::ImplTraitType &)
{}

void
DefaultResolver::visit (AST::TraitObjectType &)
{}

void
DefaultResolver::visit (AST::ParenthesisedType &)
{}

void
DefaultResolver::visit (AST::ImplTraitTypeOneBound &)
{}

void
DefaultResolver::visit (AST::TraitObjectTypeOneBound &)
{}

void
DefaultResolver::visit (AST::TupleType &)
{}

void
DefaultResolver::visit (AST::NeverType &)
{}

void
DefaultResolver::visit (AST::RawPointerType &)
{}

void
DefaultResolver::visit (AST::ReferenceType &)
{}

void
DefaultResolver::visit (AST::ArrayType &)
{}

void
DefaultResolver::visit (AST::SliceType &)
{}

void
DefaultResolver::visit (AST::InferredType &)
{}

void
DefaultResolver::visit (AST::BareFunctionType &)
{}

} // namespace Resolver2_0
} // namespace Rust
