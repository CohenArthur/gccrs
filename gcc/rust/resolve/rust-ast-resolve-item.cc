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

#include "rust-ast-resolve-item.h"
#include "rust-ast-resolve-path.h"
#include "selftest.h"

namespace Rust {
namespace Resolver {
void
ResolveTraitItems::go (AST::TraitItem *item, const CanonicalPath &prefix,
		       const CanonicalPath &canonical_prefix)
{
  if (item->is_marked_for_strip ())
    return;

  ResolveTraitItems resolver (prefix, canonical_prefix);
  item->accept_vis (resolver);
}

void
ResolveTraitItems::visit (AST::TraitItemType &type)
{
  auto decl = ResolveTraitItemTypeToCanonicalPath::resolve (type);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   type.get_node_id (), cpath);

  for (auto &bound : type.get_type_param_bounds ())
    ResolveTypeBound::go (bound.get (), type.get_node_id ());
}

void
ResolveTraitItems::visit (AST::TraitItemFunc &func)
{
  auto decl = ResolveTraitItemFunctionToCanonicalPath::resolve (func);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   func.get_node_id (), cpath);

  NodeId scope_node_id = func.get_node_id ();
  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->get_label_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  AST::TraitFunctionDecl &function = func.get_trait_function_decl ();
  if (function.has_generics ())
    {
      for (auto &generic : function.get_generic_params ())
	ResolveGenericParam::go (generic.get (), func.get_node_id ());
    }

  if (function.has_return_type ())
    ResolveType::go (function.get_return_type ().get (), func.get_node_id ());

  // we make a new scope so the names of parameters are resolved and shadowed
  // correctly
  for (auto &param : function.get_function_params ())
    {
      ResolveType::go (param.get_type ().get (), param.get_node_id ());
      PatternDeclaration::go (param.get_pattern ().get (),
			      param.get_node_id ());

      // the mutability checker needs to verify for immutable decls the number
      // of assignments are <1. This marks an implicit assignment
      resolver->mark_assignment_to_decl (
	param.get_pattern ()->get_pattern_node_id (), param.get_node_id ());
    }

  if (function.has_where_clause ())
    ResolveWhereClause::Resolve (function.get_where_clause ());

  // trait items have an optional body
  if (func.has_definition ())
    ResolveExpr::go (func.get_definition ().get (), func.get_node_id (), path,
		     cpath);

  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveTraitItems::visit (AST::TraitItemMethod &func)
{
  auto decl = ResolveTraitItemMethodToCanonicalPath::resolve (func);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   func.get_node_id (), cpath);

  NodeId scope_node_id = func.get_node_id ();
  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->get_label_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  AST::TraitMethodDecl &function = func.get_trait_method_decl ();
  if (function.has_generics ())
    {
      for (auto &generic : function.get_generic_params ())
	ResolveGenericParam::go (generic.get (), func.get_node_id ());
    }

  if (function.has_return_type ())
    ResolveType::go (function.get_return_type ().get (), func.get_node_id ());

  // self turns into (self: Self) as a function param
  AST::SelfParam &self_param = function.get_self_param ();
  AST::IdentifierPattern self_pattern (self_param.get_node_id (), "self",
				       self_param.get_locus (),
				       self_param.get_has_ref (),
				       self_param.get_is_mut (),
				       std::unique_ptr<AST::Pattern> (nullptr));

  std::vector<std::unique_ptr<AST::TypePathSegment>> segments;
  segments.push_back (std::unique_ptr<AST::TypePathSegment> (
    new AST::TypePathSegment ("Self", false, self_param.get_locus ())));

  AST::TypePath self_type_path (std::move (segments), self_param.get_locus ());

  ResolveType::go (&self_type_path, self_param.get_node_id ());
  PatternDeclaration::go (&self_pattern, self_param.get_node_id ());

  resolver->mark_assignment_to_decl (self_pattern.get_node_id (),
				     self_pattern.get_node_id ());

  // we make a new scope so the names of parameters are resolved and shadowed
  // correctly
  for (auto &param : function.get_function_params ())
    {
      ResolveType::go (param.get_type ().get (), param.get_node_id ());
      PatternDeclaration::go (param.get_pattern ().get (),
			      param.get_node_id ());

      // the mutability checker needs to verify for immutable decls the number
      // of assignments are <1. This marks an implicit assignment
      resolver->mark_assignment_to_decl (
	param.get_pattern ()->get_pattern_node_id (), param.get_node_id ());
    }

  if (function.has_where_clause ())
    ResolveWhereClause::Resolve (function.get_where_clause ());

  // trait items have an optional body
  if (func.has_definition ())
    ResolveExpr::go (func.get_definition ().get (), func.get_node_id (), path,
		     cpath);

  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveTraitItems::visit (AST::TraitItemConst &constant)
{
  auto decl = ResolveTraitItemConstToCanonicalPath::resolve (constant);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   constant.get_node_id (), cpath);

