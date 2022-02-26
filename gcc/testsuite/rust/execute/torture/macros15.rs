macro_rules! Test {
    ($a:ident, $b:ty) => {
        struct $a($b);
    };
}

fn main() -> i32 {
    Test!(Foo, i32);

    let a = Foo(123);
    a.0 - 123
}
