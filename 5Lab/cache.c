#include "cache.h"
#include "functionsForFile.h"
unsigned int hashFunction(const char* str){
    unsigned int hash = 0;
    int i;
    for (i = 0; i < strlen(str); i++) {
        hash = (hash * 47 + str[i]) % HASH_SIZE;
    }
    return hash;
}
Cache* cacheCreation(int capacity){
    Cache* cache = (Cache*) malloc(sizeof(Cache));
    cache->size = 0;
    cache->capacity = capacity;
    cache->table = (CacheNode**)calloc(HASH_SIZE, sizeof(CacheNode*));
    cache->list = (CacheList*)malloc(sizeof(CacheList));
    cache->list->head = NULL;
    cache->list->tail = NULL;
    return cache;
}
void addToCache(Cache* cache, const char* key, const char* value){
    unsigned int hash = hashFunction(key);
    CacheNode* node = cache->table[hash];
    CacheNode* prev = NULL;
    while (node != NULL){
        if (strcmp(node->key, key) == 0) {
            if (prev != NULL){
                prev->next = node->next;
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                node->prev = NULL;
                node->next = cache->table[hash];
                cache->table[hash]->prev = node;
                cache->table[hash] = node;
            }
            // Update the position in the list
            if (cache->list->head != node) {
                if (node->next != NULL) {
                    node->next->prev = node->prev;
                } else {
                    cache->list->tail = node->prev;
                }
                node->prev->next = node->next;
                node->prev = NULL;
                node->next = cache->list->head;
                cache->list->head->prev = node;
                cache->list->head = node;
            }
            return;
        }
        prev = node;
        node = node->next;
    }
    node = (CacheNode*) malloc(sizeof(CacheNode));
    node->key = strdup(key);
    node->value = strdup(value);
    node->prev = NULL;
    node->next = cache->table[hash];
    if (node->next != NULL){
        node->next->prev = node;
    }
    cache->table[hash] = node;
    cache->size++;
    // Add the node to the
    if (cache->list->head != NULL) {
        node->next = cache->list->head;
        cache->list->head->prev = node;
        cache->list->head = node;
    }else{
        cache->list->head = node;
        cache->list->tail = node;
    }
    if (cache->size > cache->capacity){
        CacheNode* LRUNode = cache->list->tail;
        cache->list->tail = LRUNode->prev;
        if (cache->list->tail != NULL) {
            cache->list->tail->next = NULL;
        } else {
            cache->list->head = NULL;
        }
        unsigned int LRUHash = hashFunction(LRUNode->key);
        if (cache->table[LRUHash] == LRUNode) {
            cache->table[LRUHash] = NULL;
        }
        free(LRUNode->key);
        free(LRUNode->value);
        free(LRUNode);
        cache->size--;
    }
}
char* getFromCache(Cache* cache, char* key){
    unsigned int hash = hashFunction(key);
    CacheNode *node = cache->table[hash];
    while (node != NULL){
        if (strcmp(node->key, key) == 0){
            if (cache->list->head != node){
                if (node->next != NULL){
                    node->next->prev = node->prev;
                }else{
                    cache->list->tail = node->prev;
                }
                node->prev->next = node->next;
                node->prev = NULL;
                node->next = cache->list->head;
                cache->list->head->prev = node;
                cache->list->head = node;
            }
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}
char* findFromCache(Cache* cache, FILE* file, char* key, int* addNew){
    char* result = getFromCache(cache, key);
    if (result != NULL){
        if (cache->size == 1)
            (*addNew)++;
        return result;
    }
    rewind(file);
    char currentWord[MAX_WORD_LENGTH];
    char prevWord[MAX_WORD_LENGTH];
    int found = 0;
    while (fscanf(file, "%s", currentWord) == 1){
        if (isdigit(key[0])){
            if (found){
                result = strdup(prevWord);
                break;
            }
            if (wordComparison(currentWord, key)){
                found = 1;
                continue;
            }
            strcpy(prevWord, currentWord);
        }
        if (isalpha(key[0])){
            if (found) {
                if (isalpha(currentWord[0])) {
                    result = findFromCache(cache, file, currentWord, addNew);
                    break;
                }
                result = strdup(currentWord);
                break;
            }
            if (wordComparison(currentWord, key)){
                found = 1;
                continue;
            }
        }
    }
    if (wordComparison(currentWord, key)){
        result = strdup(prevWord);
    }
    return result;
}
void cachePrinting(Cache* cache){
    CacheNode* node = cache->list->head;
    int num = 1;
    printf("Current cache:\n");
    while (node != NULL){
        printf("%d: %s | %s\n", num, node->key, node->value);
        node = node->next;
        num++;
    }
    if(num == 1)
        printf("The cache is empty.\n");
}
void cacheDeletion(Cache* cache){
    CacheNode* node = cache->list->head;
    while (node != NULL) {
        CacheNode* next = node->next;
        free(node->key);
        free(node->value);
        free(node);
        node = next;
    }
    free(cache->list);
    free(cache->table);
    free(cache);
}