/*
 * 6.088 IAP 2010
 * Assignment #4: Introduction to C++
 *
 * BST.h
 * Header file for the binary search tree 
 * 
 * You will implement a binary search tree that adheres to this interface.
 * 
 */

#ifndef BST_H
#define BST_H

#include <new>
#include <iostream>

/*
 * Binary search tree
 */
class BST {
    struct Node {
        int val_; Node *left_; Node *right_;
        Node(int val) : val_(val), left_(nullptr), right_(nullptr) {}
    };
    
    Node *root_;

    void delete_tree(Node *root);
    void inorder(Node *root);
public:

    // DO NOT change the declarations of the given methods.
  
    // constructo
    BST();

     // destructor
    ~BST();
  
    // inserts "val" into the tree
    void insert(int val);

    // returns true if and only if "val" exists in the tree.
    bool find(int val);

    // prints the tree elements in the in-order traversal order
    void print_inorder();
};

#endif  // BST_H
