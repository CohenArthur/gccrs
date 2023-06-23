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

#include "rust-name-resolver-2.0.h"

namespace Rust {
namespace Resolver2_0 {

void
Resolver::insert (Identifier name, NodeId id, Namespace ns)
{
  switch (ns)
    {
    case Namespace::Values:
      values.insert (name, id);
      break;
    case Namespace::Types:
      types.insert (name, id);
      break;
    case Namespace::Labels:
    case Namespace::Macros:
      gcc_unreachable ();
    }
}

void
Resolver::scoped (Rib rib, NodeId id, std::function<void (void)> lambda,
		  tl::optional<Identifier> path)
{
  values.push (rib, id, path);
  types.push (rib, id, path);
  macros.push (rib, id, path);
  // labels.push (rib, id);

  lambda ();

  values.pop ();
  types.pop ();
  macros.pop ();
  // labels.pop (rib);
}

void
Resolver::scoped (Rib rib, Namespace ns, NodeId scope_id,
		  std::function<void (void)> lambda,
		  tl::optional<Identifier> path)
{
  switch (ns)
    {
    case Namespace::Values:
      values.push (rib, scope_id, path);
      break;
    case Namespace::Types:
      types.push (rib, scope_id, path);
      break;
    case Namespace::Labels:
    case Namespace::Macros:
      gcc_unreachable ();
    }

  // for (auto &ns : namespaces)
  //   push_rib (ns);

  lambda ();

  // for (auto &ns : namespaces)
  //   pop_rib (ns);

  switch (ns)
    {
    case Namespace::Values:
      values.pop ();
      break;
    case Namespace::Types:
      types.pop ();
      break;
    case Namespace::Labels:
    case Namespace::Macros:
      gcc_unreachable ();
    }
}

} // namespace Resolver2_0
} // namespace Rust
