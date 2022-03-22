macro_rules! maybe_return { ($e:expr) => ($e); }

fn frob(x: i32) -> i32{
    maybe_return! {x}
    // should return 27
    27 // { dg-error "expecting .\}. but .integer literal. found" }
    // { dg-error "error may be from having an expression" "" { target *-*-* } .-1 }
}

fn main() -> i32 {
    frob(12) - 27
}
