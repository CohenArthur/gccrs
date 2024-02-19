// Copyright (C) 2024 Free Software Foundation, Inc.

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

#ifndef RUST_AST_BUILTIN_NODES_H
#define RUST_AST_BUILTIN_NODES_H

#include "rust-system.h"
#include "line-map.h"
#include "optional.h"
#include "rust-ast.h"
#include "rust-fmt.h"

namespace Rust {
namespace AST {

// Definitions, from rustc's `FormatArgs` AST struct
// https://github.com/rust-lang/rust/blob/1be468815c/compiler/rustc_ast/src/format.rs
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
// └──────────────────────────────────────────────┘
//                     FormatArgs
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//                                     └─────────┘
//                                      argument
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//              └───────────────────┘
//                     template
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//               └────┘└─────────┘└┘
//                      pieces
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//               └────┘           └┘
//                   literal pieces
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//                     └─────────┘
//                     placeholder
//
// format_args!("hello {abc:.xyz$}!!", abc="world");
//                      └─┘  └─┘
//                      positions (could be names, numbers, empty, or `*`)

// FIXME: Merge with the class below this one?
class FormatArgumentKind
{
public:
  enum class Kind
  {
    Normal,
    Named,
    Captured,
  } kind;

  Identifier &get_ident ()
  {
    rust_assert (kind == Kind::Captured || kind == Kind::Named);

    return ident.value ();
  }

  FormatArgumentKind (Kind kind, tl::optional<Identifier> ident)
    : kind (kind), ident (ident)
  {}

private:
  tl::optional<Identifier> ident;
};

class FormatArgument
{
public:
  static FormatArgument normal (std::unique_ptr<Expr> expr)
  {
    return FormatArgument (FormatArgumentKind::Kind::Normal, tl::nullopt,
			   std::move (expr));
  }

  static FormatArgument named (Identifier ident, std::unique_ptr<Expr> expr)
  {
    return FormatArgument (FormatArgumentKind::Kind::Named, ident,
			   std::move (expr));
  }

  static FormatArgument captured (Identifier ident, std::unique_ptr<Expr> expr)
  {
    return FormatArgument (FormatArgumentKind::Kind::Captured, ident,
			   std::move (expr));
  }

private:
  FormatArgument (FormatArgumentKind::Kind kind, tl::optional<Identifier> ident,
		  std::unique_ptr<Expr> expr)
    : kind (FormatArgumentKind (kind, ident)), expr (std::move (expr))
  {}

  FormatArgumentKind kind;
  std::unique_ptr<Expr> expr;
};

class FormatArguments
{
public:
  FormatArguments () {}
  FormatArguments (FormatArguments &&) = default;

  void push (FormatArgument &&elt) { args.emplace_back (std::move (elt)); }

private:
  FormatArguments (const FormatArguments &) = delete;

  std::vector<FormatArgument> args;
};

// TODO: Format documentation better
// Having a separate AST node for `format_args!()` expansion allows some
// important optimizations which help reduce generated code a lot. For example,
// turning `format_args!("a {} {} {}", 15, "hey", 'a')` directly into
// `format_args!("a 15 hey a")`, since all arguments are literals. Or,
// flattening imbricated `format_args!()` calls: `format_args!("heyo {}",
// format_args!("result: {}", some_result))` -> `format_args!("heyo result: {}",
// some_result)`
// FIXME: Move to rust-macro.h
class FormatArgs : public Visitable
{
public:
  enum class Newline
  {
    Yes,
    No
  };

  FormatArgs (location_t loc, Fmt::Pieces template_str,
	      FormatArguments &&arguments)
    : loc (loc), template_str (std::move (template_str)),
      arguments (std::move (arguments))
  {}

  void accept_vis (AST::ASTVisitor &vis);

private:
  location_t loc;
  // FIXME: This probably needs to be a separate type - it is one in rustc's
  // expansion of format_args!(). There is extra handling associated with it.
  // we can maybe do that in rust-fmt.cc? in collect_pieces()? like do the
  // transformation into something we can handle better
  Fmt::Pieces template_str;
  FormatArguments arguments;
};

} // namespace AST
} // namespace Rust

#endif // ! RUST_AST_BUILTIN_NODES_H
