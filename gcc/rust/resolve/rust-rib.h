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

#ifndef RUST_RIB_H
#define RUST_RIB_H

#include "rust-system.h"
#include "rust-ast.h"
#include "optional.h"
#include "expected.h"

namespace Rust {
namespace Resolver2_0 {

/**
 * All namespaces that Rust's name resolution needs to handle
 */
enum class Namespace
{
  /* */
  Values,
  /* */
  Types,
  Labels,
  Macros,
};

class Rib
{
  // when entering a function, we have to push multiple ribs: 1 for types, one
  // for values:
  // 1. types for generic type arguments
  // 2. values for the function's arguments
  // if we enter a closure for example, we only push one: values - there are no
  // generic arguments, only generic uses.

  // FIXME: Remove
  /// The rib kind restricts certain accesses,
  /// e.g. to a `Res::Local` of an outer item.
  // #[derive(Copy, Clone, Debug)]
  // crate enum RibKind<'a> {
  //     /// No restriction needs to be applied.
  //     NormalRibKind,
  //
  //     /// We passed through an impl or trait and are now in one of its
  //     /// methods or associated types. Allow references to ty params that
  //     impl or trait
  //     /// binds. Disallow any other upvars (including other ty params that
  //     are
  //     /// upvars).
  //     AssocItemRibKind,
  //
  //     /// We passed through a closure. Disallow labels.
  //     ClosureOrAsyncRibKind,
  //
  //     /// We passed through a function definition. Disallow upvars.
  //     /// Permit only those const parameters that are specified in the
  //     /// function's generics.
  //     FnItemRibKind,
  //
  //     /// We passed through an item scope. Disallow upvars.
  //     ItemRibKind(HasGenericParams),
  //
  //     /// We're in a constant item. Can't refer to dynamic stuff.
  //     ///
  //     /// The `bool` indicates if this constant may reference generic
  //     parameters
  //     /// and is used to only allow generic parameters to be used in trivial
  //     /// constant expressions.
  //     ConstantItemRibKind(bool),
  //
  //     /// We passed through a module.
  //     ModuleRibKind(Module<'a>),
  //
  //     /// We passed through a `macro_rules!` statement
  //     MacroDefinition(DefId),
  //
  //     /// All bindings in this rib are type parameters that can't be used
  //     /// from the default of a type parameter because they're not declared
  //     /// before said type parameter. Also see the `visit_generics` override.
  //     ForwardTyParamBanRibKind,
  //
  //     /// We are inside of the type of a const parameter. Can't refer to any
  //     /// parameters.
  //     ConstParamTyRibKind,
  // }

public:
  // TODO: A Rib contains a `kind` and `bindings`, which is an `IdentMap` in
  // rustc - which is just a `Hashmap<Identifier, T>`
  enum class Kind
  {
    Normal,
    ConstantItem, // -> boolean
    Module,
    Function,
    /* Const parameter ? Like... Constant item? Or Const generic? */
    ConstParamType,
  };

  Rib (Kind kind);
  Rib (Kind kind, Identifier identifier, NodeId id);
  Rib (Kind kind, std::unordered_map<Identifier, NodeId> values);

  // FIXME: What's the behavior if the key already exists?
  // Okay based on RibKind?
  // FIXME: Not void and void
  tl::expected<void, std::string> insert (Identifier name, NodeId id);
  tl::optional<NodeId> get (const Identifier &name);

  const std::unordered_map<Identifier, NodeId> &get_values () const;

private:
  Kind kind;
  std::unordered_map<Identifier, NodeId> values;
};

} // namespace Resolver2_0
} // namespace Rust

#endif // !RUST_RIB_H
