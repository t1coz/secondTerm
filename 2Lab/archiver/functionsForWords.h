#include <stdio.h>
#include "words.h"
#include <stdlib.h>
#include <string.h>
#ifndef ARCHIVER_FUNCTIONSFORWORDS_H
#define ARCHIVER_FUNCTIONSFORWORDS_H
void createNode(struct Node *node,const  char *buffer);
void addNode(struct Node *node, const char *temp);
void popNode(struct Node *node, const char *wordRemove);
void freeList(struct Node *node);
#endif
