#pragma once

// abstract methods

class BST {
public:
    virtual ~BST() = 0;

    virtual void insert(int val) = 0;
    virtual bool find(int val) = 0;
    virtual void print_inorder() = 0;
}

