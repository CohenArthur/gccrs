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
#include "rust-hir-full.h"

namespace Rust {
namespace HIR {

FormatArgsLowering::FormatArgsLowering () {}

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

  return nullptr;
}

} // namespace HIR
} // namespace Rust
