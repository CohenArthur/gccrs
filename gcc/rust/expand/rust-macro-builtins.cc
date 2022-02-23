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
#include "rust-ast.h"
#include "rust-expr.h"
#include "rust-macro.h"
#include "rust-parse.h"
#include "rust-macro-invoc-lexer.h"
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

std::unique_ptr<AST::Expr>
make_integer (Location locus, int value)
{
  return std::unique_ptr<AST::Expr> (
    new AST::LiteralExpr (std::to_string (value), AST::Literal::INT,
			  PrimitiveCoreType::CORETYPE_INT, {}, locus));
}

std::unique_ptr<AST::BlockExpr>
make_block (Location locus,
	    std::vector<std::unique_ptr<AST::Stmt>> &&statements = {},
	    std::unique_ptr<AST::Expr> &&trailing_expr = nullptr)
{
  return std::unique_ptr<AST::BlockExpr> (
    new AST::BlockExpr (std::move (statements), std::move (trailing_expr), {},
			{}, locus, Location ()));
}

std::unique_ptr<AST::Expr>
make_if (Location locus, std::unique_ptr<AST::Expr> condition,
	 std::unique_ptr<AST::BlockExpr> block)
{
  return std::unique_ptr<AST::Expr> (
    new AST::IfExprConseqElse (std::move (condition), std::move (block),
			       nullptr, {}, locus));
}

std::unique_ptr<AST::Expr>
make_not (Location locus, std::unique_ptr<AST::Expr> &&expr)
{
  return std::unique_ptr<AST::Expr> (
    new AST::NegationExpr (std::move (expr), NegationOperator::NOT, {}, locus));
}

std::unique_ptr<AST::Expr>
make_function_call (Location locus, std::string fn_name,
		    std::vector<std::unique_ptr<AST::Expr>> &&args = {})
{
  auto fn_name_path = AST::PathIdentSegment (fn_name, locus);
  auto fn_path_sgmt = AST::PathExprSegment (fn_name_path, locus);
  auto fn_path = std::unique_ptr<AST::PathInExpression> (
    new AST::PathInExpression ({fn_path_sgmt}, {}, locus));

  return std::unique_ptr<AST::Expr> (
    new AST::CallExpr (std::move (fn_path), std::move (args), {}, locus));
}

std::unique_ptr<AST::Expr>
make_macro_call (Location locus, std::string macro_name,
		 AST::DelimTokenTree token_tree)
{
  auto macro_path = AST::SimplePathSegment (macro_name, locus);
  auto macro_invoc_data
    = AST::MacroInvocData (AST::SimplePath ({macro_path}), token_tree);

  return std::unique_ptr<AST::Expr> (
    new AST::MacroInvocation (macro_invoc_data, {}, locus));
}
} // namespace

AST::ASTFragment
MacroBuiltin::assert (Location invoc_locus, AST::MacroInvocData &invoc)
{
  auto token_stream = invoc.get_delim_tok_tree ().to_token_stream ();

  MacroInvocLexer lex (std::move (token_stream));
  Parser<MacroInvocLexer> parser (std::move (lex));

  std::vector<AST::SingleASTNode> nodes;

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

      auto panic_tt = *invoc.get_delim_tok_tree ().clone_delim_token_tree ();
      auto if_expr
	= make_block (invoc_locus, {},
		      make_macro_call (invoc_locus, "panic", panic_tt));
      auto if_block
	= make_if (invoc_locus, make_not (invoc_locus, std::move (condition)),
		   std::move (if_expr));

      nodes.emplace_back (AST::SingleASTNode (std::move (if_block)));
    }

  return AST::ASTFragment (nodes);
}

AST::ASTFragment
MacroBuiltin::file (Location invoc_locus, AST::MacroInvocData &invoc)
{
  auto current_file
    = Session::get_instance ().linemap->location_file (invoc_locus);
  auto file_str = AST::SingleASTNode (make_string (invoc_locus, current_file));

  return AST::ASTFragment ({file_str});
}

AST::ASTFragment
MacroBuiltin::panic (Location invoc_locus, AST::MacroInvocData &invoc)
{
  // FIXME: rustc switches panic implementations based on the rust edition:
  // Either panic2021 or panic2015
  // It resolves to one of the two macros, which are defined in the
  // core library.
  // We can resolve to them later on once we compile the core library, but for
  // now add a call to a simple trap handler.

  // FIXME: Add call to display error message before exiting

  //  auto node = AST::SingleASTNode (
  //    make_function_call (invoc_locus, "exit",
  //			{make_integer (invoc_locus, 101)}));
  //
  // return AST::ASTFragment ({node});
  return AST::ASTFragment::create_empty ();
}
} // namespace Rust
