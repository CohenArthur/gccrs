mod A {
    pub mod B {
        pub mod C {
            pub struct Foo {
                pub f: i32,
            }
            impl Foo {
                pub fn new() -> Self {
                    Foo {
                        f: 23i32,
                    }
                }
            }
        }
    }
}

fn main() {
    let _a = A::B::C::Foo::new();
    let _b = A::B::C::Foo {
        f: 33i32,
    };
}
