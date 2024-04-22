#![feature(rustc_attrs)]
#![feature(intrinsics)]
#![feature(extern_types)]

#[rustc_builtin_macro]
macro_rules! format_args {
    () => {};
}

#[rustc_builtin_macro]
macro_rules! format_args_nl {
    () => {};
}

#[lang = "sized"]
trait Sized {}

extern "C" {
    fn printf(s: *const i8, ...);
}

pub mod core {
    pub mod fmt {
        pub struct Formatter<'a> {
            pub buf: &'a dyn Write,
        }

        impl<'a> Formatter<'a> {
            pub fn new(buf: &'a dyn Write) -> Formatter {
                Formatter { buf }
            }
        }

        pub struct Result;

        pub struct Arguments<'a> {
            pub pieces: &'a [&'static str],
            pub args: &'a [ArgumentV1<'a>],
        }

        impl<'a> Arguments<'a> {
            pub fn new_v1(pieces: &'a [&'static str], args: &'a [ArgumentV1<'a>]) -> Arguments<'a> {
                Arguments { pieces, args }
            }
        }

        pub struct Opaque;

        pub struct ArgumentV1<'a> {
            pub value: &'a Opaque,
            pub formatter: fn(&Opaque, &mut Formatter) -> Result,
        }

        impl<'a> ArgumentV1<'a> {
            pub fn new<'b, T>(
                value: &'b T,
                formatter: fn(&T, &mut Formatter) -> Result,
            ) -> ArgumentV1 {
                unsafe {
                    ArgumentV1 {
                        value: transmute(value),
                        formatter: transmute(formatter),
                    }
                }
            }
        }

        pub trait Display {
            fn fmt(&self, _: &mut Formatter) -> Result;
        }

        impl Display for i32 {
            fn fmt(&self, _: &mut Formatter) -> Result {
                // { dg-warning "unused name .self." "" { target *-*-* } .-1 }
                Result
            }
        }

        impl Display for &str {
            fn fmt(&self, _: &mut Formatter) -> Result {
                // { dg-warning "unused name .self." "" { target *-*-* } .-1 }
                Result
            }
        }

        pub trait Write {
            #[stable(feature = "rust1", since = "1.0.0")]
            fn write_str(&mut self, s: &str) -> Result;

            /// Glue for usage of the [`write!`] macro with implementors of this trait.
            ///
            /// This method should generally not be invoked manually, but rather through
            /// the [`write!`] macro itself.
            ///
            /// # Examples
            ///
            /// ```
            /// use std::fmt::{Error, Write};
            ///
            /// fn writer<W: Write>(f: &mut W, s: &str) -> Result<(), Error> {
            ///     f.write_fmt(format_args!("{}", s))
            /// }
            ///
            /// let mut buf = String::new();
            /// writer(&mut buf, "world").unwrap();
            /// assert_eq!(&buf, "world");
            /// ```
            #[stable(feature = "rust1", since = "1.0.0")]
            fn write_fmt(&mut self, _args: Arguments<'_>) -> Result {
                write(self, _args)
            }
        }

        pub fn write<T: Write>(output: &mut T, args: Arguments<'_>) -> Result {
            let mut formatter = Formatter::new(output);

            let pieces: &[&str] = args.pieces;

            formatter
                .buf
                .write_str(unsafe { transmute::<_, &str>(*0usize.get_unchecked(pieces)) });

            // let arg = &args[0usize] as &ArgumentV1;
            // (arg.formatter)(arg.value, &mut formatter);

            // for (arg, piece) in args.args.iter().zip(args.pieces.iter()) {
            //     formatter.buf.write_str(*piece)?;
            //     (arg.formatter)(arg.value, &mut formatter)?;
            //     idx += 1;
            // }

            // // There can be only one trailing string piece left.
            // if let Some(piece) = args.pieces.get(idx) {
            //     formatter.buf.write_str(*piece)?;
            // }

            Result
        }
    }
}

extern "rust-intrinsic" {
    #[rustc_const_stable(feature = "const_ptr_offset", since = "1.61.0")]
    pub fn offset<T>(ptr: *const T, count: isize) -> *const T;
    fn size_of<T>() -> usize;
    fn transmute<T, U>(src: T) -> U;
}

extern "C" {
    fn printf(s: *const i8, ...);
}

pub struct FatPtr<T> {
    pub data: *const T,
    pub len: usize,
}

pub union Repr<T> {
    rust: *const [T],
    rust_mut: *mut [T],
    raw: FatPtr<T>,
}

pub enum Option<T> {
    None,
    Some(T),
}

#[lang = "Range"]
pub struct Range<Idx> {
    pub start: Idx,
    pub end: Idx,
}

#[lang = "const_slice_ptr"]
impl<T> *const [T] {
    pub const fn len(self) -> usize {
        unsafe { Repr { rust: self }.raw.len }
    }

    pub const fn as_ptr(self) -> *const T {
        self as *const T
    }
}

#[lang = "const_ptr"]
impl<T> *const T {
    pub const unsafe fn offset(self, count: isize) -> *const T {
        unsafe { offset(self, count) }
    }

    pub const unsafe fn add(self, count: usize) -> Self {
        unsafe { self.offset(count as isize) }
    }

    pub const fn as_ptr(self) -> *const T {
        self as *const T
    }
}

#[lang = "index"]
trait Index<Idx> {
    type Output;

    fn index(&self, index: Idx) -> &Self::Output;
}

impl<T> [T] {
    pub const fn is_empty(&self) -> bool {
        self.len() == 0
    }

    pub const fn len(&self) -> usize {
        unsafe { Repr { rust: self }.raw.len }
    }
}

pub unsafe trait SliceIndex<T> {
    type Output;

    fn get(self, slice: &T) -> Option<&Self::Output>;

    unsafe fn get_unchecked(self, slice: *const T) -> *const Self::Output;

    fn index(self, slice: &T) -> &Self::Output;
}

unsafe impl<T> SliceIndex<[T]> for usize {
    type Output = T;

    fn get(self, slice: &[T]) -> Option<&T> {
        unsafe { Option::Some(&*self.get_unchecked(slice)) }
    }

    fn index(self, slice: &[T]) -> &T {
        unsafe { &*self.get_unchecked(slice) }
    }

    unsafe fn get_unchecked(self, slice: *const [T]) -> *const T {
        // SAFETY: the caller guarantees that `slice` is not dangling, so it
        // cannot be longer than `isize::MAX`. They also guarantee that
        // `self` is in bounds of `slice` so `self` cannot overflow an `isize`,
        // so the call to `add` is safe.
        unsafe { slice.as_ptr().add(self) }
    }
}

impl<T, I> Index<I> for [T]
where
    I: SliceIndex<[T]>,
{
    type Output = I::Output;

    fn index(&self, index: I) -> &I::Output {
        index.index(self)
    }
}

pub mod std {
    pub mod io {
        use core::Result;

        pub struct Stdout;

        impl core::fmt::Write for Stdout {
            fn write_str(&mut self, s: &str) -> Result {
                unsafe {
                    printf(
                        "%s\0" as *const str as *const i8,
                        s as *const str as *const i8,
                    )
                };

                Result
            }
        }

        fn print_to_stdout(args: core::fmt::Arguments<'_>, _label: &str) {
            Stdout.write_fmt(args);
        }

        pub fn _print(args: core::fmt::Arguments<'_>) {
            print_to_stdout(args, "stdout");
        }
    }
}

macro_rules! println {
    ($($arg:tt)*) => {{
        std::io::_print(format_args_nl!($($arg)*));
    }};
}

fn main() -> i32 {
    println!("hello, world!");

    0
}
