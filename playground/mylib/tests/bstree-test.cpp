// compile with g++ bstree-test.cpp -lgtest -lgtest_main -pthread

#include <gtest/gtest.h>
#include <optional>
#include "../include/ds.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace ds::trees;

TEST(BinarySearchTree, InsertAndErase) {
    bstree<int> tree;

    tree.insert(10);
    tree.insert(20);
    EXPECT_EQ(tree.size(), 2);

    tree.erase(0);
    EXPECT_EQ(tree.size(), 1);

    tree.erase(0);
    EXPECT_EQ(tree.size(), 0);
}

TEST(BinarySearchTree, Operators) {
    bstree<double> tree;

    tree.insert(1.2345);
    EXPECT_TRUE(tree[0] == 1.2345);
}

TEST(BinarySearchTree, Get) {
    bstree<int> tree;

    std::optional<int> get_val = tree.get(40);
    EXPECT_EQ(get_val, std::nullopt);

    tree.insert(32);
    get_val = tree.get(0);
    EXPECT_EQ(get_val.value(), 32);
}

TEST(BinarySearchTree, Present) {
    bstree<int> tree;
   
    EXPECT_FALSE(tree.present(17)); 
    
    tree.insert(42);
    EXPECT_TRUE(tree.present(42));
}

TEST(BinarySearchTree, RootValue) {
    bstree<double> tree;

    std::optional<double> root_value = tree.root_val();
    EXPECT_TRUE(root_value == std::nullopt);
    
    tree.insert(3.141592);
    root_value = tree.root_val();
    EXPECT_EQ(root_value.value(), 3.141592);
}

TEST(BinarySearchTree, Size) {
    bstree<int> tree;
    
    EXPECT_EQ(tree.size(), 0);

    tree.insert(20);
    EXPECT_EQ(tree.size(), 1);

    tree.insert(10);
    EXPECT_EQ(tree.size(), 2);

    tree.erase(1);
    EXPECT_EQ(tree.size(), 1);
    
    tree.insert(10);
    EXPECT_EQ(tree.size(), 1);
    
    tree.erase(0);
    EXPECT_EQ(tree.size(), 0);
}
