#include <iostream>

int foo() { return 42; }

int main(int argc, char **argv) {
    int x = 10;
    int &rx = x;
    const int &l = foo();
    std::cout << &l << " " << &x << " " << &rx << std::endl;

    return 0;
}