  ResolveType::go (constant.get_type ().get (), constant.get_node_id ());

  if (constant.has_expr ())
    ResolveExpr::go (constant.get_expr ().get (), constant.get_node_id (), path,
		     cpath);

  // the mutability checker needs to verify for immutable decls the number
  // of assignments are <1. This marks an implicit assignment
  resolver->mark_decl_mutability (constant.get_node_id (), false);
  resolver->mark_assignment_to_decl (constant.get_node_id (),
				     constant.get_node_id ());
}

void
ResolveItem::go (AST::Item *item, const CanonicalPath &prefix,
		 const CanonicalPath &canonical_prefix, NodeId self_id)
{
  ResolveItem resolver (prefix, canonical_prefix, self_id);
  item->accept_vis (resolver);
}

void
ResolveItem::visit (AST::TypeAlias &alias)
{
  auto talias
    = CanonicalPath::new_seg (alias.get_node_id (), alias.get_new_type_name ());
  auto path = prefix.append (talias);
  auto cpath = canonical_prefix.append (talias);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   alias.get_node_id (), cpath);

  NodeId scope_node_id = alias.get_node_id ();
  resolver->get_type_scope ().push (scope_node_id);

  if (alias.has_generics ())
    {
      for (auto &generic : alias.get_generic_params ())
	ResolveGenericParam::go (generic.get (), alias.get_node_id ());
    }

  if (alias.has_where_clause ())
    ResolveWhereClause::Resolve (alias.get_where_clause ());

  ResolveType::go (alias.get_type_aliased ().get (), alias.get_node_id ());

  resolver->get_type_scope ().pop ();
}

void
ResolveItem::visit (AST::Module &module)
{
  auto mod = CanonicalPath::new_seg (module.get_node_id (), module.get_name ());
  auto path = prefix.append (mod);
  auto cpath = canonical_prefix.append (mod);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   module.get_node_id (), cpath);

  resolve_visibility (module.get_visibility (), self_id);

  NodeId module_id = module.get_node_id ();
  resolver->get_name_scope ().push (module_id);
  resolver->get_type_scope ().push (module_id);
  resolver->get_label_scope ().push (module_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  for (auto &item : module.get_items ())
    ResolveTopLevel::go (item.get (), CanonicalPath::create_empty (), cpath);

  auto old_id = self_id;

  mappings->insert_module_child (old_id, self_id);
  mappings->insert_module_super (self_id, old_id);

  self_id = module_id;

  for (auto &item : module.get_items ())
    ResolveItem::go (item.get (), path, cpath, module_id);

  self_id = old_id;

  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveItem::visit (AST::TupleStruct &struct_decl)
{
  auto decl = CanonicalPath::new_seg (struct_decl.get_node_id (),
				      struct_decl.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   struct_decl.get_node_id (), cpath);

  resolve_visibility (struct_decl.get_visibility (), self_id);

  NodeId scope_node_id = struct_decl.get_node_id ();
  resolver->get_type_scope ().push (scope_node_id);

  if (struct_decl.has_generics ())
    {
      for (auto &generic : struct_decl.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), struct_decl.get_node_id ());
	}
    }

  if (struct_decl.has_where_clause ())
    ResolveWhereClause::Resolve (struct_decl.get_where_clause ());

  for (AST::TupleField &field : struct_decl.get_fields ())
    {
      if (field.get_field_type ()->is_marked_for_strip ())
	continue;

      resolve_visibility (field.get_visibility (), self_id);

      ResolveType::go (field.get_field_type ().get (),
		       struct_decl.get_node_id ());
    }

  resolver->get_type_scope ().pop ();
}

void
ResolveItem::visit (AST::Enum &enum_decl)
{
  auto decl = CanonicalPath::new_seg (enum_decl.get_node_id (),
				      enum_decl.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   enum_decl.get_node_id (), cpath);

  resolve_visibility (enum_decl.get_visibility (), self_id);

  NodeId scope_node_id = enum_decl.get_node_id ();
  resolver->get_type_scope ().push (scope_node_id);

  if (enum_decl.has_generics ())
    {
      for (auto &generic : enum_decl.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), enum_decl.get_node_id ());
	}
    }

  if (enum_decl.has_where_clause ())
    ResolveWhereClause::Resolve (enum_decl.get_where_clause ());

  /* The actual fields are inside the variants.  */
  for (auto &variant : enum_decl.get_variants ())
    // FIXME: Is `self_id` really necessary here? Test out if `self` makes sense
    // inside an Enum's items
    ResolveItem::go (variant.get (), path, cpath, scope_node_id);

  resolver->get_type_scope ().pop ();
}

