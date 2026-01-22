// MIPT (2023-2024), seminar 4.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *buildAL(int *arr, int n);
Node *newNode(void);
void freeLL(Node *head);
void printLL(Node *head);

int main(int argc, char **argv) {
    int *arr; int n;
    if (argc > 1) {
        n = argc - 1;
        arr = (int *)calloc(n, sizeof(int));
        if (!arr) {
            perror("memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; ++i)
            arr[i] = atoi(argv[i + 1]);
    } else {
        fprintf(stderr, "No arguments are given\n");
        return 1;
    }

    Node *head = buildAL(arr, n);
    printLL(head);
    freeLL(head);

    return 0;
}

Node *newNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return node;
}

Node *buildAL(int *arr, int n) {
    Node *even = newNode(), *odd = newNode();
    Node *currEven = even, *currOdd = odd, *prevOdd = NULL;

    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            currEven->val = arr[i];
            currEven->next = (i < n - 1) ? (struct Node *)newNode() : NULL;
            currEven = (Node *)currEven->next;
        } else {
            currOdd->val = arr[i];
            currOdd->next = (i < n - 1) ? (struct Node *)newNode() : NULL;
            prevOdd = currOdd;
            currOdd = (Node *)currOdd->next;
        }
    }
    if (prevOdd) free(currOdd);
    currEven = even;
    while (currEven->next)
       currEven = currEven->next;
    currEven->next = odd; 

    return even;
}

void printLL(Node *head) {
    for (Node *curr = head; curr; curr = (Node *)curr->next) {
        printf("%d", curr->val);
        if (curr->next) printf(" -> ");
    }
    printf("\n");
}

void freeLL(Node *head) {
    while (head) {
        Node *tmp = (Node *)head->next;
        free(head);
        head = tmp;
    }
}
