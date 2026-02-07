// std::any gives you a chance to store anything in an object, and it reports
// errors (or throw exceptions) when you'd like to access a type that is not active.

#include <any>
#include <cassert>
#include <iostream>
#include <string>

void any_example() {
    std::any a(12);
    
    a = std::string{};
    a = 16;

    assert(std::any_cast<int>(a) == 16);

    try {
        std::cout << std::any_cast<std::string>(a) << '\n';
    } catch (const std::bad_any_cast &e) {
        std::cout << e.what() << '\n';
    }

    assert(a.has_value());
    a.reset();
    assert(!a.has_value());
}

int main(int argc, char **argv) {

    return 0;
}
