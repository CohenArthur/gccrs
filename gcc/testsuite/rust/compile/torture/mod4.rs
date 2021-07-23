mod foo {
    pub struct Foo {
        pub f: i32,
    }

    pub fn foofn() -> i32 {
        return 3i32;
    }
}

struct Bar {b:i32}

fn main() {
	let _t=Bar{b:3i32};
    let a;
    a = foo::Foo { f: 3i32 };

    let b;
    b = foo::foofn();
}
