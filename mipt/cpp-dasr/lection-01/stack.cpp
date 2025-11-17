#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

template <typename T>
class Stack {
private: // default for class, public is a default for structs
    T *vec;
    std::size_t size;
    std::size_t capacity;
public:
    Stack() : capacity(1), size(0){
        try {
            vec = new T[1];
        } catch (const std::bad_alloc& e) {
            std::cerr << "memory allocation failed: " << e.what() << '\n';
            vec = nullptr;
            throw;
        }
    }
    Stack(int capacity) : capacity(capacity), size(0) {
        try {
            vec = new T[capacity];
        } catch (const std::bad_alloc& e) {
            std::cerr << "memory allocation failed: " << e.what() << '\n';
            vec = nullptr;
            throw;
        }
    }
    ~Stack() {
        delete[] vec;
    }

    void push(T val) {
        if (size >= capacity) {
            capacity *= 2;
            T* tmp = new T[capacity];
            if (!tmp) {
                std::cerr << "memory allocation failed\n";
                return;
            }
            for (std::size_t i = 0; i < size; ++i)
                tmp[i] = vec[i];
            delete[] vec;
            vec = tmp;
        }
        vec[size++] = val;
    }
    T *pop() {
        if (size == 0) return nullptr;
        return &vec[size--];
    }
    void clear() {
        delete[] vec;
        size = 0; capacity = 1;
        vec = new T[capacity];
    }
    void print() {
        std::cout << "[ ";
        for (int i = 0; i < size - 1; ++i)
            std::cout << vec[i] << ", ";
        std::cout << vec[size - 1] << " ]\n";
    }
};

int main(int argc, char **argv) {
    Stack<int> s(11);
    
    s.push(5);
    s.push(3141592);
    s.print();
    s.pop();
    s.print();

    return 0;
}
