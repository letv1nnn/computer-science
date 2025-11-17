#include "lruCache.h"

Node *newNode(const void *val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    n->val = val; n->next = NULL; n->prev = NULL;
    return n;
}

void deleteNode(Node *node) {
    if (!node) return;
    node->val = NULL;
    free(node);
}

