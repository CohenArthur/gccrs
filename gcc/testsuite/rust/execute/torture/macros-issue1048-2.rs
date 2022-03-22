macro_rules! maybe_return { ($e:expr) => ($e); }

fn frob(x: i32) -> i32{
    maybe_return! {x}
    // should return 27
    27
}

fn main() -> i32 {
    frob(12) - 27
}
