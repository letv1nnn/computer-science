// 1. `auto` deduces the variable type from its initializer.
// 2. An initializer is mandatory when using `auto`.
// 
// 3. Top-level `const` is discarded during type deduction.
// 4. References are discarded unless explicitly requested.
// 
// 5. Use `auto&` to preserve lvalue references.
// 6. Use `const auto&` to preserve constness and references.
// 7. Use `auto&&` for forwarding (universal) references.
// 
// 8. Pointer types are preserved during deduction.
// 9. Top-level const on pointers is discarded.
// 10. cv-qualifiers on the pointee are preserved.
//
// 11. Arrays decay to pointers unless deduced as a reference.
// 12. Functions decay to function pointers unless deduced as a reference.
//
// 13. `auto` with braced initialization deduces `std::initializer_list` when possible.
// 14. Mixed-type braced initializers are not allowed.
// 15. Direct-list initialization with a single element deduces the element type.
//
// 16. Multiple variables declared with `auto` must deduce to the same type.
// 17. `auto` deduction follows template type deduction rules.
//
// 18. `auto` can be used as a function return type (C++14+).
// 19. Trailing return types can use `auto`.
//
// 20. `auto` cannot be used without an initializer.
// 21. `auto` cannot deduce different types in a single declaration.
// 22. `auto` cannot be used for function parameters (except with C++20 concepts).

#include <string>

void auto_example() {
    int a = 10;
    auto aa = 10;

    std::string str{};
    auto as = ""; // const char * by default

    const int ca = 42;
    auto aca = ca; // auto cancelles int out in such cases

    double dn = 3.141592;
    double &rdn = dn;
    auto ardn = dn; // cancelles references
    const double &crdn = dn;
    auto acrdn = dn; // same as const
    
    int number{1};
    int *ptr_n = &number;
    auto auto_ptr_n = &number;
    
    const int *c_ptr_n = &number;
    auto auto_c_ptr_n = c_ptr_n; // does not leave anything

    int * const const_ptr_int = &number;
    auto auto_const_ptr_int = const_ptr_int; // const pointer loses its constant
                                                    // so in case of const T * const -> auto(const T * const) -> const T *

    auto li = {1, 2, 3}; // std::init, wtf???
}

// decltype(expr) yields the exact type of expr without evaluating it
// Unparenthesized names give the declared type
// Parenthesized expressions follow value category rules
// lvalue expressions -> T&, xvalue -> T&&, prvalue -> T
// cv-qualifiers and references are preserved
// decltype(auto) uses decltype deduction rules
// Commonly used for templates and exact type deduction

void decltype_example() {
    int i = 42;
    decltype(i) di = 57;

    const int ci = 0;
    decltype(ci) dci = 0;

    int *ptr = nullptr;
    decltype(ptr) dptr;
}

// well well well stuff, since decltype and auto are used for different scenarios, we can connect them
void decltype_auto_example() {
    int i = 42;
    const int *ptr = &i;
    decltype(auto) daptr = ptr;  // does not descard the const part
}

template <typename T, typename R>
auto tfunc(T a, R b) -> decltype(a * b) { return a * b; }

int main(int argc, char **argv) {
    auto_example();
    decltype_example();
    decltype_auto_example();
    return 0;
}
