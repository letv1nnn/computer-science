// 3. Трейты. Программирование на Rust

use std::os::raw::c_void;

trait Pet {
    fn name<'a>(&'a self) -> &'a str;
    fn sound<'a, 'b: 'a>(&'a self) -> &'b str;
}

#[derive(Debug, Clone)]
struct Cat {
    name: String,
    age: u8,
    lifes: u8,
}

impl Cat {
    const fn new(name: String) -> Self {
        Self {
            name,
            age: 0_u8,
            lifes: 9_u8,
        }
    }
}

impl Pet for Cat {
    fn name<'a>(&'a self) -> &'a str {
        &self.name
    }
    fn sound<'a, 'b: 'a>(&'a self) -> &'b str {
        "meow"
    }
}

fn greet_pet(pet: Box<dyn Pet>) {
    println!("You: \"hello, {}\"", pet.name());
    println!("{}: \"{}\"", pet.name(), pet.sound());
}

#[repr(C)]
#[derive(Debug, Copy, Clone)]
struct PetVtable<'a> {
    drop: fn(*mut c_void),
    size: usize,
    align: usize,
    name: fn(*const c_void) -> &'a str,
    sound: fn(*const c_void) -> &'static str,
}

#[test]
fn breaking_dynamic_dispatch() {
    const PTR_SIZE: usize = std::mem::size_of::<usize>();

    // trait object: usize to data and usize to vtable
    // [ptr to data, ptr to vtable]
    let mut kitty: Box<dyn Pet> = Box::new(Cat::new("kitty".to_string()));
    assert_eq!(std::mem::size_of::<Box<dyn Pet>>(), 2 * PTR_SIZE);

    // addresses of `ptr to data` and `ptr to vtable`
    let addr_of_data_ptr = &mut kitty as *mut _ as *mut c_void as usize;
    let addr_of_vtable_ptr = &mut kitty as *mut _ as *mut c_void as usize + PTR_SIZE;
    assert_eq!(addr_of_data_ptr, addr_of_vtable_ptr - PTR_SIZE);

    // at this point, we have to pointes to data and to compiler generated vtable.

    // we need pointer to pointer to vtable, to be able to dereference the vtable's fields
    let ptr_to_ptr_to_vtable = addr_of_vtable_ptr as *mut *const PetVtable<'_>;

    // changing vtable's sound method to bark()
    let mut new_vtable = unsafe { **ptr_to_ptr_to_vtable };
    new_vtable.sound = bark;

    unsafe { *ptr_to_ptr_to_vtable = &new_vtable };

    // we changed the vtable only for `kitty` instance, not for all Cat(s)
    assert_eq!(kitty.sound(), "woof");
}

const fn bark<'a>(_this: *const c_void) -> &'a str {
    "woof"
}
