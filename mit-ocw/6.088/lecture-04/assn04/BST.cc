#include "BST.h"
#include <new>

BST::BST() : root_(nullptr) {}

BST::~BST() { delete_tree(root_); }

void BST::delete_tree(Node *root) {
    if (!root) return;
    delete_tree(root->left_);
    delete_tree(root->right_);
    delete root;
}

void BST::insert(int val) {
    Node *new_node = nullptr;
    try {
        new_node = new Node(val);   
    } catch (...) {
        throw std::bad_alloc();
    }
    if (!root_) {
        root_ = new_node;
        return;
    }
    Node *curr = root_;
    while (1) {
        if (val < curr->val_) {
            if (curr->left_) {
                curr = curr->left_;
            } else {
                curr->left_ = new_node;
                return;
            }
        } else if (val > curr->val_) {
            if (curr->right_) {
                curr = curr->right_;
            } else {
                curr->right_ = new_node;
                return;
            }
        } else {
            return;
        }
    }
}

bool BST::find(int val) {
    if (!root_) return false;
    for (Node *curr = root_;;) {
        if (!curr) return false;
        if (curr->val_ == val) return true;
        else if (curr->val_ > val) curr = curr->left_;
        else curr = curr->right_;
    }
    return false;
}

void BST::print_inorder() {
    if (!root_) return;
    inorder(root_);
    std::cout << '\n';
}

void BST::inorder(Node *root) {
    if (!root) return;
    inorder(root->left_);
    std::cout << root->val_ << ' ';
    inorder(root->right_);
}

