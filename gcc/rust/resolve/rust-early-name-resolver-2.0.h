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

#ifndef RUST_EARLY_NAME_RESOLVER_2_0_H
#define RUST_EARLY_NAME_RESOLVER_2_0_H

#include "optional.h"
#include "rust-ast.h"
#include "rust-ast-visitor.h"
#include "rust-name-resolver-2.0.h"
#include "rust-default-resolver.h"

namespace Rust {
namespace Resolver2_0 {

class Early : public DefaultResolver
{
  using DefaultResolver::visit;

public:
  Early (Resolver &resolver);

  void go (AST::Crate &crate);

  // we need to handle definitions for textual scoping
  void visit (AST::MacroRulesDefinition &) override;

  // as well as lexical scopes
  void visit (AST::BlockExpr &) override;

  void visit (AST::MacroInvocation &) override;
  void visit (AST::UseDeclaration &) override;
  void visit (AST::UseTreeRebind &) override;
  void visit (AST::UseTreeList &) override;
  void visit (AST::UseTreeGlob &) override;

private:
  // TODO: Add documentation that this is needed...
  class TextualScope
  {
  public:
    void push ();
    void pop ();

    void insert (std::string name, NodeId id);
    tl::optional<NodeId> get (const std::string &name);

  private:
    std::vector<std::unordered_map<std::string, NodeId>> scopes;
  };

  TextualScope textual_scope;
};

} // namespace Resolver2_0
} // namespace Rust

#endif // ! RUST_EARLY_NAME_RESOLVER_2_0_H
