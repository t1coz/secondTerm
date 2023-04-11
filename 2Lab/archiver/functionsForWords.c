#include "functionsForWords.h"
#include "words.h"
void createNode(struct Node *node,const  char *buffer){
    struct Words *word = (struct Words*) malloc(sizeof(struct Words));
    if (strlen(buffer) > 100){
        free(word);
        return;
    }else{
        strcpy(word->word, buffer);
    }
    word->count = 1;
    word->next = NULL;
    word->prev = node->tail;
    if (node->head == NULL){
        node->head = word;
        node->tail = word;
    }else{
        node->tail->next = word;
        word->prev = node->tail;
        node->tail = word;
    }
    node->size++;
}
void addNode(struct Node *node, const char *temp){
    struct Words *tempIterator = node->head;
    while (tempIterator != NULL){
        if (strcmp(tempIterator->word, temp) == 0){
            tempIterator->count++;
            break;
        }
        tempIterator = tempIterator->next;
    }
    if (tempIterator == NULL){
        createNode(node, temp);
    }
}
void popNode(struct Node *node, const char *wordRemove){
    struct Words *neededToRemove = node->head;
    while (neededToRemove != NULL){
        if (strcmp(neededToRemove->word, wordRemove) == 0){
            if (neededToRemove == node->head){
                node->head = neededToRemove->next;
                if (node->head != NULL){
                    node->head->prev = NULL;
                }
            }else if (neededToRemove == node->tail){
                node->tail = neededToRemove->prev;
                if (node->tail != NULL){
                    node->tail->next = NULL;
                }
            }else{
                neededToRemove->prev->next = neededToRemove->next;
                neededToRemove->next->prev = neededToRemove->prev;
            }
            free(neededToRemove);
            node->size --;
            return;
        }
        neededToRemove = neededToRemove->next;
    }
}
void freeList(struct Node *node){
    struct Words *current = node->head;
    while (current != NULL) {
        struct Words *next = current->next;
        free(current);
        current = next;
    }
    node->head = NULL;
    node->tail = NULL;
    node->size = 0;
}