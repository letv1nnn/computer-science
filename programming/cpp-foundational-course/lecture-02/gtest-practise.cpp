// unit testing framework from Google
// compiling: g++ gtest-practise.cpp -lgtest -lgtest_main -pthread

#include <cstring>
#include <gtest/gtest.h>

namespace {
    int sum(int a, int b) { return a + b; }
}

TEST(BasicTesting, Addition) {
    EXPECT_EQ(sum(1, 1), 2);
    EXPECT_EQ(sum(1, 9), 10);

    EXPECT_NE(sum(1, 1), 3);
    EXPECT_NE(sum(5, 6), 10);

    EXPECT_TRUE(sum(90, 16) == 106);
    EXPECT_FALSE(sum(90, 16) == 1);
}

TEST(BasicTesting, CommonMacros) {
    // Equality
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_GT(2, 1);
    EXPECT_LT(1, 2);
    EXPECT_LE(1, 1);
    EXPECT_GE(2, 2);
    // Boolean
    EXPECT_TRUE(std::strcmp("hello", "hello") == 0);
    EXPECT_FALSE(1 == 2);
    // Floating-point
    EXPECT_FLOAT_EQ(1.f, 1.f);
    EXPECT_DOUBLE_EQ(1., 1.);
    EXPECT_NEAR(18, 21, 3);
    // String
    EXPECT_STREQ("world", "world");
    EXPECT_STRNE("hello", "world");
}
