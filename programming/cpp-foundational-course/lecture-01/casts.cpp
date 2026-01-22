// C++ foundational course, MIPT, 2021-2022

#include <iostream>
#include <cstdio>

void static_cast_example();
void dynamic_cast_example();
void const_cast_example();
void reinterpret_cast_example();

int main(int argc, char **argv) {
#ifdef STATIC_CAST
    static_cast_example();
#elif DYNAMIC_CAST
    dynamic_cast_example();
#elif CONST_CAST
    const_cast_example();
#else
    reinterpret_cast_example();
#endif
    return 0;
}

// Compile-time cast for well-defined, non-polymorphic conversions.
// Use when conversion is logically correct and guaranteed.
class Base {};
class Derived : public Base {};

void static_cast_example() {
    int x = 5;
    double y = static_cast<double>(x);
    
    std::cout << "X: " << typeid(x).name() << ", Y: " << typeid(y).name() << '\n';

    Base *b = static_cast<Base *>(new Derived);
}

// Runtime-checked cast for polymorphic types (must have virtual function).
// Use when you aren’t sure of the dynamic type
struct Animal { virtual void speak() { std::cout << "animal speaks...\n"; } };
struct Dog : public Animal { void speak() override { std::cout << "dog barks...\n"; } };

void dynamic_cast_example() {
    Animal *a = new Dog;
    a->speak();

    Dog *d = dynamic_cast<Dog *>(a);
    d->speak();
}

// Adds or removes const / volatile.
// Only safe if original object was not declared const.
void const_cast_example() {
    int num = 42;
    const int *cp = &num;
    int *p = const_cast<int *>(cp);
    printf("Const pointer address: %p\nConst casted pointer address: %p\n", cp, p);
    (*p)++; 
    printf("Cp: %d, P: %d\n", *cp, *p);
}


// Low-level bit reinterpretation.
// Use only when you understand memory layout.
void reinterpret_cast_example() {
    int x = 65;
    int *px = &x;
    char *p = reinterpret_cast<char *>(px);
    std::cout << *p << '\n';
}

