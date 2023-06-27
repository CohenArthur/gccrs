struct Bar;

trait Foo {
    fn bar(&self) {}
}

fn outer() {
    impl Foo for Bar {}
}

fn main() {
    Bar.bar();
}
