#pragma once

#include <iostream>
#include <cstddef>
#include <optional>

namespace ds {
    namespace trees {
        template <typename T>
        class bstree {
        protected:
            struct Node {
                Node *left_, *right_, *parent_;
                std::optional<T> val_ = std::nullopt;
                Node(T val);
                Node();
            };
        protected:
            void print_inorder(Node *root) const;
            void destroy(Node *root);
            void find(std::size_t &idx, Node *&curr) const;
            Node *min_node(Node* n) const;
        protected:
            std::size_t size_;
            Node *root_;
        public:
            bstree();
            bstree(T val);
            virtual ~bstree();
        public:
            virtual void insert(T val);
            virtual void erase(std::size_t idx);
            std::optional<T> get(std::size_t idx) const;
            bool present(T val) const;
        public:
            T &operator[](std::size_t idx);
            const T &operator[](std::size_t idx) const;
        public:
            std::optional<T> root_val() const;
            std::size_t size() const;
            void print() const;
        };
        
        template <typename T>
        class avl_tree : public bstree<T> {};

        template <typename T>
        class rb_tree {};
    }
    namespace sequence {
        template <typename T>
        class vector {};

        template <typename T>
        class queue {};

        template <typename T>
        class stack {
        private:
            T *data_;
            std::size_t size_, capacity_;
        public:
            stack();
            ~stack();
        public:
            void push(T &val);
            T &pop();
            void reserve();
        public:
            std::size_t size();
            std::size_t capacity();
        };
    }
    namespace hash {
        template <typename T>
        class hashmap {};
    }
}

// --------------------------------------------------------------------------------------Stack
template <typename T>
ds::sequence::stack<T>::stack() : size_(0), capacity_(0), data_(nullptr) {}

template <typename T>
ds::sequence::stack<T>::~stack() { delete[] data_; }

template <typename T>
std::size_t ds::sequence::stack<T>::capacity() { return capacity_; }

template <typename T>
std::size_t ds::sequence::stack<T>::size() { return size_; }

template <typename T>
void ds::sequence::stack<T>::reserve() {
    std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T *new_data = new T[new_capacity];
    for (std::size_t i{}; i < size_; ++i)
        new_data[i] = data_[i];
    delete[] data_;

    data_ = new_data;
    capacity_ = new_capacity;
}

template <typename T>
void ds::sequence::stack<T>::push(T &val) {
    if (size_ >= capacity_) reserve();
    data_[size_] = val;
    size_++;
}

template <typename T>
T &ds::sequence::stack<T>::pop() {
    size_--;
    return data_[size_ + 1];
}

// --------------------------------------------------------------------------------------Binary-Search Tree
template <typename T>
ds::trees::bstree<T>::Node::Node() : left_(nullptr), right_(nullptr), parent_(nullptr) {}

template <typename T>
ds::trees::bstree<T>::Node::Node(T val) : Node() { val_ = val; }

template <typename T>
ds::trees::bstree<T>::bstree() : size_(0), root_(nullptr) {}

template <typename T>
ds::trees::bstree<T>::bstree(T val) : size_(1), root_(new Node(val)) {}

template <typename T>
ds::trees::bstree<T>::~bstree() { destroy(root_); }

template <typename T>
void ds::trees::bstree<T>::destroy(Node *root) {
    if (!root) return;
    destroy(root->left_);
    destroy(root->right_);
    delete root;
}

template <typename T>
void ds::trees::bstree<T>::print() const {
    std::cout << "[ ";
    print_inorder(root_);
    std::cout << "]\n";
}

template <typename T>
void ds::trees::bstree<T>::print_inorder(Node *root) const {
    if (!root) return;
    print_inorder(root->left_);
    std::cout << root->val_.value() << ' ';
    print_inorder(root->right_);
}

template <typename T>
std::optional<T> ds::trees::bstree<T>::root_val() const { return root_ ? root_->val_ : std::nullopt; }

template <typename T>
std::size_t ds::trees::bstree<T>::size() const { return size_; }

template <typename T>
bool ds::trees::bstree<T>::present(T val) const {
    for (Node *curr = root_; curr;) {
        if (curr->val_.value() == val) return true;
        else if (curr->val_.value() > val) curr = curr->left_;
        else curr = curr->right_;
    }
    return false;
}

template <typename T>
void ds::trees::bstree<T>::insert(T val) {
    try {
        Node *inserted_node = new Node(val);
        if (!root_) {
            root_ = inserted_node;
        } else {
            Node *curr = root_;
            while (1) {
                if (val < curr->val_.value()) {
                    if (curr->left_) {
                        curr = curr->left_;
                    } else {
                        curr->left_ = inserted_node;
                        inserted_node->parent_ = curr;
                        break;
                    }
                } else if (val > curr->val_.value()) {
                    if (curr->right_) {
                        curr = curr->right_;
                    } else {
                        curr->right_ = inserted_node;
                        inserted_node->parent_ = curr;
                        break;
                    }
                }
                else {
                    delete inserted_node;
                    return;
                }
            }
        }
        ++size_;
    } catch (std::bad_alloc) {
        std::cerr << "memory allocation failed\n";
    }
}

template <typename T>
typename ds::trees::bstree<T>::Node *ds::trees::bstree<T>::min_node(Node* n) const {
    while (n && n->left_) n = n->left_;
    return n;
}

template <typename T>
void ds::trees::bstree<T>::erase(std::size_t idx) {
    if (idx >=size_ || !root_) return;

    Node *z = root_;
    std::size_t i = idx;
    find(i, z);
    if (!z) return;

    if (!z->left_ || !z->right_) {
        Node* child = z->left_ ? z->left_ : z->right_;

        if (!z->parent_) {
            root_ = child;
        } else if (z == z->parent_->left_) {
            z->parent_->left_ = child;
        } else {
            z->parent_->right_ = child;
        }

        if (child) {
            child->parent_ = z->parent_;
        }

        delete z;
    } else {
        Node* succ = min_node(z->right_);

        z->val_ = succ->val_;

        Node* succ_child = succ->right_;

        if (succ->parent_->left_ == succ) succ->parent_->left_ = succ_child;
        else succ->parent_->right_ = succ_child;

        if (succ_child) succ_child->parent_ = succ->parent_;

        delete succ;
    }
    --size_;
}

template <typename T>
std::optional<T> ds::trees::bstree<T>::get(std::size_t idx) const {
    if (idx >= size_ || !root_) return std::nullopt;
    Node *curr = root_;
    find(idx, curr);
    return curr->val_;
}

template <typename T>
void ds::trees::bstree<T>::find(std::size_t &idx, Node *&curr) const {
    if (!curr) return;
    find(idx, curr->left_);
    if (idx == 0) return;
    --idx;
    find(idx, curr->right_);
}

template <typename T>
T &ds::trees::bstree<T>::operator[](std::size_t idx) {
    if (idx >= size_ || !root_) throw std::out_of_range("bstree index out of range"); 
    Node* curr = root_;
    find(idx, curr);
    return curr->val_.value();
}

template <typename T>
const T &ds::trees::bstree<T>::operator[](std::size_t idx) const {
    if (idx >= size_ || !root_) throw std::out_of_range("bstree index out of range");
    Node* curr = root_;
    find(idx, curr);
    return curr->val_.value();
}
