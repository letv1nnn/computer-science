// MIPT (2023-2024), seminar 4.2
// Problem IPO. Implement preorder traversal using iterative approach.

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    void *val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct StackNode {
    TreeNode *val;
    struct StackNode *next;
} StackNode;

void push(StackNode **stack, TreeNode *val);
TreeNode *pop(StackNode **stack);

TreeNode *newTreeNode(void *val);
void deleteTree(TreeNode *root);

void recursivePreorder(TreeNode *root);
void iterativePreorder(TreeNode *root);

int main(int argc, char **argv) {
    int vals[] = {1, 2, 5, 3, 4, 6, 7};
    TreeNode *root = newTreeNode(vals);
    TreeNode *n1 = newTreeNode(vals + 1), *n2 = newTreeNode(vals + 2);
    root->left = n1; root->right = n2;
    TreeNode *n3 = newTreeNode(vals + 3), *n4 = newTreeNode(vals + 4), *n5 = newTreeNode(vals + 5), *n6 = newTreeNode(vals + 6);
    n1->left = n3; n1->right = n4; n2->left = n5; n2->right = n6;

    printf("Recursive Preorder Traversal: ");
    recursivePreorder(root);
    printf("\n");

    printf("Iterative Preorder Traversal: ");
    iterativePreorder(root);
    printf("\n");

    deleteTree(root);
    return 0;
}

void push(StackNode **stack, TreeNode *val) {
    StackNode *tmp = (StackNode *)calloc(1, sizeof(StackNode));
    if (!tmp) {
        perror("memory allocation failed");
        abort();
    }
    tmp->val = val; tmp->next = *stack;
    *stack = tmp;
}

TreeNode *pop(StackNode **stack) {
    TreeNode *treeNode = (*stack)->val;
    StackNode *tmp = *stack;
    *stack = tmp->next;
    free(tmp);
    return treeNode;    
}

void recursivePreorder(TreeNode *root) {
    if (!root) return;
    printf("%d ", *(int *)root->val);
    recursivePreorder(root->left);
    recursivePreorder(root->right);
}

void iterativePreorder(TreeNode *root) {
    if (!root) return;
    StackNode *stack = NULL;
    push(&stack, root);
    
    while (stack) {
        TreeNode *node = pop(&stack);
        printf("%d ", *(int *)node->val);
 
        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
}

TreeNode *newTreeNode(void *val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node) {
        perror("memory allocation failed");
        abort();
    }
    node->val = val;
    return node;
}

void deleteTree(TreeNode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