/* EnumItem doesn't need to be handled, no fields.  */
void
ResolveItem::visit (AST::EnumItem &item)
{
  // Since at this point we cannot have visibilities on enum items anymore, we
  // can skip handling them

  auto decl
    = CanonicalPath::new_seg (item.get_node_id (), item.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   item.get_node_id (), cpath);
}

void
ResolveItem::visit (AST::EnumItemTuple &item)
{
  auto decl
    = CanonicalPath::new_seg (item.get_node_id (), item.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   item.get_node_id (), cpath);

  for (auto &field : item.get_tuple_fields ())
    {
      if (field.get_field_type ()->is_marked_for_strip ())
	continue;

      ResolveType::go (field.get_field_type ().get (), item.get_node_id ());
    }
}

void
ResolveItem::visit (AST::EnumItemStruct &item)
{
  auto decl
    = CanonicalPath::new_seg (item.get_node_id (), item.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   item.get_node_id (), cpath);

  for (auto &field : item.get_struct_fields ())
    {
      if (field.get_field_type ()->is_marked_for_strip ())
	continue;

      ResolveType::go (field.get_field_type ().get (), item.get_node_id ());
    }
}

void
ResolveItem::visit (AST::EnumItemDiscriminant &item)
{
  auto decl
    = CanonicalPath::new_seg (item.get_node_id (), item.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);

  mappings->insert_canonical_path (mappings->get_current_crate (),
				   item.get_node_id (), cpath);
}

void
ResolveItem::visit (AST::StructStruct &struct_decl)
{
  auto decl = CanonicalPath::new_seg (struct_decl.get_node_id (),
				      struct_decl.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   struct_decl.get_node_id (), cpath);

  resolve_visibility (struct_decl.get_visibility (), self_id);

  NodeId scope_node_id = struct_decl.get_node_id ();
  resolver->get_type_scope ().push (scope_node_id);

  if (struct_decl.has_generics ())
    {
      for (auto &generic : struct_decl.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), struct_decl.get_node_id ());
	}
    }

  if (struct_decl.has_where_clause ())
    ResolveWhereClause::Resolve (struct_decl.get_where_clause ());

  for (AST::StructField &field : struct_decl.get_fields ())
    {
      if (field.get_field_type ()->is_marked_for_strip ())
	continue;

      resolve_visibility (field.get_visibility (), self_id);

      ResolveType::go (field.get_field_type ().get (),
		       struct_decl.get_node_id ());
    }

  resolver->get_type_scope ().pop ();
}

void
ResolveItem::visit (AST::Union &union_decl)
{
  auto decl = CanonicalPath::new_seg (union_decl.get_node_id (),
				      union_decl.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   union_decl.get_node_id (), cpath);

  resolve_visibility (union_decl.get_visibility (), self_id);

  NodeId scope_node_id = union_decl.get_node_id ();
  resolver->get_type_scope ().push (scope_node_id);

  if (union_decl.has_generics ())
    {
      for (auto &generic : union_decl.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), union_decl.get_node_id ());
	}
    }

  if (union_decl.has_where_clause ())
    ResolveWhereClause::Resolve (union_decl.get_where_clause ());

  for (AST::StructField &field : union_decl.get_variants ())
    {
      if (field.get_field_type ()->is_marked_for_strip ())
	continue;

      ResolveType::go (field.get_field_type ().get (),
		       union_decl.get_node_id ());
    }

  resolver->get_type_scope ().pop ();
}

void
ResolveItem::visit (AST::StaticItem &var)
{
  auto decl
    = CanonicalPath::new_seg (var.get_node_id (), var.get_identifier ());
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   var.get_node_id (), cpath);

  ResolveType::go (var.get_type ().get (), var.get_node_id ());
  ResolveExpr::go (var.get_expr ().get (), var.get_node_id (), path, cpath);

  // the mutability checker needs to verify for immutable decls the number
  // of assignments are <1. This marks an implicit assignment
  resolver->mark_assignment_to_decl (var.get_node_id (), var.get_node_id ());
}

void
ResolveItem::visit (AST::ConstantItem &constant)
{
  auto decl = ResolveConstantItemToCanonicalPath::resolve (constant);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   constant.get_node_id (), cpath);

  resolve_visibility (constant.get_visibility (), self_id);

  ResolveType::go (constant.get_type ().get (), constant.get_node_id ());
  ResolveExpr::go (constant.get_expr ().get (), constant.get_node_id (), path,
		   cpath);

  // the mutability checker needs to verify for immutable decls the number
  // of assignments are <1. This marks an implicit assignment
  resolver->mark_decl_mutability (constant.get_node_id (), false);
  resolver->mark_assignment_to_decl (constant.get_node_id (),
				     constant.get_node_id ());
}

