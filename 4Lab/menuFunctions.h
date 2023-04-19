#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef INC_4LAB_MENUFUNCTIONS_H
#define INC_4LAB_MENUFUNCTIONS_H
void menuInterface(Node* root, Node** answers);
void functionsSelection(Node** root, Node*** answers, int* sizeOfAnswers, int choice, char* userName);
int methodOfInput(int size);
void getStr(char **string);
void logger(const char* username, const char* action, const char* message);
#endif
