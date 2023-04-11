#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "words.h"
#ifndef ARCHIVER_FUNCTIONS_H
#define ARCHIVER_FUNCTIONS_H
void getStr(char **string);
int cycleWord(const char *token, char *temp);

void readFile(struct Node *node, const char *fileName);

char *findMaxLenPopularWord(const struct Node *node);
int getMaxCount(const struct Node *node);
char *findMinLenRareWord(const struct Node *node);
int getMinCount(const struct Node *node);

void deleteSymbol(char *temp);
void checkTransitionToANewLine(char *temp, const char *token);
void inputSpaces(const char *buffer, char *temp, int i);
void token(char *buffer, char *temp, char **array, int size);
char** fillingVocabulary(const char *filePath, struct Node *node, int *size);
int fileCompression(const char *filePath, struct Node *node);
int fileDecompression(const char *compressedFilePath);
#endif //ARCHIVER_FUNCTIONS_H