void
ResolveItem::visit (AST::Function &function)
{
  auto decl = ResolveFunctionItemToCanonicalPath::resolve (function);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   function.get_node_id (), cpath);

  resolve_visibility (function.get_visibility (), self_id);

  NodeId scope_node_id = function.get_node_id ();
  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->get_label_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  if (function.has_generics ())
    {
      for (auto &generic : function.get_generic_params ())
	ResolveGenericParam::go (generic.get (), function.get_node_id ());
    }

  // resolve any where clause items
  if (function.has_where_clause ())
    ResolveWhereClause::Resolve (function.get_where_clause ());

  if (function.has_return_type ())
    ResolveType::go (function.get_return_type ().get (),
		     function.get_node_id ());

  // we make a new scope so the names of parameters are resolved and shadowed
  // correctly
  for (auto &param : function.get_function_params ())
    {
      ResolveType::go (param.get_type ().get (), param.get_node_id ());
      PatternDeclaration::go (param.get_pattern ().get (),
			      param.get_node_id ());

      // the mutability checker needs to verify for immutable decls the number
      // of assignments are <1. This marks an implicit assignment
      resolver->mark_assignment_to_decl (
	param.get_pattern ()->get_pattern_node_id (), param.get_node_id ());
    }

  // resolve the function body
  ResolveExpr::go (function.get_definition ().get (), function.get_node_id (),
		   path, cpath);

  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveItem::visit (AST::InherentImpl &impl_block)
{
  NodeId scope_node_id = impl_block.get_node_id ();
  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());

  resolve_visibility (impl_block.get_visibility (), self_id);

  if (impl_block.has_generics ())
    {
      for (auto &generic : impl_block.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), impl_block.get_node_id ());
	}
    }

  // resolve any where clause items
  if (impl_block.has_where_clause ())
    ResolveWhereClause::Resolve (impl_block.get_where_clause ());

  // FIXME this needs to be protected behind nominal type-checks see:
  // rustc --explain E0118

  CanonicalPath self_cpath = CanonicalPath::create_empty ();
  bool canonicalize_type_with_generics = false;
  NodeId resolved_node
    = ResolveType::go (impl_block.get_type ().get (), impl_block.get_node_id (),
		       canonicalize_type_with_generics, &self_cpath);
  if (resolved_node == UNKNOWN_NODEID)
    {
      resolver->get_type_scope ().pop ();
      resolver->get_name_scope ().pop ();
      return;
    }

  // Setup paths
  bool canonicalize_type_args = !impl_block.has_generics ();
  bool type_resolve_generic_args = false;

  CanonicalPath impl_type
    = ResolveTypeToCanonicalPath::resolve (*impl_block.get_type ().get (),
					   canonicalize_type_args,
					   type_resolve_generic_args);
  CanonicalPath impl_prefix = prefix.append (impl_type);

  // see https://godbolt.org/z/a3vMbsT6W
  CanonicalPath cpath = CanonicalPath::create_empty ();
  if (canonical_prefix.size () <= 1)
    {
      cpath = self_cpath;
    }
  else
    {
      std::string seg_buf = "<impl " + self_cpath.get () + ">";
      CanonicalPath seg
	= CanonicalPath::new_seg (impl_block.get_node_id (), seg_buf);
      cpath = canonical_prefix.append (seg);
    }
  // done setup paths

  auto Self
    = CanonicalPath::get_big_self (impl_block.get_type ()->get_node_id ());

  resolver->get_type_scope ().insert (Self,
				      impl_block.get_type ()->get_node_id (),
				      impl_block.get_type ()->get_locus ());

  for (auto &impl_item : impl_block.get_impl_items ())
    {
      resolve_impl_item (impl_item.get (), impl_prefix, cpath);
    }

  resolver->get_type_scope ().peek ()->clear_name (
    Self, impl_block.get_type ()->get_node_id ());

  resolver->get_type_scope ().pop ();
  resolver->get_name_scope ().pop ();
}

