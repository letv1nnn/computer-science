#include <iostream>
#include <string>
#include <utility>

// inefficient copying
/*
void print_name(std::string name) {
    std::cout << name << '\n';
}
*/

// only accepts lvalues, T& is a lvalue reference
void print_name(std::string &name) {
    std::cout << "[lvalue] " << name << '\n';
}

// only accepts rvalues, T&& is a rvalue reference
void print_name(std::string &&name) {
    std::cout << "[rvalue] " << name << '\n';
}

// accepts both lvalues and rvalues, const T& is used for both lvalue and rvalue reference
void print_name(const std::string &name) {
    std::cout << "[lvalue & rvalue] " << name << '\n';
}

int main(int argc, char **argv) {
    std::string name = "Name ", surname = "Surname";
    std::string fullname = name + surname;

    print_name(fullname);
    print_name(name + surname);
    print_name(std::move(fullname));

    return 0;
}

