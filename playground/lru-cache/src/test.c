#include "lruCache.h"

void node_test();
void doubly_linked_list_test();
void hash_table_test();
void lru_cache_test();

int main(int argc, char **argv) {
    printf("\t  <===> TESTS <===>\n");
    
    node_test();
    doubly_linked_list_test();
    hash_table_test();
    lru_cache_test();

    return 0;
}

void node_test() {
    int integer = 1729;
    Node *n = newNode(&integer);
    
    assert(n != NULL);
    assert(n->val == &integer);
    
    deleteNode(n);
    printf("node_test \t\t\tPASSED\n");
}

void doubly_linked_list_test() {
    DoublyLinkedList *l = newDoublyLinkedList();

    double pi = 3.141592;
    const char *hello = "world";

    push_back(l, &pi);
    assert(l->head && l->tail);
    assert(l->head->val == l->tail->val);
    assert(l->head->val == &pi);
    assert(l->size == 1);

    push_front(l, hello);
    assert(l->head->val == hello);
    assert(l->head->val != l->tail->val);
    assert(l->tail->val == &pi);
    assert(l->size == 2);

    const void *back_val = pop_back(l);
    assert(back_val == &pi);
    assert(l->size == 1);
    
    const void *front_val = pop_front(l);
    assert(front_val == hello);
    assert(l->size == 0);
    assert(empty(l));

    deleteDoublyLinkedList(l);
    printf("doubly_linked_list_test \tPASSED\n");
}

void hash_table_test() {
    HashTable *ht = newHashTable(HT_RANGE);

    unsigned k1 = 10, v1 = 100;
    unsigned k2 = 20, v2 = 200;
    
    insert(ht, &k1, &v1);
    insert(ht, &k2, &v2);
    assert(*(unsigned *)get(ht, &k1) == 100);
    assert(*(unsigned *)get(ht, &k2) == 200);

    erase(ht, &k1);
    assert(get(ht, &k1) == NULL);

    int keys[] = {1, 2, 3, 4, 5};
    int values[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        insert(ht, &keys[i], &values[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        int *retrieved = (int *)get(ht, &keys[i]);
        assert(retrieved != NULL);
        assert(*retrieved == values[i]);
    }
    
    int new_value = 999;
    insert(ht, &keys[0], &new_value);
    int *updated = (int *)get(ht, &keys[0]);
    assert(updated != NULL);

    deleteHashTable(ht);
    printf("hash_table_test \t\tPASSED\n");
}

void lru_cache_test() {
    LRU *lru = newLRU(3);

    int k1 = 1, v1 = 100;
    int k2 = 2, v2 = 200;
    int k3 = 3, v3 = 300;
    int k4 = 4, v4 = 400;

    putLru(lru, &k1, &v1);
    putLru(lru, &k2, &v2);
    putLru(lru, &k3, &v3);

    assert(*(int *)getLru(lru, &k1) == 100);
    assert(*(int *)getLru(lru, &k2) == 200);
    assert(*(int *)getLru(lru, &k3) == 300);

    putLru(lru, &k4, &v4);
    assert(getLru(lru, &k1) == NULL);
    assert(*(int *)getLru(lru, &k4) == 400);
    assert(*(int *)getLru(lru, &k2) == 200);
    assert(*(int *)getLru(lru, &k3) == 300);

    deleteLRU(lru);
    printf("lru_cache_test \t\t\tPASSED\n");
}
