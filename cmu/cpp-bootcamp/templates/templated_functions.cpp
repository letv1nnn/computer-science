#include <iostream>
#include <gtest/gtest.h>

// it is possible to create specialized templated functions, that do
// different things for differrent types.

template <typename T> void print_msg() {
    std::cout << "Hello, World!\n";
}

template <> void print_msg<float>() {
    std::cout << "print_msg called with float type!\n";
}

// template parameters do not have to be classes. Take this basic
// function that takess in a bool as a template parameter and
// does different things to the argument depending on the boolean argument.
template <bool T> int add3(int a) {
    return (T) ? a + 3 : a;
}

int main(int argc, char **argv)  {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TemplatedFunction, MainTest) {
    EXPECT_EQ(add3<bool{}>(int{}), 0);
    EXPECT_EQ(add3<true>(3), 6);
}
