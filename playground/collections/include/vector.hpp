#pragma once

#include <cstddef>
#include <iostream>
#include <ostream>
#include <new>
#include <stdexcept>

template<typename T>
class vector {
    size_t capacity_;
    size_t size_;
    T *data_;

    void grow() {
        size_t new_capacity = (capacity_ == 0) ? 1 : 2 * capacity_;
        T* new_data = nullptr;
        try {
            new_data = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i)
                new_data[i] = data_[i];
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        } catch (const std::bad_alloc& e) {
            delete[] new_data;
            std::cerr << "memory allocation failed\n";
            return;
        }
    }
public:
    vector() : capacity_(0), size_(0), data_(nullptr) {}
    ~vector(){ delete[] data_; }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void push_back(const T& value) {
        if (size_ >= capacity_) grow();
        data_[size_] = value;
        ++size_;
    }
    template<typename... Args>
    T& emplace_back(Args&&...args) {
        if (size_ >= capacity_) grow();
        try {
            new (data_ + size_) T(std::forward<Args>(args)...);
            return data_[size_++];
        } catch (...) {
            std::cerr << "memory allocation failed\n";
            return data_[size_];
        }
    }
    
    void pop_back() { size_--; }
    void erase(size_t idx) {
        if (idx >= size_)
           throw std::out_of_range("vector index out of range"); 
        if (size_ == 1 || size_ == idx + 1) { size_--; return; }
        for (int i = idx + 1; i < size_; ++i)
            data_[i - 1] = data_[i];
        size_--;
    }
        
    void clear() { size_ = 0; }
    void resize(size_t size) {
        if (size_ == size) return;
        else if (size_ > size) { size_ = size; return; }
        while (size >= capacity_) grow();
        size_ = size;
    }
   
    // element access 
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    T& at(size_t index) {
        if (index >= size_)
            throw std::out_of_range("vector index out of range");
        return data_[index];
    }
    const T& at(size_t index) const {
        if (index >= size_)
            throw std::out_of_range("vector index out of range");
        return data_[index];
    }
    T& front() {
        if (size_ > 0) return data_[0];
        throw std::out_of_range("vector index out of range");
    }
    const T& front() const {
        if (size_ > 0) return data_[0];
        throw std::out_of_range("vector index out of range");
    }
    T& back() {
        if (size_ > 0) return data_[size_ - 1];
        throw std::out_of_range("vector index out of range");
    }
    const T& back() const {
        if (size_ > 0) return data_[size_ - 1];
        throw std::out_of_range("vector index out of range");
    }

    // printing vector
    friend std::ostream& operator<<(std::ostream& os, const vector<T>& v){
        os << "[ ";
        for (size_t i = 0; i < v.size_; ++i) {
            os << v.data_[i];
            if (i + 1 < v.size_) os << ", ";
        }
        os << " ]";
        return os;
    }
};