void
ResolveItem::visit (AST::Method &method)
{
  auto decl = ResolveMethodItemToCanonicalPath::resolve (method);
  auto path = prefix.append (decl);
  auto cpath = canonical_prefix.append (decl);
  mappings->insert_canonical_path (mappings->get_current_crate (),
				   method.get_node_id (), cpath);

  NodeId scope_node_id = method.get_node_id ();

  resolve_visibility (method.get_visibility (), self_id);

  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->get_label_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  if (method.has_generics ())
    {
      for (auto &generic : method.get_generic_params ())
	ResolveGenericParam::go (generic.get (), method.get_node_id ());
    }

  // resolve any where clause items
  if (method.has_where_clause ())
    ResolveWhereClause::Resolve (method.get_where_clause ());

  if (method.has_return_type ())
    ResolveType::go (method.get_return_type ().get (), method.get_node_id ());

  // self turns into (self: Self) as a function param
  AST::SelfParam &self_param = method.get_self_param ();
  AST::IdentifierPattern self_pattern (self_param.get_node_id (), "self",
				       self_param.get_locus (),
				       self_param.get_has_ref (),
				       self_param.get_is_mut (),
				       std::unique_ptr<AST::Pattern> (nullptr));

  std::vector<std::unique_ptr<AST::TypePathSegment>> segments;
  segments.push_back (std::unique_ptr<AST::TypePathSegment> (
    new AST::TypePathSegment ("Self", false, self_param.get_locus ())));

  AST::TypePath self_type_path (std::move (segments), self_param.get_locus ());

  ResolveType::go (&self_type_path, self_param.get_node_id ());
  PatternDeclaration::go (&self_pattern, self_param.get_node_id ());

  resolver->mark_assignment_to_decl (self_pattern.get_node_id (),
				     self_pattern.get_node_id ());

  // we make a new scope so the names of parameters are resolved and shadowed
  // correctly
  for (auto &param : method.get_function_params ())
    {
      ResolveType::go (param.get_type ().get (), param.get_node_id ());
      PatternDeclaration::go (param.get_pattern ().get (),
			      param.get_node_id ());

      // the mutability checker needs to verify for immutable decls the number
      // of assignments are <1. This marks an implicit assignment
      resolver->mark_assignment_to_decl (
	param.get_pattern ()->get_pattern_node_id (), param.get_node_id ());
    }

  // resolve any where clause items
  if (method.has_where_clause ())
    ResolveWhereClause::Resolve (method.get_where_clause ());

  // resolve the function body
  ResolveExpr::go (method.get_definition ().get (), method.get_node_id (), path,
		   cpath);

  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveItem::visit (AST::TraitImpl &impl_block)
{
  NodeId scope_node_id = impl_block.get_node_id ();

  resolve_visibility (impl_block.get_visibility (), self_id);

  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());

  if (impl_block.has_generics ())
    {
      for (auto &generic : impl_block.get_generic_params ())
	{
	  ResolveGenericParam::go (generic.get (), impl_block.get_node_id ());
	}
    }

  // resolve any where clause items
  if (impl_block.has_where_clause ())
    ResolveWhereClause::Resolve (impl_block.get_where_clause ());

  CanonicalPath canonical_trait_type = CanonicalPath::create_empty ();
  bool canonicalize_type_with_generics = false;
  NodeId trait_resolved_node
    = ResolveType::go (&impl_block.get_trait_path (), impl_block.get_node_id (),
		       canonicalize_type_with_generics, &canonical_trait_type);
  if (trait_resolved_node == UNKNOWN_NODEID)
    {
      resolver->get_type_scope ().pop ();
      resolver->get_name_scope ().pop ();
      return;
    }

  CanonicalPath canonical_impl_type = CanonicalPath::create_empty ();
  NodeId type_resolved_node
    = ResolveType::go (impl_block.get_type ().get (), impl_block.get_node_id (),
		       canonicalize_type_with_generics, &canonical_impl_type);
  if (type_resolved_node == UNKNOWN_NODEID)
    {
      resolver->get_type_scope ().pop ();
      resolver->get_name_scope ().pop ();
      return;
    }

  // setup paths
  bool canonicalize_type_args = !impl_block.has_generics ();
  bool type_resolve_generic_args = false;

  CanonicalPath impl_type_seg
    = ResolveTypeToCanonicalPath::resolve (*impl_block.get_type ().get (),
					   canonicalize_type_args,
					   type_resolve_generic_args);
  CanonicalPath trait_type_seg
    = ResolveTypeToCanonicalPath::resolve (impl_block.get_trait_path (),
					   canonicalize_type_args,
					   type_resolve_generic_args);

  CanonicalPath projection
    = TraitImplProjection::resolve (impl_block.get_node_id (), trait_type_seg,
				    impl_type_seg);
  CanonicalPath impl_prefix = prefix.append (projection);

  // setup canonical-path
  CanonicalPath canonical_projection
    = TraitImplProjection::resolve (impl_block.get_node_id (),
				    canonical_trait_type, canonical_impl_type);
  CanonicalPath cpath = CanonicalPath::create_empty ();
  if (canonical_prefix.size () <= 1)
    {
      cpath = canonical_projection;
    }
  else
    {
      std::string projection_str = canonical_projection.get ();
      std::string seg_buf
	= "<impl " + projection_str.substr (1, projection_str.size () - 2)
	  + ">";
      CanonicalPath seg
	= CanonicalPath::new_seg (impl_block.get_node_id (), seg_buf);
      cpath = canonical_prefix.append (seg);
    }

  // DONE setup canonical-path

  auto Self
    = CanonicalPath::get_big_self (impl_block.get_type ()->get_node_id ());

  resolver->get_type_scope ().insert (Self,
				      impl_block.get_type ()->get_node_id (),
				      impl_block.get_type ()->get_locus ());

  for (auto &impl_item : impl_block.get_impl_items ())
    {
      resolve_impl_item (impl_item.get (), impl_prefix, cpath);
    }

  resolver->get_type_scope ().peek ()->clear_name (
    Self, impl_block.get_type ()->get_node_id ());
  resolver->get_type_scope ().pop ();
}

