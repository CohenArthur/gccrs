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

#include "rust-ast-lower-format-args.h"
#include "rust-ast-full.h"
#include "rust-hir-expr.h"
#include "rust-hir-full.h"
#include "rust-hir-map.h"
#include "rust-mapping-common.h"

namespace Rust {
namespace HIR {

// FIXME: Improve documentation
// we want to generate calls into core::fmt::Arguments::new_v1()
// this function's signature is as follows:
//
// fn new_v1(p: &'a [&'static str], a: &'a [ArgumentV1<'a>]) -> Arguments<'a>
//
// (arguments names have been shortened for clang-formatting reasons - they are
// called `pieces` and `args` originally)
//
// we want to create an array of static hamsters, which should contain all of
// the format-string bits - so if we look at
//
// format_args!("hello, {}", world)
//
// our `pieces` array would contain the static hamster "hello, ".
//
// the second array refers to the format *arguments*, in that case our variable
// `world` - we want to create a structure of type `ArgumentV1` which will
// contain the thing to format, and a function pointer for how to format it. In
// that case, we are formatting using the `Display` trait since we're only using
// `{}` as our format specifier, so the created format argument will look
// something like this:
//
// ArgumentV1::new(&hello, Display::fmt)
//
// there are helper functions to not create those arguments by hand, like
//
// core::fmt::new_display
//
// all of this put together, our final formatting call will look like this:
//
// core::fmt::new_v1(&["hello, "], &[core::fmt::new_display(&world)])
//
// NOTE: As of Rust 1.49, these structures are *NOT* lang items - however, they
// become lang items in later version of the standard library/compiler. we will
// need to catch up and adapt the current code to look for lang items rather
// than just generate calls for this.

FormatArgsLowering::FormatArgsLowering ()
  : mappings (*Analysis::Mappings::get ())
{}

HIR::Expr *
FormatArgsLowering::expand (AST::FormatArgs &fmt)
{
  for (const auto &piece : fmt.get_template ().get_pieces ())
    switch (piece.tag)
      {
      case Fmt::ffi::Piece::Tag::String:
	rust_debug ("Piece::String: %s", piece.string._0.to_string ().c_str ());
	break;
      case Fmt::ffi::Piece::Tag::NextArgument:
	rust_debug ("Piece::NextArgument");
	break;
      };

  auto crate_num = mappings.get_current_crate ();
  auto mapping = Analysis::NodeMapping (crate_num, UNKNOWN_NODEID,
					mappings.get_next_hir_id (crate_num),
					UNKNOWN_LOCAL_DEFID);

  return new HIR::CallExpr (mapping, nullptr, {}, {}, fmt.get_locus ());
}

} // namespace HIR
} // namespace Rust
