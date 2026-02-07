// The class template std::optional manages an optional contained value, i.e. a value that may or may not be present.
//
// Any instance of optional at any given point in time either contains a value or does not contain a value.
// If an optional contains a value, the value is guaranteed to be nested within the optional object.
// Thus, an optional object models an object, not a pointer, even though operator*() and operator->() are defined.

// When an object of type optional<T> is contextually converted to bool, the conversion returns true if
// the object contains a value and false if it does not contain a value.

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <optional>
#include <string>

template <typename T> std::optional<T> divide(const T a, const T b) {
    return (b == 0) ? std::nullopt : std::optional<T>(a / b);
}

void optional_example() {
    // c++ 17
    std::optional<std::string> option{};
    assert(!option.has_value());
    option.emplace("str");
    assert(option.has_value());

    std::string str = option.value();
    assert(str == "str");

    option.reset();
    assert(!option.has_value());

    str = option.value_or("or str");
    assert(str == "or str");

    std::optional<int> k{2};
    assert(k.value() == *k);

    std::optional<std::string> hello{"hello"};
    assert(hello.value().size() == hello->size());

    // c++ 23
    auto c = divide(12, 4)
            .and_then([](int x) {
                return divide(x, 3);
            });
    assert(c == 1);
   
    int num = divide(5, 0)
            .or_else([] { return std::optional<int>{42}; })
            .value(); 
    assert(num == 42);
}

int main(int argc, char **argv) {
    optional_example();

    return 0;
}