void
ResolveItem::visit (AST::Trait &trait)
{
  NodeId scope_node_id = trait.get_node_id ();

  resolve_visibility (trait.get_visibility (), self_id);

  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());

  // we need to inject an implicit self TypeParam here
  AST::TypeParam *implicit_self
    = new AST::TypeParam ("Self", trait.get_locus ());
  trait.insert_implict_self (
    std::unique_ptr<AST::GenericParam> (implicit_self));
  CanonicalPath Self = CanonicalPath::get_big_self (trait.get_node_id ());

  for (auto &generic : trait.get_generic_params ())
    {
      ResolveGenericParam::go (generic.get (), trait.get_node_id ());
    }

  // Self is an implicit TypeParam so lets mark it as such
  resolver->get_type_scope ().append_reference_for_def (
    Self.get_node_id (), implicit_self->get_node_id ());

  if (trait.has_type_param_bounds ())
    {
      for (auto &bound : trait.get_type_param_bounds ())
	{
	  ResolveTypeBound::go (bound.get (), trait.get_node_id ());
	}
    }

  // resolve any where clause items
  if (trait.has_where_clause ())
    ResolveWhereClause::Resolve (trait.get_where_clause ());

  // resolve the paths
  CanonicalPath path = CanonicalPath::create_empty ();
  CanonicalPath cpath = CanonicalPath::create_empty ();
  //

  for (auto &item : trait.get_trait_items ())
    {
      ResolveTraitItems::go (item.get (), path, cpath);
    }

  resolver->get_type_scope ().pop ();
  resolver->get_name_scope ().pop ();
}

void
ResolveItem::visit (AST::ExternBlock &extern_block)
{
  resolve_visibility (extern_block.get_visibility (), self_id);

  for (auto &item : extern_block.get_extern_items ())
    {
      resolve_extern_item (item.get ());
    }
}

static void
flatten_glob (const AST::UseTreeGlob &glob,
	      std::vector<AST::SimplePath> &paths);
static void
flatten_rebind (const AST::UseTreeRebind &glob,
		std::vector<AST::SimplePath> &paths);
static void
flatten_list (const AST::UseTreeList &glob,
	      std::vector<AST::SimplePath> &paths);

static void
flatten (const AST::UseTree *tree, std::vector<AST::SimplePath> &paths)
{
  switch (tree->get_kind ())
    {
      case AST::UseTree::Glob: {
	auto glob = static_cast<const AST::UseTreeGlob *> (tree);
	flatten_glob (*glob, paths);
	break;
      }
      case AST::UseTree::Rebind: {
	auto rebind = static_cast<const AST::UseTreeRebind *> (tree);
	flatten_rebind (*rebind, paths);
	break;
      }
      case AST::UseTree::List: {
	auto list = static_cast<const AST::UseTreeList *> (tree);
	flatten_list (*list, paths);
	break;
      }
      break;
    }
}

static void
flatten_glob (const AST::UseTreeGlob &glob, std::vector<AST::SimplePath> &paths)
{
  if (glob.has_path ())
    paths.emplace_back (glob.get_path ());
}

static void
flatten_rebind (const AST::UseTreeRebind &rebind,
		std::vector<AST::SimplePath> &paths)
{
  auto path = rebind.get_path ();
  if (rebind.has_path ())
    paths.emplace_back (path);

  // FIXME: Do we want to emplace the rebind here as well?
  if (rebind.has_identifier ())
    {
      auto rebind_path = path;
      auto new_seg = rebind.get_identifier ();

      // Add the identifier as a new path
      rebind_path.get_segments ().back ()
	= AST::SimplePathSegment (new_seg, Location ());

      paths.emplace_back (rebind_path);
    }
}

static void
flatten_list (const AST::UseTreeList &list, std::vector<AST::SimplePath> &paths)
{
  auto prefix = AST::SimplePath::create_empty ();
  if (list.has_path ())
    prefix = list.get_path ();

  for (const auto &tree : list.get_trees ())
    {
      auto sub_paths = std::vector<AST::SimplePath> ();
      flatten (tree.get (), sub_paths);

      for (auto &sub_path : sub_paths)
	{
	  auto new_path = prefix;
	  std::copy (sub_path.get_segments ().begin (),
		     sub_path.get_segments ().end (),
		     std::back_inserter (new_path.get_segments ()));

	  paths.emplace_back (new_path);
	}
    }
}

