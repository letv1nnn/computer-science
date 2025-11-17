#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

# define HT_RANGE 100

typedef struct Pair { void *key; void *value; } Pair;
// node function prototypes:
typedef struct Node { struct Node *next; struct Node *prev; const void *val; } Node;
Node *newNode(const void *val);
void deleteNode(Node *node);

// doubly-linked list function prototypes:
typedef struct { Node *head; Node *tail; size_t size; } DoublyLinkedList;
DoublyLinkedList *newDoublyLinkedList();
void deleteDoublyLinkedList(DoublyLinkedList *list);
void push_front(DoublyLinkedList *list, const void *val);
void push_back(DoublyLinkedList *list, const void *val);
const void *pop_back(DoublyLinkedList *list);
const void *pop_front(DoublyLinkedList *list);
size_t size(DoublyLinkedList *list);
bool empty(DoublyLinkedList *list);

// hash-table
typedef struct HashTable { size_t range; DoublyLinkedList **buckets; } HashTable;
HashTable *newHashTable(size_t range);
void deleteHashTable(HashTable *ht);
void insert(HashTable *ht, void *key, void *val);
void *get(HashTable *ht, void *key);
void erase(HashTable *ht, void *key);

// LRU Cache
typedef struct { void *key; void *value; } LRUNode;
typedef struct { size_t capacity; size_t currSize; DoublyLinkedList *list; HashTable *ht; } LRU;
LRU *newLRU(size_t capacity);
void deleteLRU(LRU *lru);
void *getLru(LRU *lru, void *key);
void putLru(LRU *lru, void *key, void *val);
void printLRU(LRU *lru);
