#ifndef INC_5LAB_CACHE_H
#define INC_5LAB_CACHE_H
#define DNS 100
#define MAX_WORD_LENGTH 256
#define MAX_CACHE_SIZE 3
#define HASH_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct CacheNode{
    char* key;
    char* value;
    struct CacheNode* prev;
    struct CacheNode* next;
}CacheNode;

typedef struct CacheList{
    CacheNode *head;
    CacheNode *tail;
}CacheList;

typedef struct Cache{
    int size;
    int capacity;
    CacheNode** table;
    CacheList* list;
}Cache;

unsigned int hashFunction(const char* str);

Cache* cacheCreation(int capacity);
void addToCache(Cache* cache, const char* key, const char* value);
char* getFromCache(Cache* cache, char* key);
char* findFromCache(Cache* cache, FILE* file, char* key, int* addNew);
void cachePrinting(Cache* cache);
void cacheDeletion(Cache* cache);
#endif
