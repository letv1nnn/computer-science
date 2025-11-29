#pragma once

#include <algorithm>
#include <cstddef>
#include <ostream>


template<typename T>
class node {
public:
    T val_;
    node *left_, *right_;
    size_t height_;
    node(const T& val) : val_(val), left_(nullptr), right_(nullptr), height_(1) {}
    ~node() { delete left_; delete right_; }
};


template<typename T>
class avltree {
    node<T> *root_;
    
    size_t height(node<T> *node) const { return node ? node->height_ : 0; }
    size_t balance_factor(node<T> *left, node<T> *right) const { return abs(left->height_ - right->height_); }
    void update_height(node<T> *node) { node->height_ = 1 + std::max(node->left_->height_, node->right_->height_); }

    void inorder(node<T> *root, std::ostream& os) {
        if (!root) return;
        inorder(root->left_, os);
        os << root->val_ << " ";
        inorder(root->right_, os);
    }

public:
    avltree() {}
    ~avltree() { delete root_; }

    

    friend std::ostream& operator<<(std::ostream& os, const avltree<T>& tree) {
        os << "[ ";
        tree.inorder(tree.root_, os); 
        os << " ]";
        return os;
    }
};

