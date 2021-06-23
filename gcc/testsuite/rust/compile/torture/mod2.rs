mod A {
    pub mod B {
        pub mod C {
            pub struct Foo {
                pub f: i32,
            }
        }
    }
}

impl A::B::C::Foo {
    pub fn new() -> Self {
        A::B::C::Foo {
            f: 23i32,
        }
    }
}
fn main() {
    let a = A::B::C::Foo::new(); // { dg-warning "unused name" }
    let b = A::B::C::Foo { // { dg-warning "unused name" }
        f: 33i32,
    };
}
