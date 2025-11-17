#include "lruCache.h"

DoublyLinkedList *newDoublyLinkedList() {
    DoublyLinkedList *l = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    if (!l) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    l->size = 0; l->head = NULL; l->tail = NULL;
    return l;
}

void deleteDoublyLinkedList(DoublyLinkedList *l) {
    if (!l) return;
    for (Node *curr = l->head, *next = NULL; curr; curr = next) {
        next = curr->next;
        deleteNode(curr);
    }
    l->size = 0;
    l->head = NULL; l->tail = NULL;
    free(l);
}

size_t size(DoublyLinkedList *list) {
    return list->size;
}

bool empty(DoublyLinkedList *list) {
    return list->size == 0;
}

void push_back(DoublyLinkedList *l, const void *v) {
    if (!l || !v) return;
    Node *tmp = newNode(v);
    if (l->size == 0) {
        l->head = l->tail = tmp;
    } else {
        l->tail->next = tmp;
        tmp->prev = l->tail;
        l->tail = tmp;
    }
    l->size++;
}

void push_front(DoublyLinkedList *l, const void *v) {
    if (!l || !v) return;
    Node *tmp = newNode(v);
    assert(tmp != NULL);
    if (l->size == 0 && !l->head && !l->tail) l->head = l->tail = tmp;
    else {
        tmp->next = l->head;
        l->head->prev = tmp;
        l->head = tmp;
    }
    l->size++;
}

const void *pop_back(DoublyLinkedList *l) {
    if (!l || l->size == 0) return NULL;
    const void *val = l->tail->val;
    Node *to_delete = l->tail;

    if (l->size == 1) {
        l->head = l->tail = NULL;
    } else {
        l->tail = l->tail->prev;
        l->tail->next = NULL;
    }

    deleteNode(to_delete);
    l->size--;
    return val;
}

const void *pop_front(DoublyLinkedList *l) {
    if (!l || l->size == 0) return NULL;
    
    const void *val = l->head->val;
    Node *to_delete = l->head;
    
    if (l->size == 1) {
        l->head = l->tail = NULL;
    } else {
        l->head = l->head->next;
        l->head->prev = NULL;
    }
    
    deleteNode(to_delete);
    l->size--;
    return val;
}

