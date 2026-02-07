// A variant is a data type introduced in C++ 17 that can hold values of different
// types, much like a union in C. However, std::variant brings type safety to the table,
// making it a safer and more versatile alternative.

#include <cassert>
#include <string>
#include <variant>

void variant_example() {
    std::variant<int, double, std::string> my_var;
    my_var = 42;

    assert(std::holds_alternative<int>(my_var));
    assert(!std::holds_alternative<double>(my_var));

    assert(my_var.index() == 0);
    assert(std::get<0>(my_var) == 42);

    my_var.emplace<std::string>(std::string{});
    assert(std::get<2>(my_var) == std::string{});
}

int main(int argc, char **argv) {
    variant_example();
    return 0;
}
