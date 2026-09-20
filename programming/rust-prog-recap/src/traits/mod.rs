// 3. Трейты. Программирование на Rust

#![allow(dead_code)]

pub(crate) mod trait_objects_and_object_safety;
pub(crate) mod vtables;

// monomorphization happens during compilation
fn make_default<T: Default>(_: T) -> T {
    T::default()
}

trait Area {
    fn area(&self) -> f64;
}

#[derive(Debug, Clone, Copy)]
struct Point(f64, f64);

#[derive(Debug, Clone, Copy)]
struct Circle {
    center: Point,
    radius: f64,
}

impl Area for Circle {
    fn area(&self) -> f64 {
        const PI: f64 = 3.141592;
        PI * self.radius * self.radius
    }
}

#[derive(Debug, Clone, Copy)]
struct Rectangle {
    width: f64,
    height: f64,
}

impl Area for Rectangle {
    fn area(&self) -> f64 {
        self.width * self.height
    }
}

fn try_to_store_shapes() {
    // impossible, because Area has unknown size,
    // thus we can only use dynamic dispatch, in other words
    // we can't store objects of different types since they
    // have different std::mem::size_of().
    // trait is not a type, it's type's property, however
    // in this case it becomes a type (fat pointer).
    // let mut shapes: Vec<Area> = Vec::new();
    let mut shapes: Vec<Box<dyn Area>> = Vec::new();
    shapes.push(Box::new(Circle {
        center: Point(12.34, -56.78),
        radius: 42.0,
    }));
    shapes.push(Box::new(Rectangle {
        width: 5.0,
        height: 32.0,
    }));
    shapes.iter().for_each(|s| println!("{}", s.area()));
}

trait A {
    fn a(&self);
}

// any type that impls B, must impl A
trait B: A {
    fn b(&self);
}
