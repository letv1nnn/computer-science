// Move semantics in C++ are a useful concept that allows for the efficient
// and optimized transfer of ownership of data between objects. One of the
// main goals of move semantics is to increase performance, since moving an
// object is faster and more efficient than deep copying the object.

// lvalues are objects that refer to a location in memory.
// rvalues are anything that is not a lvalue.

// std::move is the most common way of moving an object from one lvalue to
// another. std::move casts an expression to a rvalue. This allows for us to
// interact with a lvalue as a rvalue, and allows for the ownership to be
// transferred from one lvalue to another.

#include <vector>
#include <utility>
#include <iostream>

void move_add_three_and_print(std::vector<int> &&vec) {
    std::vector<int> vec1 = std::move(vec);
    vec1.push_back(3);
    for (const int &item : vec1)
        std::cout << item << ' ';
    std::cout << '\n';
}

void add_three_and_print(std::vector<int> &&vec) {
    vec.push_back(3);
    for (const int &item : vec)
        std::cout << item << ' ';
    std::cout << '\n';
}

template <typename T> void print_vector(const std::vector<T> vec) {
    for (int i{}; i < vec.size(); ++i)
        std::cout << vec[i] << ' ';
    std::cout << '\n';
}

int main(int argc, char **argv) {
    //  | lvalue |   | rvalue |
    int      a     =     10;

    std::vector<int> int_vector = {1, 2, 3, 4};
    std::vector<int> stealing_ints = std::move(int_vector);

    std::cout << "Initial int_vector: "; print_vector(int_vector);
    std::cout << "Moved to stealing_ints: "; print_vector(stealing_ints);

    std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);

    rvalue_stealing_ints[1]--;

    std::cout << "Printing from stealing_int: "; print_vector(stealing_ints);
    std::cout << "Printing from rvalue_stealing_ings: "; print_vector(rvalue_stealing_ints);

    // -------------------------------------
    std::vector<int> int_array2 = {1, 2, 3, 4};
    std::cout << "Calling move_add_three_and_print...\n";
    move_add_three_and_print(std::move(int_array2));
    // std::cout << "int_array2: "; print_vector(int_array2);

    std::vector<int> int_array3 = {1, 2, 3, 4};
    std::cout << "Calling add_three_and_print...\n";
    add_three_and_print(std::move(int_array3));
    // std::cout << "int_array3: "; print_vector(int_array3);

    return 0;
}
