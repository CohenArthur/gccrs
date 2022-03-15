//! There are two main components to the polonius-engine library: Facts and
//! Output.

use polonius_engine::{AllFacts, Atom, FactTypes};

use std::convert::From;

#[derive(Debug, Clone, Copy, Default)]
struct GccrsPolonius;

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct GccrsAtom(usize);

impl Atom for GccrsAtom {
    fn index(self) -> usize {
        self.0
    }
}

impl From<usize> for GccrsAtom {
    fn from(inner: usize) -> GccrsAtom {
        GccrsAtom(inner)
    }
}

impl From<GccrsAtom> for usize {
    fn from(atom: GccrsAtom) -> Self {
        atom.index()
    }
}

impl FactTypes for GccrsPolonius {
    type Origin = GccrsAtom;
    type Loan = GccrsAtom;
    type Point = GccrsAtom;
    type Variable = GccrsAtom;
    type Path = GccrsAtom;
}

#[repr(C)]
pub struct FfiGccrsPolonius(pub(crate) AllFacts<GccrsPolonius>);

#[no_mangle]
/// # Safety
/// You *need* to call this function before any other polonius related
/// functions. It will initialize the inner content of the `handle` pointer
/// and return.
pub unsafe extern "C" fn polonius_init() -> *mut FfiGccrsPolonius {
    let facts = AllFacts::default();
    eprintln!("[polonius] init");
    Box::into_raw(Box::new(FfiGccrsPolonius(facts)))
}

/// # Safety
/// This is not safe
#[no_mangle]
pub unsafe extern "C" fn polonius_deinit(handle: *mut FfiGccrsPolonius) {
    eprintln!("[polonius] deinit");
    Box::from_raw(handle);
}

#[no_mangle]
/// # Safety
/// Do not call this function without having initialized the handle first using
/// [`polonius_init`]
pub unsafe extern "C" fn polonius_var_used_at(
    handle: *mut FfiGccrsPolonius,
    var_id: usize,
    point_id: usize,
) {
    let handle = handle.as_mut().unwrap();

    handle.0.var_used_at.push((var_id.into(), point_id.into()))
}

#[no_mangle]
/// # Safety
/// Do not call this function without having initialized the handle first using
/// [`polonius_init`]
pub unsafe extern "C" fn polonius_define_var(
    handle: *mut FfiGccrsPolonius,
    var_id: usize,
    point_id: usize,
) {
    let handle = handle.as_mut().unwrap();

    handle
        .0
        .var_defined_at
        .push((var_id.into(), point_id.into()))
}
