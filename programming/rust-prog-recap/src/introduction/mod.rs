#![allow(dead_code)]

use std::io::Write;

// Philosphy Intro:
// functional/complicated code does not slowen runtime.
//
// the following example:
// fn average(xs: &[i32]) -> f64 {
//     xs.iter().fold(0, |x, y| x + y) as f64 / xs.len() as f64
// }
// executes in the same speed as
fn average(xs: &[i32]) -> f64 {
    let mut sum: i32 = 0;
    for i in 0..xs.len() {
        sum += xs[i];
    }
    sum as f64 / xs.len() as f64
}

// Why do we need Runtime?
// - Automatic memory management - saves dev time.
// - Amadal law - runtime of the program does not matter if 90% is IO.
// - Manual memory management - leads to catastrophic errors.

// println!("Hello, World!");
fn no_macro_hello_world() {
    let buf: &'static [u8; 14_usize] = b"Hello, World!\n"; // valid UTF-8
    std::io::stdout().write_all(buf).unwrap();
}

fn integers() {
    let _y = 92_000_000_i64;
    let _hex_octal_bin: u64 = 0xffff_ffff + 0o777 + 0b1;
    let byte = b'a';
    assert_eq!(byte, 64_u8);
}

// overflow = programmer's fault!
// `cargo run` will panic, but `cargo run --release` will not.
fn overflow() {
    let x = i32::MAX;
    let y = x + 1;
    println!("{}", y);
}

fn explicit_arithmetic_with_overflow() {
    let x = i32::MAX;

    let y = x.wrapping_add(1);
    assert_eq!(y, i32::MIN);

    let y = x.saturating_add(1);
    assert_eq!(y, i32::MAX);

    let (y, overflowed) = x.overflowing_add(1);
    assert!(overflowed);
    assert_eq!(y, i32::MIN);

    match x.checked_add(1) {
        Some(_) => unreachable!(),
        None => println!("overflowed"),
    };
}

fn tuples() {
    let t = (72,);
    println!("{:?}", &t as *const (i32,));
    println!("{:?}", &t.0 as *const i32);
}

fn dealloc() {
    let x = Box::new(1);
    let y = Box::new(42);

    drop(x);
    drop(y);
}

trait Drop<T> {
    fn drop(_: T);
}

impl<T> Drop<T> for T {
    fn drop(_: T) {}
}

#[derive(Debug, Clone, Copy, Default)]
struct Point {
    x: f64,
    y: f64,
}

fn vector() {
    let xs = vec![Point::default(), Point::default()];
    // first el.x addr == first el addr
    assert_eq!(
        &xs[0].x as *const f64 as *const usize,
        &xs[0] as *const Point as *const usize,
    );
    // second el.y addr == second el addr + 1
    assert_eq!(
        &xs[1].y as *const f64 as usize,
        &xs[1] as *const Point as usize + std::mem::size_of::<f64>(),
    );
}
