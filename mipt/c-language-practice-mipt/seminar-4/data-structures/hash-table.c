// MIPT (2023-2024), seminar 4.3
// *** I wanted to implement evrything in just one file.
// Maths
// universal families of functions
// m is the hash power and p is a prime number greater than m
// for integers: h(x) = ((ax + b) % p) % m, a != 0
// for strings: h(c1...cl) = (Σ(from i = 1 to l)(cj * r ^ (l - i))) % p

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

# define HT_RANGE 100
# define M 10
# define W 32 
# define A 7
# define B 13

typedef struct Pair { void *key; void *value; } Pair;
typedef struct Node { struct Node *next; void *val; } Node;
typedef struct LinkedList { Node *head; size_t length; } LinkedList;
typedef struct HashTable { LinkedList **buckets; size_t range; } HashTable;

// linked list related functions
LinkedList *newLinkdeList();
void deleteLinkedList(LinkedList *linkedlist);
void push(LinkedList *linkdedlist, void *val);
void *pop(LinkedList *linkedlist);
// nodes for linked list
Node *newNode(void *val, Node *next);
void deleteNode(Node *node);
// hash table
HashTable *newHashTable();
void deleteHashTable(HashTable *hashtable);
void insert(HashTable *hashtable, void *key, void *value);
void delete(HashTable *hashtable, void *key);
void *get(HashTable *hashtable, void *key);

unsigned hashint(unsigned a, unsigned b, unsigned x) { return (a * x + b) >> (W - M); }

void test();

int main(int argc, char **argv) {
    test();
    return 0;
}

void test() {
    HashTable *ht = newHashTable();

    unsigned k1 = 10, v1 = 100;
    unsigned k2 = 20, v2 = 200;
    
    insert(ht, &k1, &v1);
    insert(ht, &k2, &v2);
    assert(*(unsigned *)get(ht, &k1) == 100);
    assert(*(unsigned *)get(ht, &k2) == 200);

    delete(ht, &k1);
    assert(get(ht, &k1) == NULL);

    deleteHashTable(ht);
}

// hash table
HashTable *newHashTable() {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    ht->range = HT_RANGE;
    ht->buckets = (LinkedList **)malloc(HT_RANGE * sizeof(LinkedList *));
    if (!ht->buckets) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ht->range; ++i)
        ht->buckets[i] = newLinkdeList();
    return ht;
}

void deleteHashTable(HashTable *hashtable) {
    for (int i = 0; i < hashtable->range; ++i)
        deleteLinkedList(hashtable->buckets[i]);
    free(hashtable);
}

void insert(HashTable *hashtable, void *key, void *value) {
    unsigned index = hashint(A, B, *(unsigned *)(key)) % hashtable->range;
    
    Pair *p = (Pair *)malloc(sizeof(Pair));
    if (!p) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    p->key = key; p->value = value;

    push(hashtable->buckets[index], p);
}

void *get(HashTable *hashtable, void *key) {
    unsigned index = hashint(A, B, *(unsigned *)(key)) % hashtable->range;
    
    Node *curr = hashtable->buckets[index]->head;
    while (curr) {
        Pair *p = (Pair *)curr->val;
        if (*(unsigned *)p->key == *(unsigned *)key) {
            return p->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void delete(HashTable *hashtable, void *key) {
    unsigned index = hashint(A, B, *(unsigned *)key) % hashtable->range;

    Node *curr = hashtable->buckets[index]->head;
    Node *prev = NULL;

    while (curr) {
        Pair *p = (Pair *)curr->val;
        if (*(unsigned *)p->key == *(unsigned *)key) {
            if (prev) prev->next = curr->next;
            else hashtable->buckets[index]->head = curr->next;

            free(p);     // free Pair
            deleteNode(curr); // free Node
            hashtable->buckets[index]->length--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// linked list related functions
LinkedList *newLinkdeList() {
    LinkedList *linkedlist = (LinkedList *)malloc(sizeof(LinkedList));
    if (!linkedlist) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    linkedlist->head = NULL; linkedlist->length = 0;
    return linkedlist;
}

void deleteLinkedList(LinkedList *linkedlist) {
    for (Node *curr = linkedlist->head, *next = NULL; curr; curr = next) {
        next = curr->next;
        deleteNode(curr);
    }
    linkedlist->length = 0;
    free(linkedlist);
}

void push(LinkedList *linkdedlist, void *val) {
    Node *node = newNode(val, NULL);
    (linkdedlist->length)++;
    if (!linkdedlist->head) {
        linkdedlist->head = node;
        return;
    }
    Node *curr;
    for (curr = linkdedlist->head; curr->next; curr = curr->next) {}
    curr->next = node;
}

void *pop(LinkedList *linkedlist) {
    if (!linkedlist->head) return NULL;
    Node *curr = linkedlist->head, *prev = NULL;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    
    if (prev) prev->next = NULL;
    else linkedlist->head = NULL;
    
    (linkedlist->length)--;
    void *val = curr->val;
    deleteNode(curr);
    return val;
}

// nodes for linked list
Node *newNode(void *val, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    node->val = val;
    node->next = (next) ? (Node *)next : NULL;
    return node;
}

void deleteNode(Node *node) {
    free(node);
}

