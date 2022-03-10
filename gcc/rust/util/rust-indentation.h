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

#ifndef RUST_INDENTATION_H
#define RUST_INDENTATION_H

#include <sstream>

#include "rust-diagnostics.h"

namespace Rust {
class IndentManager
{
public:
  IndentManager () : current (0) {}

  IndentManager increment () { return IndentManager (current + step); }

  IndentManager decrement ()
  {
    rust_assert (current != 0);

    return IndentManager (current - step);
  }

  std::string as_string () const { return std::string (current, ' '); }

private:
  IndentManager (size_t level) : current (level) {}

  /* Step by which to modify the current level each time */
  static constexpr size_t step = 4;

  /* Current level of indentation to print */
  size_t current;
};
} // namespace Rust

/**
 * Overload in order to help clear up the code when building pretty-prints
 */
std::ostream& operator<<(std::ostream &stream, const Rust::IndentManager &indentation);

#endif // RUST_INDENTATION_H
