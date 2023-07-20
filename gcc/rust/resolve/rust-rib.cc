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

#include "rust-rib.h"

namespace Rust {
namespace Resolver2_0 {

DuplicateNameError::DuplicateNameError (std::string name, NodeId existing)
  : name (name), existing (existing)
{}

Rib::Rib (Kind kind) : kind (kind) {}

Rib::Rib (Kind kind, std::string identifier, NodeId id)
  : Rib (kind, {{identifier, id}})
{}

Rib::Rib (Kind kind, std::unordered_map<std::string, NodeId> values)
  : kind (kind), values (std::move (values))
{}

tl::expected<NodeId, DuplicateNameError>
Rib::insert (std::string name, NodeId id)
{
  auto res = values.emplace (name, id);
  auto inserted_id = res.first->second;

  for (const auto &kv : values)
    rust_debug ("k: %s, v: %d", kv.first.c_str (), kv.second);

  auto ok = res.second;
  rust_debug ("Rib(%p), inserting `%s` (%d) -> Ok? %s", (void *) &values,
	      name.c_str (), id, ok ? "yes" : "no");

  // if we couldn't insert, the element already exists - exit with an error
  // this is okay if we allow shadowing tho - like macros or labels
  // how do we deal with this? `bool can_shadow = false`? TODO XXX
  if (!res.second)
    return tl::make_unexpected (DuplicateNameError (name, inserted_id));

  // return the NodeId
  return inserted_id;
}

tl::optional<NodeId>
Rib::get (const std::string &name)
{
  auto it = values.find (name);

  if (it == values.end ())
    return tl::nullopt;

  return it->second;
}

const std::unordered_map<std::string, NodeId> &
Rib::get_values () const
{
  return values;
}

} // namespace Resolver2_0
} // namespace Rust
