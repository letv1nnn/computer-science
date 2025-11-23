#include "./include/vector.hpp"
#include <assert.h>

#define TEST_HEADER(header) std::cout << "\t<===> TEST: " << (header) << " <===>\n";
#define TEST_PASSED(action) std::cout << "PASSED: " << (action) << '\n';
#define TEST_ALL_PASSED std::cout << "All tests PASSED ✅\n";

void vector_test();

int main(int argc, char **argv) {
    
    vector_test();

    return 0;
}

void vector_test() {
    TEST_HEADER("vector");

    vector<int> v1;
    
    v1.push_back(23);
    assert(v1.front() == 23);    
    assert(v1.back() == 23);
    TEST_PASSED("push_back, front, back"); 

    v1.push_back(76);
    assert(v1.front() == 23);    
    assert(v1.back() == 76);
    TEST_PASSED("push_back, front, back"); 

    assert(v1.capacity() == 2);
    assert(v1.size() == 2);
    v1.push_back(38);
    assert(v1.capacity() == 4);
    assert(v1.size() == 3);
    TEST_PASSED("capacity, size");

    v1.pop_back();
    assert(v1.size() == 2);
    assert(v1.back() == 76);
    TEST_PASSED("pop_back, back, size");

    assert(v1.empty() == false);
    TEST_PASSED("empty");

    v1.resize(10);
    assert(v1.size() == 10);
    assert(v1.capacity() == 16);
    TEST_PASSED("resize");

    assert(v1[0] == 23);
    assert(v1[1] == 76);
    assert(v1.at(0) == 23);
    assert(v1.at(1) == 76);
    TEST_PASSED("[] operator, at");

    v1.erase(1);
    assert(v1[1] == 0);
    assert(v1.size() == 9);
    v1.emplace_back(1729);
    assert(v1.back() == 1729);
    TEST_PASSED("erase, emplace_back");

    v1.clear();
    assert(v1.size() == 0);
    TEST_PASSED("clear");

    TEST_ALL_PASSED;
}


