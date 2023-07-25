// { dg-options "-frust-name-resolution-2.0" }

pub mod foo {
    pub mod bar {
        pub mod baz {
            pub mod qux {
                #[macro_export]
                macro_rules! foo {
                    (one) => {};
                }

                pub fn foo() {}
            }
        }

        fn f() {
            crate::foo::bar::baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }

            super::bar::baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }
            baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }

            fn inner() {
                macro_rules! foo {
                    (two) => {};
                }

                crate::foo::bar::baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }
                super::bar::baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }
                baz::qux::foo!(); // { dg-error "could not resolve macro invocation" }

                foo!(two); // ok
                crate::foo!(one); // ok
                super::super::foo!(one); // ok
                super::super::super::foo!(); // { dg-error "too many leading .super. keywords" }
                                             // { dg-error "could not resolve macro invocation" "" { target *-*-* } .-1 }

                super::crate::foo!(); // { dg-error "leading path segment .crate. can only be used" }
                                      // { dg-error "could not resolve macro invocation" "" { target *-*-* } .-1 }
            }
        }
    }
}