/**
 * Flatten a UseDeclaration's UseTree into multiple simple paths to resolve.
 *
 * Given the following use declarations:
 * ```
 * use some::path::to_resolve; #1
 * use some::path::to_glob::*; #2
 * use some::path::{one, two}; #2
 * ```
 *
 * In the first case, we simply want to return a vector with a single
 * SimplePath:
 * [some::path::to_resolve]
 *
 * In the second case, we want to resolve the glob's "origin path":
 * [some::path::to_glob]
 *
 * Finally in the third case, we want to create two SimplePaths to resolve:
 * [some::path::one, some::path::two]
 */
static std::vector<AST::SimplePath>
flatten_use_dec_to_paths (const AST::UseDeclaration &use_item)
{
  auto paths = std::vector<AST::SimplePath> ();

  const auto &tree = use_item.get_tree ();
  flatten (tree.get (), paths);

  return paths;
}

void
ResolveItem::visit (AST::UseDeclaration &use_item)
{
  auto to_resolve = flatten_use_dec_to_paths (use_item);

  for (auto &path : to_resolve)
    ResolvePath::go (&path, parent, self_id);
}

void
ResolveImplItems::go (AST::InherentImplItem *item, const CanonicalPath &prefix,
		      const CanonicalPath &canonical_prefix, NodeId self_id)
{
  if (item->is_marked_for_strip ())
    return;

  ResolveImplItems resolver (prefix, canonical_prefix, self_id);
  item->accept_vis (resolver);
}

void
ResolveImplItems::go (AST::TraitImplItem *item, const CanonicalPath &prefix,
		      const CanonicalPath &canonical_prefix, NodeId self_id)
{
  if (item->is_marked_for_strip ())
    return;

  ResolveImplItems resolver (prefix, canonical_prefix, self_id);
  item->accept_vis (resolver);
}

void
ResolveImplItems::visit (AST::TypeAlias &alias)
{
  ResolveItem::visit (alias);

  resolve_visibility (alias.get_visibility (), self_id);

  // FIXME this stops the erronious unused decls which will be fixed later on
  resolver->get_type_scope ().append_reference_for_def (alias.get_node_id (),
							alias.get_node_id ());
}

void
ResolveExternItem::go (AST::ExternalItem *item)
{
  ResolveExternItem resolver;
  item->accept_vis (resolver);
}

void
ResolveExternItem::visit (AST::ExternalFunctionItem &function)
{
  NodeId scope_node_id = function.get_node_id ();

  resolve_visibility (function.get_visibility (), self_id);

  resolver->get_name_scope ().push (scope_node_id);
  resolver->get_type_scope ().push (scope_node_id);
  resolver->get_label_scope ().push (scope_node_id);
  resolver->push_new_name_rib (resolver->get_name_scope ().peek ());
  resolver->push_new_type_rib (resolver->get_type_scope ().peek ());
  resolver->push_new_label_rib (resolver->get_type_scope ().peek ());

  // resolve the generics
  if (function.has_generics ())
    {
      for (auto &generic : function.get_generic_params ())
	ResolveGenericParam::go (generic.get (), function.get_node_id ());
    }

  if (function.has_return_type ())
    ResolveType::go (function.get_return_type ().get (),
		     function.get_node_id ());

  // we make a new scope so the names of parameters are resolved and shadowed
  // correctly
  for (auto &param : function.get_function_params ())
    {
      ResolveType::go (param.get_type ().get (), param.get_node_id ());
    }

  // done
  resolver->get_name_scope ().pop ();
  resolver->get_type_scope ().pop ();
  resolver->get_label_scope ().pop ();
}

void
ResolveExternItem::visit (AST::ExternalStaticItem &item)
{
  resolve_visibility (item.get_visibility (), self_id);

  ResolveType::go (item.get_type ().get (), item.get_node_id ());
}

} // namespace Resolver
} // namespace Rust

#if CHECKING_P

namespace selftest {

static void
rust_flatten_nested_glob (void)
{
  auto foo = Rust::AST::SimplePathSegment ("foo", Location ());
  auto bar = Rust::AST::SimplePathSegment ("bar", Location ());
  auto foobar = Rust::AST::SimplePath ({foo, bar});

  auto glob
    = Rust::AST::UseTreeGlob (Rust::AST::UseTreeGlob::PathType::PATH_PREFIXED,
			      foobar, Location ());

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_glob (glob, paths);

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 1);
  ASSERT_EQ (paths[0].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[0].get_segments ()[1].as_string (), "bar");
}

