#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T> vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) std::cout << vec[i] << ", ";
    std::cout << vec[n - 1] << '\n';
}

int main(int argc, char **argv) {
    std::vector<int> v = {1, 2, 3, 4, 5}; 
    std::cout << "Initial vector: ";
    print(v);

    // push_back takes an already constructed object and copies or moves it into the vector.
    v.push_back(99);
    print(v);

    // emplace_back constructs the object directly inside the vector
    v.emplace_back(1729);
    print(v);

    // insert, inserts elements at the specified location in the container
    v.insert(v.begin(), 111);
    print(v);
    v.insert(v.begin() + 10, 2, 33);
    print(v);
    v.insert(v.end(), {601, 602, 603});
    print(v);

    // emplace, inserts a new element into the container directly before pos.
    v.emplace(v.begin() + 20, 777);
    print(v);

    // erases the specified element from the container
    v.erase(v.begin() + 3);
    print(v);
    v.erase(v.begin(), v.begin() + 3);
    print(v);

    // reserve, increase the capacity of the vector
    v.reserve(24);
    std::cout << "Capacity: " << v.capacity() << '\n';

    // resize creates n elements in the vector. If int is default, each element is initialized to 0.
    v.resize(32);
    print(v);

    // erases all elements from the container. After this call, size() returns zero. Does not effect the capacity.
    // v.clear();
    
    // pop_back, removes the last element of the container
    v.pop_back();
    print(v);

    return 0;
}

