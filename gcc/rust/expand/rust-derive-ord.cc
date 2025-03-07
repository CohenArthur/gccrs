// Copyright (C) 2025 Free Software Foundation, Inc.

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

#include "rust-derive-ord.h"
#include "rust-ast-dump.h"
#include "rust-ast.h"
#include "rust-derive.h"
#include "rust-item.h"

namespace Rust {
namespace AST {

DeriveOrd::DeriveOrd (Ordering ordering, location_t loc)
  : DeriveVisitor (loc), ordering (ordering)
{}

std::unique_ptr<Item>
DeriveOrd::go (Item &item)
{
  item.accept_vis (*this);

  AST::Dump::debug (*expanded);

  return std::move (expanded);
}

std::unique_ptr<Item>
DeriveOrd::cmp_impl (
  std::unique_ptr<AssociatedItem> &&cmp_fn, Identifier type_name,
  const std::vector<std::unique_ptr<GenericParam>> &type_generics)
{
  auto trait = ordering == Ordering::Partial ? "PartialOrd" : "Ord";
  auto trait_path = builder.type_path ({"core", "cmp", trait}, true);

  auto trait_bound
    = builder.trait_bound (builder.type_path ({"core", "cmp", trait}, true));

  auto trait_items = vec (std::move (cmp_fn));

  auto cmp_generics
    = setup_impl_generics (type_name.as_string (), type_generics,
			   std::move (trait_bound));

  return builder.trait_impl (trait_path, std::move (cmp_generics.self_type),
			     std::move (trait_items),
			     std::move (cmp_generics.impl));
}

std::unique_ptr<AssociatedItem>
DeriveOrd::cmp_fn (std::unique_ptr<BlockExpr> &&block, Identifier type_name)
{
  // auto return_ty = ordering == Ordering::Total
  // ? builder.type_path_segment_generic ({"core", "option", "Option"}, true)

  // Ordering
  auto return_type = builder.type_path ({"core", "cmp", "Ordering"}, true);

  // In the case of PartialOrd, we return an Option<Ordering>
  if (ordering == Ordering::Partial)
    {
      auto generic = GenericArg::create_type (ptrify (return_type));

      auto generic_seg = builder.type_path_segment_generic (
	"Option", GenericArgs ({}, {generic}, {}, loc));
      auto core = builder.type_path_segment ("core");
      auto option = builder.type_path_segment ("option");

      return_type
	= builder.type_path (vec (std::move (core), std::move (option),
				  std::move (generic_seg)),
			     true);
    }

  // &self, other: &Self
  auto params = vec (
    builder.self_ref_param (),
    builder.function_param (builder.identifier_pattern ("other"),
			    builder.reference_type (ptrify (
			      builder.type_path (type_name.as_string ())))));

  auto function_name = ordering == Ordering::Partial ? "partial_cmp" : "cmp";

  return builder.function (function_name, std::move (params),
			   ptrify (return_type), std::move (block));
}

std::unique_ptr<Expr>
recursive_match ()
{
  return nullptr;
}

void
DeriveOrd::visit_struct (StructStruct &item)
{
  // FIXME: Put cmp_fn call inside cmp_impl, pass a block to cmp_impl instead -
  // this avoids repeating the same parameter twice (the type name)
  expanded = cmp_impl (cmp_fn (builder.block (), item.get_identifier ()),
		       item.get_identifier (), item.get_generic_params ());
}

void
DeriveOrd::visit_tuple (TupleStruct &item)
{}

void
DeriveOrd::visit_enum (Enum &item)
{}

void
DeriveOrd::visit_union (Union &item)
{
  if (ordering == Ordering::Total)
    rust_error_at (item.get_locus (), "derive(Ord) cannot be used on unions");
  else
    rust_error_at (item.get_locus (),
		   "derive(PartialOrd) cannot be used on unions");
}

} // namespace AST
} // namespace Rust
