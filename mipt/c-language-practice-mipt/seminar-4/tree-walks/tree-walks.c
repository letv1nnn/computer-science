// MIPT (2023-2024), seminar 4.2
// Tree traversals
// LRV - postorder
// LVR - inorder
// VLR - preorder

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *val;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(void *val);
void deleteTree(Node *root);

void postorder(Node *root);
void preorder(Node *root);
void inorder(Node *root);

int main(int argc, char **argv) {
    int vals[] = {1, 2, 3, 4, 5, 6, 7};
    Node *root = newNode(vals);
    Node *n1 = newNode(vals + 1);
    Node *n2 = newNode(vals + 2);
    Node *n3 = newNode(vals + 3);
    Node *n4 = newNode(vals + 4);
    Node *n5 = newNode(vals + 5);
    Node *n6 = newNode(vals + 6);

    root->left = n1; root->right = n2;
    n1->left = n3; n1->right = n4; 
    n2->left = n5; n2->right = n6;

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    deleteTree(root);
    return 0;
}

void postorder(Node *root) {
    if (!root) return;
    postorder(root->left);
    printf("%d ", *(int *)root->val);
    postorder(root->right);
}

void preorder(Node *root) {
    if (!root) return;
    printf("%d ", *(int *)root->val);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    inorder(root->right);
    printf("%d ", *(int *)root->val);
}

Node *newNode(void *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        perror("memory allocation failed");
        abort();
    }
    node->val = val; node->left = NULL; node->right = NULL;
    return node;
}

void deleteTree(Node *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

