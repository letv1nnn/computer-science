// MIPT (2023-2024), seminar 4.2
// Problem IS, check if an arbitrary binary tree is binary search tree.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node *new(int val);
void delete(Node *root);

bool isBinarySearch(Node *root, int *prev);

int main(int argc, char **argv) {
    int vals[] = {4, 2, 9, 1, 3, 6, 10};
    Node *root = new(vals[0]);
    Node *n1 = new(vals[1]), *n2 = new(vals[2]);
    root->left = n1; root->right = n2;
    Node *n3 = new(vals[3]), *n4 = new(vals[4]), *n5 = new(vals[5]), *n6 = new(vals[6]);
    n1->left = n3; n1->right = n4; n2->left = n5; n2->right = n6;

    int prev = INT_MIN;
    printf("The given tree is ");
    if (isBinarySearch(root, &prev)) printf("Binary Search Tree\n");
    else printf("NOT Binary Search Tree\n");
    
    delete(root);
    return 0;
}

bool isBinarySearch(Node *root, int *prev) {
    if (!root) return true;
    if (!isBinarySearch(root->left, prev)) return false;
    if (root->val <= *prev) return false;
    *prev = root->val;
    return isBinarySearch(root->right, prev);
}

Node *new(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {perror("memory allocation failed"); abort();}
    node->val = val;
    return node;
}

void delete(Node *root) {
    if (!root) return;
    delete(root->left);
    delete(root->right);
    free(root);
}

