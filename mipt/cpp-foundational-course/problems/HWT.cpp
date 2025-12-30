// C++ foundational course, MIPT, 2021-2022
// compile with: g++ HWT.cpp -DTEST_MODE -lgtest -lgtest_main -pthread
/*
From standard input, a sequence of unique integer keys and two types
of queries is given: finding the k-th smallest element and counting
elements smaller than a given value. Keys and queries may appear in any order.
*/

#include <cmath>
#include <cstddef>
#include <cstdlib>

#include <iostream>
#include <optional>
#include <vector>
#include <queue>
#include <optional>

#include <gtest/gtest.h>

struct Input {
    std::vector<int> keys_, ms_, ns_;
    Input(std::vector<int> keys, std::vector<int> ms, std::vector<int> ns)
        : keys_(keys), ms_(ms), ns_(ns) {}
    Input() {
        char c; int num;
        std::cout << "Enter pairs (k, key), (m, mth smallest element) or (n, n smallest elements):\n";
        while (std::cin >> c >> num) {
            if (c == 'k') keys_.push_back(num);
            else if (c == 'm') ms_.push_back(num);
            else if (c == 'n') ns_.push_back(num);
        }
    }
};

template <typename T>
class Tree {
private:
    struct Node {
        T val_;
        std::size_t size_ = 1;
        Node *left_ = nullptr, *right_ = nullptr;
        Node(T val) : val_(val) {}
    };

    static std::size_t size(Node* n) { return n ? n->size_ : 0; }
    static void update(Node* n) { if (n) n->size_ = 1 + size(n->left_) + size(n->right_); }
private:
    void print_inorder(Node *root) const {
        if (!root) return;
        print_inorder(root->left_);
        std::cout << root->val_ << ' ';
        print_inorder(root->right_);
    }
    void inorder(std::vector<T> &vec, Node *root) {
        if (!root) return;
        inorder(vec, root->left_);
        vec.push_back(root->val_);
        inorder(vec, root->right_);
    }
private:
    Node *root_ = nullptr;
public:
    Tree(const T& val) { root_ = new Node(val); }
    Tree() = default;

    bool is_balanced() {
        if (!root_) return true;

        std::queue<Node*> q;
        q.push(root_);

        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            
            std::size_t l = size(cur->left_);
            std::size_t r = size(cur->right_);
            if (std::abs(static_cast<long>(l) - static_cast<long>(r)) > 1)
                return false;

            if (cur->left_) q.push(cur->left_);
            if (cur->right_) q.push(cur->right_);
        }
        return true;
    }

    void insert(const T val) {
        
    }
    void erase(const T val) {

    }

    std::vector<T> get_inorder() {
        std::vector<T> vec;
        inorder(vec, root_);
        return vec;
    }

    void print() const { print_inorder(root_); std::cout << '\n'; }
    T get_root() const { return root_->val_; }

    std::optional<T> get_mth_smallest(int m) {
        std::vector<T> vec = get_inorder();
        if (m > 0 && m <= vec.size()) return  vec[m - 1];
        else return std::nullopt;
    }
    int get_smaller_than_n(int n) {
        std::vector<T> vec = get_inorder();
        int count = 0;
        for (int i{}; i < vec.size(); ++i) 
            if (vec[i] < n) ++count;
        return count;
    }
};

void solution(const Input &input);

int main(int argc, char **argv) {
#ifndef TEST_MODE
    Input input;
    solution(input);
    return 0;
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}

void solution(const Input &input) {
    Tree<int> tree;
    std::cout << "M: ";
    for (int i{}; i < input.ms_.size(); ++i) {
        auto res = tree.get_mth_smallest(input.ms_[i]);
        if (res) std::cout << *res << ' ';
    }
    std::cout << "\nN: ";
    for (int i{}; i < input.ns_.size(); ++i) {
        auto res = tree.get_smaller_than_n(input.ns_[i]);
        if (res) std::cout << res << ' ';
    }
    std::cout << '\n';
}

TEST(Tree, IsBalanced) {
    Tree<int> tree;
    bool is_balanced = tree.is_balanced();
    EXPECT_TRUE(is_balanced == true);
}
