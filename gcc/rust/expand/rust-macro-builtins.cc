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

#include "rust-macro-builtins.h"
#include "rust-diagnostics.h"
#include "rust-expr.h"
#include "rust-macro-invoc-lexer.h"
#include "rust-parse.h"
#include "rust-session-manager.h"

namespace Rust {
namespace {
std::unique_ptr<AST::Expr>
make_string (Location locus, std::string value)
{
  return std::unique_ptr<AST::Expr> (
    new AST::LiteralExpr (value, AST::Literal::STRING,
			  PrimitiveCoreType::CORETYPE_STR, {}, locus));
}
} // namespace

AST::ASTFragment
MacroBuiltin::assert (Location invoc_locus, AST::MacroInvocData &invoc)
{
  auto token_stream = invoc.get_delim_tok_tree ().to_token_stream ();

  MacroInvocLexer lex (std::move (token_stream));
  Parser<MacroInvocLexer> parser (std::move (lex));

  std::vector<std::unique_ptr<AST::SingleASTNode>> nodes;

  if (parser.peek_current_token ()->get_id () == TokenId::END_OF_FILE)
    {
      rust_error_at (
	invoc_locus,
	"%<assert!()%> requires a boolean expression as an argument");
      return AST::ASTFragment::create_empty ();
    }
  else
    {
      // FIXME:
      // Expand to the following code:
      // if <condition> {
      // } else {
      //      panic!("assertion failed");
      //      // For now generate a trap or something
      // }
      auto condition = parser.parse_expr ();
      auto if_expr = std::unique_ptr<AST::BlockExpr> (
	new AST::BlockExpr ({}, nullptr, {}, {}, invoc_locus, Location ()));
      auto else_expr = std::unique_ptr<AST::BlockExpr> (
	new AST::BlockExpr ({}, nullptr, {}, {}, invoc_locus, Location ()));

      auto if_block = std::unique_ptr<AST::Expr> (
	new AST::IfExprConseqElse (std::move (condition), std::move (if_expr),
				   std::move (else_expr), {}, invoc_locus));
      auto if_node = std::unique_ptr<AST::SingleASTNode> (
	new AST::SingleASTNode (std::move (if_block)));
      nodes.emplace_back (std::move (if_node));
    }

  return AST::ASTFragment::create_empty ();
}

AST::ASTFragment
MacroBuiltin::file (Location invoc_locus, AST::MacroInvocData &invoc)
{
  auto current_file
    = Session::get_instance ().linemap->location_file (invoc_locus);
  auto file_str = AST::SingleASTNode (make_string (invoc_locus, current_file));

  return AST::ASTFragment ({file_str});
}
} // namespace Rust