static void
rust_flatten_glob (void)
{
  auto frob = Rust::AST::SimplePath::from_str ("frobulator", Location ());

  auto glob
    = Rust::AST::UseTreeGlob (Rust::AST::UseTreeGlob::PathType::PATH_PREFIXED,
			      frob, Location ());

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_glob (glob, paths);

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 1);
  ASSERT_EQ (paths[0], "frobulator");
}

static void
rust_flatten_rebind_none (void)
{
  auto foo = Rust::AST::SimplePathSegment ("foo", Location ());
  auto bar = Rust::AST::SimplePathSegment ("bar", Location ());
  auto foobar = Rust::AST::SimplePath ({foo, bar});

  auto rebind = Rust::AST::UseTreeRebind (Rust::AST::UseTreeRebind::NONE,
					  foobar, Location ());

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_rebind (rebind, paths);

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 1);
  ASSERT_EQ (paths[0].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[0].get_segments ()[1].as_string (), "bar");
}

static void
rust_flatten_rebind (void)
{
  auto frob = Rust::AST::SimplePath::from_str ("frobulator", Location ());

  auto rebind = Rust::AST::UseTreeRebind (Rust::AST::UseTreeRebind::IDENTIFIER,
					  frob, Location (), "saindoux");

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_rebind (rebind, paths);

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 2);
  ASSERT_EQ (paths[0], "frobulator");
  ASSERT_EQ (paths[1], "saindoux");
}

static void
rust_flatten_rebind_nested (void)
{
  auto foo = Rust::AST::SimplePathSegment ("foo", Location ());
  auto bar = Rust::AST::SimplePathSegment ("bar", Location ());
  auto baz = Rust::AST::SimplePathSegment ("baz", Location ());

  auto foo_bar_baz = Rust::AST::SimplePath ({foo, bar, baz});

  auto rebind = Rust::AST::UseTreeRebind (Rust::AST::UseTreeRebind::IDENTIFIER,
					  foo_bar_baz, Location (), "saindoux");

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_rebind (rebind, paths);

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 2);
  ASSERT_EQ (paths[0].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[0].get_segments ()[1].as_string (), "bar");
  ASSERT_EQ (paths[0].get_segments ()[2].as_string (), "baz");
  ASSERT_EQ (paths[1].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[1].get_segments ()[1].as_string (), "bar");
  ASSERT_EQ (paths[1].get_segments ()[2].as_string (), "saindoux");
}

static void
rust_flatten_list (void)
{
  auto foo = Rust::AST::SimplePathSegment ("foo", Location ());
  auto bar = Rust::AST::SimplePathSegment ("bar", Location ());
  auto foo_bar = Rust::AST::SimplePath ({foo, bar});

  auto baz = Rust::AST::SimplePath::from_str ("baz", Location ());
  auto bul = Rust::AST::SimplePath::from_str ("bul", Location ());

  // use foo::bar::{baz, bul};

  auto use0 = std::unique_ptr<Rust::AST::UseTree> (
    new Rust::AST::UseTreeRebind (Rust::AST::UseTreeRebind::NONE, baz,
				  Location ()));
  auto use1 = std::unique_ptr<Rust::AST::UseTree> (
    new Rust::AST::UseTreeRebind (Rust::AST::UseTreeRebind::NONE, bul,
				  Location ()));

  auto uses = std::vector<std::unique_ptr<Rust::AST::UseTree>> ();
  uses.emplace_back (std::move (use0));
  uses.emplace_back (std::move (use1));

  auto list = Rust::AST::UseTreeList (Rust::AST::UseTreeList::PATH_PREFIXED,
				      foo_bar, std::move (uses), Location ());

  auto paths = std::vector<Rust::AST::SimplePath> ();
  Rust::Resolver::flatten_list (list, paths);

  for (auto &path : paths)
    fprintf (stderr, "%s\n", path.as_string ().c_str ());

  ASSERT_TRUE (!paths.empty ());
  ASSERT_EQ (paths.size (), 2);
  ASSERT_EQ (paths[0].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[0].get_segments ()[1].as_string (), "bar");
  ASSERT_EQ (paths[0].get_segments ()[2].as_string (), "baz");
  ASSERT_EQ (paths[1].get_segments ()[0].as_string (), "foo");
  ASSERT_EQ (paths[1].get_segments ()[1].as_string (), "bar");
  ASSERT_EQ (paths[1].get_segments ()[2].as_string (), "bul");
}

static void
rust_use_dec_flattening (void)
{
  rust_flatten_glob ();
  rust_flatten_nested_glob ();
  rust_flatten_rebind_none ();
  rust_flatten_rebind ();
  rust_flatten_rebind_nested ();
  rust_flatten_list ();
}

void
rust_simple_path_resolve_test (void)
{
  rust_use_dec_flattening ();
}
} // namespace selftest

#endif // CHECKING_P
