#![feature(no_core)]
#![no_core]

#[cfg(all(target_pointer_width = "64", not(windows)))]
pub type c_long = i64;
#[cfg(all(target_pointer_width = "64", not(windows)))]
pub type c_ulong = u64;
