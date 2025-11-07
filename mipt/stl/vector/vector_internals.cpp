#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main(int argc, char **argv) {
    int n;
    if (argc == 2) n = std::stoi(argv[1]);
    else std::cin >> n;

    std::vector<int> vec;

    // resize creates n elements in the vector. If int is default, each element is initialized to 0.
    // vec.resize(n);

    // reserve only allocates memory, does not change the size.
    // vec.reserve(n); 

    for (int i = 0; i < n; ++i)
        vec.push_back(i);

    std::cout << "Size of the vector on the stack: " << sizeof(vec) << '\n';
    std::cout << "Size of the vector on the heap: " << vec.size() << '\n';
    std::cout << "Capacity of the vector on the heap: " << vec.capacity() << '\n';


    return 0;
}
