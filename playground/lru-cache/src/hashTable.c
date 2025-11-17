#include "lruCache.h"

size_t hashint(size_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % HT_RANGE;
}

HashTable *newHashTable(size_t range) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    ht->range = range;
    ht->buckets = (DoublyLinkedList **)malloc(sizeof(DoublyLinkedList *) * range);
    if (!ht->buckets) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < ht->range; ++i)
        ht->buckets[i] = newDoublyLinkedList();
    return ht;
}

void deleteHashTable(HashTable *ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->range; ++i)
        deleteDoublyLinkedList(ht->buckets[i]);
    ht->range = 0;
    free(ht);
}

void insert(HashTable *ht, void *key, void *val) {
    if (!ht || !key || !val) return;
    size_t index = hashint(*(size_t *)(key)) % ht->range;

    Pair *p = (Pair *)malloc(sizeof(Pair));
    if (!p) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    p->key = key; p->value = val;

    push_back(ht->buckets[index], p);
}

void *get(HashTable *ht, void *key) {
    if (!ht || !key) return NULL;

    size_t index = hashint(*(size_t *)(key)) % ht->range;
    
    Node *curr = ht->buckets[index]->head;
    while (curr) {
        Pair *p = (Pair *)curr->val;
        if (*(size_t *)p->key == *(size_t *)key) {
            return p->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void erase(HashTable *ht, void *key) {
    if (!ht || !key) return;

    size_t index = hashint(*(size_t *)key) % ht->range;

    Node *curr = ht->buckets[index]->head;
    Node *prev = NULL;

    while (curr) {
        Pair *p = (Pair *)curr->val;
        if (*(size_t *)p->key == *(size_t *)key) {
            if (prev) prev->next = curr->next;
            else ht->buckets[index]->head = curr->next;
            
            if (curr->next) curr->next->prev = prev;
            else ht->buckets[index]->tail = prev;

            free(p);
            deleteNode(curr);
            ht->buckets[index]->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

