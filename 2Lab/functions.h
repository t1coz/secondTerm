#include <stdio.h>
#include <string.h>
#ifndef ARCHIVER_FUNCTIONS_H
#define ARCHIVER_FUNCTIONS_H
int isLetter(char s);
int strLen(char* str);
int countWords(char *s);
void splittingInAnotherArray(char* str, char*** words);
int mostRepeated(char*arr, char** words);

#endif //ARCHIVER_FUNCTIONS_H
