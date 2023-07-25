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

Early::Early (Resolver &resolver) : DefaultResolver (resolver) {}

void
Early::go (AST::Crate &crate)
{
  // First we go through TopLevel resolution to get all our declared items
  auto toplevel = TopLevel (resolver);
  toplevel.go (crate);

  rust_debug ("[ARTHUR] toplevel values:\n%s",
	      resolver.values.as_debug_string ().c_str ());
  rust_debug ("[ARTHUR] toplevel types:\n%s",
	      resolver.types.as_debug_string ().c_str ());
  rust_debug ("[ARTHUR] toplevel macros:\n%s",
	      resolver.macros.as_debug_string ().c_str ());

  // FIXME: Do we add a `scoped` method?
  textual_scope.push ();

  // Then we proceed to the proper "early" name resolution: Import and macro
  // name resolution
  for (auto &item : crate.items)
    item->accept_vis (*this);

  textual_scope.pop ();
}

void
Early::TextualScope::push ()
{
  // push a new empty scope
  scopes.emplace_back ();
}

void
Early::TextualScope::pop ()
{
  rust_assert (!scopes.empty ());

  scopes.pop_back ();
}

void
Early::TextualScope::insert (std::string name, NodeId id)
{
  rust_assert (!scopes.empty ());

  // FIXME: Do not ignore return value
  scopes.back ().insert ({name, id});

  rust_unreachable ();
}

tl::optional<NodeId>
Early::TextualScope::get (const std::string &name)
{
  for (auto iterator = scopes.rbegin (); iterator != scopes.rend (); iterator++)
    {
      auto scope = *iterator;
      auto found = scope.find (name);
      if (found != scope.end ())
	return found->second;
    }

  return tl::nullopt;
}

void
Early::visit (AST::MacroRulesDefinition &def)
{
  DefaultResolver::visit (def);

  textual_scope.insert (def.get_rule_name ().as_string (), def.get_node_id ());
}

void
Early::visit (AST::MacroInvocation &invoc)
{
  auto path = invoc.get_invoc_data ().get_path ();

  // When a macro is invoked by an unqualified identifier (not part of a
  // multi-part path), it is first looked up in textual scoping. If this does
  // not yield any results, then it is looked up in path-based scoping. If the
  // macro's name is qualified with a path, then it is only looked up in
  // path-based scoping.

  // https://doc.rust-lang.org/reference/macros-by-example.html#path-based-scope

  tl::optional<NodeId> definition = tl::nullopt;
  if (path.get_segments ().size () == 1)
    {
      auto text_def
	= textual_scope.get (path.get_final_segment ().as_string ());

      if (!text_def)
	definition = resolver.macros.resolve_path (path);
    }
  else
    {
      definition = resolver.macros.resolve_path (path);
    }

  if (!definition.has_value ())
    {
      rust_error_at (invoc.get_locus (), "could not resolve macro invocation");
      return;
    }

  rust_debug_loc (invoc.get_locus (), "[ARTHUR]: definition found: %d",
		  definition.value ());
}

void
Early::visit (AST::UseDeclaration &use)
{
  rust_debug_loc (use.get_locus (), "ARTHUR: visiting");
}

void
Early::visit (AST::UseTreeRebind &use)
{
  rust_debug_loc (use.get_locus (), "ARTHUR: visiting");
}

void
Early::visit (AST::UseTreeList &use)
{
  rust_debug_loc (use.get_locus (), "ARTHUR: visiting");
}

void
Early::visit (AST::UseTreeGlob &use)
{
  rust_debug_loc (use.get_locus (), "ARTHUR: visiting");
}

} // namespace Resolver2_0
} // namespace Rust
