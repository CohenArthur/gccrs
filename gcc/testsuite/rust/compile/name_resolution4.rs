trait Foo {
    fn foo(&self) {}
}

struct Bar;

fn bar() {
    impl Foo for Bar {}
}

fn main() {
    Bar.foo();
}
