#include <cstdint>
#include <iostream>

void const_cast_example() {
    std::int32_t a{};
    const std::int32_t &ref = a;

    std::int32_t *const pa = const_cast<std::int32_t *>(&ref);
    ++(*pa);  

    std::int32_t &ra = const_cast<std::int32_t&>(ref);
    ra++;

    std::cout << "A: " <<  a << std::endl;
    std::cout << "*PA: " <<  *pa << std::endl;
    std::cout << "RA: " << ra << std::endl;
}

// constexpr does not guarantee compile time evaluation, it CAN be evaluated at compile time.
// constexpr works with function and variables.
//
// PI is a constant and its value is guaranteed to be computed at compile time.
constexpr double PI = 3.1415;
constexpr double area(const double radius) { return PI * (radius * radius); }

// consteval works only with functions, and guarantees that thus MUST be evaluated at compile time. No exceptions.
// immediate function
consteval int add(const int a, const int b) { return a + b; }

// constinit only applies to variables and it ensures compile time initialization 
consteval const char *static_init() { return "hello"; }
const char *dynamic_init() { return "hello"; }

int main(int argc, char **argv) {
    const_cast_example();

    // evaluated at compile time.
    constexpr double x = area(20.f); 
    std::cout << x << std::endl;

    // the following expression won't compile
    // constinit auto dynamic_init = dynamic_init();    
    constinit auto static_init = static_init();

    return 0;
}
