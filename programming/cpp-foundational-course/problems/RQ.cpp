// C++ foundational course, MIPT, 2021-2022
// compile with: g++ -DTEST_MODE RQ.cpp -lgtest -lgtest_main -pthread

#include <iostream>
#include <gtest/gtest.h>

template <typename C, typename T>
int range_query(const C& s, T fst, T snd);

int main(int argc, char **argv) {
#ifndef TEST_MODE
    std::size_t size{}; 
    std::cout << "Enter the number of keys: ";
    std::cin >> size;
    
    std::vector<int> vec(size);
    std::cout << "Enter " << size << " keys:\n";
    for (int i{}; i < size; ++i)
        std::cin >> vec[i];

    std::size_t lower, upper;
    std::cout << "Enter bounds: ";
    std::cin >> lower >> upper;

    int result = range_query(vec, lower, upper);
    std::cout << "Result: " << result << '\n';
    return 0;
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}

template <typename C, typename T>
int range_query(const C& s, T fst, T snd) {
    using itt = typename C::const_iterator;
    itt start = std::lower_bound(s.begin(), s.end(), fst);
    itt fin = std::upper_bound(s.begin(), s.end(), snd);
    return std::distance(start, fin);
}

TEST(ProblemTest, RangeQuery) {
    std::vector<int> vec{1, 13, 18, 19, 37, 5};
    std::size_t lower{3}, upper{31};
    int result = range_query(vec, lower, upper);
    EXPECT_EQ(result, 5);
    
    vec.push_back(101);
    lower = 17, upper = 38;
    result = range_query(vec, lower, upper);
    EXPECT_EQ(result, 4);
}
