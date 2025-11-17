#include "lruCache.h"

LRU *newLRU(size_t capacity) {
    LRU *lru = (LRU *)malloc(sizeof(LRU));
    if (!lru) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    lru->capacity = capacity; lru->currSize = 0;
    lru->ht = newHashTable(HT_RANGE); lru->list = newDoublyLinkedList();
    return lru;
}

void deleteLRU(LRU *lru) {
    if (!lru) return;
    Node *curr = lru->list->head;
    while (curr) {
        LRUNode *data = (LRUNode *)curr->val;
        free(data);
        curr = curr->next;
    }
    deleteDoublyLinkedList(lru->list);
    deleteHashTable(lru->ht);
    free(lru);
}

void putLru(LRU *lru, void *key, void *val) {
    if (!lru || !key || !val) return;

    LRUNode *existingData = (LRUNode *)get(lru->ht, key);
    if (existingData) {
        existingData->value = val;
        getLru(lru, key);
        return;
    }
    
    LRUNode *newData = (LRUNode *)malloc(sizeof(LRUNode));
    if (!newData) {
        perror("memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newData->key = key;
    newData->value = val;
    
    if (lru->currSize >= lru->capacity) {
        LRUNode *lruData = (LRUNode *)pop_back(lru->list);
        if (lruData) {
            erase(lru->ht, lruData->key);
            free(lruData);
            lru->currSize--;
        }
    }
    
    push_front(lru->list, newData);
    insert(lru->ht, key, newData);
    lru->currSize++;
}

void *getLru(LRU *lru, void *key) {
    if (!lru || !key) return NULL;

    LRUNode *foundData = (LRUNode *)get(lru->ht, key);
    if (!foundData) return NULL;
    
    Node *curr = lru->list->head;
    while (curr) {
        LRUNode *data = (LRUNode *)curr->val;
        if (*(size_t *)data->key == *(size_t *)key) {
            if (curr->prev) curr->prev->next = curr->next;
            else lru->list->head = curr->next;
            
            if (curr->next) curr->next->prev = curr->prev;
            else lru->list->tail = curr->prev;
            
            lru->list->size--;
            
            curr->prev = NULL;
            curr->next = lru->list->head;
            if (lru->list->head) lru->list->head->prev = curr;
            lru->list->head = curr;
            if (!lru->list->tail) lru->list->tail = curr;
            lru->list->size++;
            
            return foundData->value;
        }
        curr = curr->next;
    }
    
    return NULL;
}

void printLRU(LRU *lru) {
    if (!lru) return;
    printf("LRU Cache (size: %zu/%zu): ", lru->currSize, lru->capacity);
    
    Node *curr = lru->list->head;
    while (curr) {
        LRUNode *data = (LRUNode *)curr->val;
        printf("[key: %zu, val: %d] ", *(size_t *)data->key, *(int *)data->value);
        curr = curr->next;
    }
    printf("\n");
}

