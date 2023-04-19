#include <stdio.h>
#include <stdlib.h>
#ifndef INC_4LAB_LIBRARY_H
#define INC_4LAB_LIBRARY_H
typedef struct Node Node;
struct Node{
    char* question;
    Node* yes;
    Node* no;
};
void clearStructHistory(Node*** answers, int* answersSize);
void freeStructure(Node* node);

void insertingObject(Node* node, const char* question, const char* answer);
void actualGame(Node* node, Node*** answers, int* answersSize, char* userName);

int findClosingBracket(const char* row);
void furtherParsing(Node** node, const char* fileRow, const char* yesBeginning, const char* answerChecking);
Node* nodeParsing(const char* fileRow);
Node* loadFromFile(FILE* file);
Node* loadDatabase(const char* filePath);

void saveToFile(Node* node, FILE* file);
void savingDatabase(Node* root, const char* databasePath);

void showTree(struct Node* root, Node** answers, int level, int sizeOfAnswers);
#endif
