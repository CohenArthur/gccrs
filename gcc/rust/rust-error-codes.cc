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

#include "rust-error-codes.h"

namespace Rust {

static std::map<Code, std::string> str_map = {
#define ERR_STR(__code) {Code::__code, #__code},
  ERR_STR (E0054)
#undef ERR_STR
};

ErrorCode::ErrorCode (Code code) : code (code) {}

const std::string &
ErrorCode::get_str () const
{
  auto it = str_map.find (code);

  rust_assert (it != str_map.end ());

  return it->second;
}

} // namespace Rust
