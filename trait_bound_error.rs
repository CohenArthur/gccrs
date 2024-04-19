struct Arguments<'a>;
struct Result;
struct Formatter;

#[lang = "sized"]
trait Sized {}

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
    fn write_fmt(&mut self, args: Arguments<'_>) -> Result {
        write(self, args)
    }
}

pub fn write<T: Write>(output: &mut T, args: Arguments<'_>) -> Result {
    let mut formatter = Formatter;

    let mut idx = 0;

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

pub struct Stdout;

impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> Result {
        // unsafe { puts(s as *const str as *const i8) };

        Result
    }
}

fn print_to<T: Write>(args: Arguments<'_>, s: T, label: &str) {
    s.write_fmt(args);
}

pub fn _print(args: Arguments<'_>) {
    print_to(args, Stdout, "stdout");
}

macro_rules! println {
    ($($arg:tt)*) => {{
        std::io::_print(format_args_nl!($($arg)*));
    }};
}

fn main() {}
