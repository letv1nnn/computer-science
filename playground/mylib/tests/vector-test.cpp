// compile with: 

#include "../include/ds.hpp"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace ds::sequence;

TEST(Vector, Basi) {
    vector<int> v;
}
