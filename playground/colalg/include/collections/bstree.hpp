#pragma once

#include <new>
#include <ostream>

template <typename T>
class node {
public:
    T val_;
    node *left_, *right_; 

public:
    node(T val);
    node(const node& other);
    ~node();
    node& operator=(const node& other);
};

template <typename T>
class bstree {
protected:
    node<T> *root_;

    // traversal functions
    void postorder_deletion(node<T> *root);
    void inorder_cout(node<T>* root, std::ostream& os) const;
    bool equal_trees(node<T> *r1, node<T> *r2) const;
    node<T>* remove_node(node<T>* r, T val);
public:
    // constructors
    bstree();
    bstree(T root_val);
    bstree(const bstree& other);
    // destructor
    ~bstree();

    // getters
    node<T> getRoot();

    // methods
    virtual void insert(T val);
    virtual bool find(T val);
    virtual void remove(T val);

    // operators
    bstree& operator=(const bstree& other);
    bool operator==(const bstree& other);
    friend std::ostream& operator<<(std::ostream& os, const bstree<T>& tree) {
        os << "[ ";
        tree.inorder_cout(tree.root_, os);
        os << "]";
        return os;
    }
};

template <typename T>
node<T>::node(T val)
    : val_(val), left_(nullptr), right_(nullptr) {}

template <typename T>
node<T>::node(const node& other) {
    val_ = other.val_;
    left_ = other.left_;
    right_ = other.right_;
}

template <typename T>
node<T>::~node() {
    left_ = right_ = nullptr;
}

template <typename T>
node<T>& node<T>::operator=(const node<T>& other) {
    val_ = other.val_;
    left_ = other.left_;
    right_ = other.right_;
    return *this;
}

template <typename T>
bool bstree<T>::equal_trees(node<T> *r1, node<T> *r2) const {
    if (!r1 || !r2) return false;
    bool left = equal_trees(r1->left, r2->left);
    bool right = equal_trees(r1->left, r2->left);
    return left == right;
}

template <typename T>
bool bstree<T>::operator==(const bstree<T>& other) {
    return equal_trees(root_, other.root_); 
}

template <typename T>
bstree<T>::bstree() : root_(nullptr) {}

template <typename T>
bstree<T>::bstree(T root_val) {
    try { root_ = new node<T>(root_val); }
    catch (...) { throw std::bad_alloc(); }
}

template <typename T>
bstree<T>::bstree(const bstree& other) {
    root_ = other.root_;
}

template <typename T>
bstree<T>::~bstree() {
    postorder_deletion(root_); 
}

template <typename T>
void bstree<T>::postorder_deletion(node<T> *root) {
    if (!root) return;
    postorder_deletion(root->left_);
    postorder_deletion(root->right_);
    delete(root);
}

template <typename T>
void bstree<T>::inorder_cout(node<T> *root, std::ostream& os) const {
    if (!root) return;
    inorder_cout(root->left_, os);
    os << root->val_ << ' ';
    inorder_cout(root->right_, os);
}

template <typename T>
bstree<T>& bstree<T>::operator=(const bstree<T>& other) {
    root_ = other.root_;
    return *this;
}

template <typename T>
void bstree<T>::insert(T val) {
    if (!root_) {
        root_ = new node(val);
        return;
    }
    node<T> *curr = root_;
    while (1) {
        if (!curr || curr->val_ == val) return;
        if (curr->val_ > val) {
            if (curr->left_) {
                curr = curr->left_;
            } else {
                try {
                    curr->left_ = new node<T>(val);
                    return;
                } catch (...) {
                    throw std::bad_alloc();
                }
            }
        } else {
            if (curr->right_) {
                curr = curr->right_;
            } else {
                try {
                    curr->right_ = new node<T>(val);
                    return;
                } catch (...) {
                    throw std::bad_alloc();
                }
            }
        }
    }
}

template <typename T>
bool bstree<T>::find(T val) {
    if (!root_) return false;
    node<T> *curr = root_;
    while (curr) {
        if (curr->val_ == val) return true;
        else if (curr->val_ > val) curr = curr->left_;
        else curr = curr->right_;
    }
    return false;
}

template <typename T>
node<T>* bstree<T>::remove_node(node<T>* r, T val) {
    if (!r) return nullptr;
    if (val < r->val_) {
        r->left_ = remove_node(r->left_, val);
    }
    else if (val > r->val_) {
        r->right_ = remove_node(r->right_, val);
    }
    else {
        // no children
        if (!r->left_ && !r->right_) {
            delete r;
            return nullptr;
        }
        // one child
        if (!r->left_) {
            node<T>* temp = r->right_;
            delete r;
            return temp;
        }
        if (!r->right_) {
            node<T>* temp = r->left_;
            delete r;
            return temp;
        }
        // two children — find inorder successor
        node<T>* succ = r->right_;
        while (succ->left_) succ = succ->left_;
        r->val_ = succ->val_;
        r->right_ = remove_node(r->right_, succ->val_);
    }
    return r;
}

template <typename T>
void bstree<T>::remove(T val) {
    root_ = remove_node(root_, val);
}

