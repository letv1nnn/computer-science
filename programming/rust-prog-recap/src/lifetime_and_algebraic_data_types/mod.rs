// 2. Время жизни, ADT (Програмирование на Rust)

#![allow(dead_code)]

mod net;

// &'_ T is always Copy
// &'_ mut T is no Copy

fn foo() {
    let x = 1;
    let r: &'_ i32;
    {
        let y = 2;
        r = f(&x, &y);
    }
    println!("{}", *r);

    const fn f<'a: 'b, 'b>(x: &'a i32, _: &'b i32) -> &'a i32 {
        x
    }
}

// 'static > 'a
fn bar<'a, T>(_: &'_ T) -> &'a str {
    let xs: &'static str = "any";
    xs
}

#[repr(transparent)]
#[derive(Debug, Clone)]
struct BoxWrapper<T> {
    inner: Box<T>,
}

fn tar() {
    let mut _w = BoxWrapper {
        inner: Box::new(42),
    };
    let _: &'_ i32 = &*_w.inner; // '_ lives only on 38th line
    _w = BoxWrapper {
        inner: Box::new(62),
    };
}

// Typing
// Ordinary - can be used any number of times.
// Linear - must be used exactly once.
// Affine - must be used at most once.
//
// Rust is considered to have Affine typing for non-Copy types and Ordinary for Copy

fn never_and_unit_types() {
    // (!) used for computations that never return a value
    let _x = loop {};
    #[allow(while_true, unreachable_code)]
    let _y = while true {};

    // ! can coerce into other types because an expression that never
    // produces a value can be used anywhere a value would be required
    let _z = match (|| Some(42))() {
        Some(n) => n,
        None => panic!("got nothing"),
    };

    let something = || Some(42);
    let init = if let Some(val) = something() {
        val
    } else {
        loop {}
    };
    println!("{}", init);

    fn diverge() -> ! {
        loop {}
    }

    let x = return;

    // panic!(); for bag signaling
    // unimplemented!(); for not yet written code
    // unreachable!() for impossible operation

    enum Void {}

    fn nevervoid(void: Void) -> Vec<i32> {
        match void {} // !
    }

    // here, result guarantees successful inner value
    fn extract<T>(result: Result<T, Void>) -> T {
        match result {
            Ok(inner) => inner,
            Err(void) => match void {},
        }
    }
}

fn ranges() {
    let _bounded = 0..10;
    let _from = 0..;
    let _to = ..10;
    let _full = ..;
    let _inclusive = 0..=9;

    for i in (0..10).step_by(2) {
        println!("i = {}", i);
    }
}

fn slices() {
    // slice always knows its length
    // access by index always checks its boundary
    // not possible to turn it off
    // &[T] can be got from &[T; N] or Vec<T>

    let (_x, _y) = (&[1, 2, 3], Box::new([1, 2, 3]));

    fn print_slice(xs: &[i32]) {
        for idx in 0..xs.len() {
            println!("{}", xs[idx]);
        }
    }
}

#[repr(C)]
#[derive(Debug, Copy, Clone)]
struct ZstDefaultAlignment;

#[repr(align(8))]
#[derive(Debug, Copy, Clone)]
struct ZstCustomAlignment;

#[repr(C)]
#[derive(Debug, Copy, Clone)]
struct TupleStructDefaultOrder(u8, i128, u16);

#[derive(Debug, Copy, Clone)]
struct TupleStructReordered(u8, i128, u16);

#[test]
fn alignment_and_size_structs() {
    use std::mem::{align_of, size_of};

    assert_eq!(size_of::<ZstDefaultAlignment>(), 0_usize);
    assert_eq!(align_of::<ZstDefaultAlignment>(), 1_usize);

    assert_eq!(size_of::<ZstCustomAlignment>(), 0_usize);
    assert_eq!(align_of::<ZstCustomAlignment>(), 8_usize);

    assert_eq!(size_of::<TupleStructDefaultOrder>(), 48_usize);
    assert_eq!(align_of::<TupleStructDefaultOrder>(), 16_usize);

    assert_eq!(size_of::<TupleStructReordered>(), 32_usize);
    assert_eq!(align_of::<TupleStructReordered>(), 16_usize);
}

#[derive(Debug, Copy, Clone)]
enum ZstEnum {}

#[derive(Debug, Copy, Clone)]
enum Res<T, E> {
    Ok(T),
    Err(E),
}

#[derive(Copy, Clone)]
union Union {
    a: u8,
    b: u32,
}

#[test]
fn alignment_and_size_enums_and_unions() {
    use std::mem::{align_of, size_of};

    assert_eq!(size_of::<ZstEnum>(), 0_usize);
    assert_eq!(align_of::<ZstEnum>(), 1_usize);

    assert_eq!(size_of::<Res<u16, String>>(), 24_usize);
    assert_eq!(align_of::<Res<(), String>>(), 8_usize);

    assert_eq!(size_of::<Union>(), 4_usize);
    assert_eq!(align_of::<Union>(), 4_usize);
}
