// A reference in C++ is a method of creating an alias to a variable, where
// these aliases refer to the same data in memory. References are useful for
// keeping track of state, passing arguments into functions, and for general
// performance improvements. In general, it is important to understand
// references to do well in this class.

#include <gtest/gtest.h>

void add_three(int &a) { a+= 3; }

TEST(References, Fundamentals) {
    int a{};
    add_three(a);
    EXPECT_EQ(a, 3);
}
