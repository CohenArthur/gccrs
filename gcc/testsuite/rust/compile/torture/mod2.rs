mod A {
    pub mod B {
        pub mod C {
            pub struct Foo {
            }
        }
    }
}

impl A::B::C::Foo {
    pub fn new() -> Self {
        A::B::C::Foo {
        }
    }
}
 
fn main() {
   let _a = A::B::C::Foo::new();
}
