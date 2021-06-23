mod foo {
    pub struct Foo {
        pub f: i32,
    }

    pub fn foofn() -> i32 {
        return 3i32;
    }
}

fn main() {
    let a;
    a = foo::Foo { f: 3i32 };

    let b;
    b = foo::foofn();
}
