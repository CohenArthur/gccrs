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

#ifndef RUST_ERROR_CODES_H
#define RUST_ERROR_CODES_H

#include "rust-system.h"

namespace Rust {

enum class Code
{
  E0054, // Invalid cast
};

class ErrorCode
{
public:
  ErrorCode (Code code);

  const std::string &get_str () const;

private:
  Code code;
};

} // namespace Rust

#endif // !RUST_ERROR_CODES_H
