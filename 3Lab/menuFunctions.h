#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#ifndef INC_3LAB_FUNCTIONS_H
#define INC_3LAB_FUNCTIONS_H
void getStr(char **string);
void menuInterface(BMPImage *image, char* filePath);

int methodOfInput(int size);
double methodOfInputDouble();
int methodOfInputInt();
double methodOfInputGamma();
int methodOfInputMedian();

void functionsSelection(const BMPImage *image, int choice);
#endif
