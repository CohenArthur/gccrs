#include <rust-name-resolver.h>

namespace Rust {
namespace Resolver {

  void Scope::append_reference_for_def (NodeId refId, NodeId defId)
  {
    bool ok = false;

    Resolver *resolver = Resolver::get ();

    iterate ([&] (Rib *r) mutable -> bool {
      if (r->decl_was_declared_here (defId))
        {
          ok = true;
          r->append_reference_for_def (defId, refId);
          return false;
        }
      return true;
    });

    if (!ok)
      resolver->iterate_type_ribs ([&] (Rib *r) -> bool {
        if (r->decl_was_declared_here (defId))
          {
            ok = true;
            r->append_reference_for_def (defId, refId);
            return false;
          }
        return true;
      });

    rust_assert (ok);
  }

}
}
