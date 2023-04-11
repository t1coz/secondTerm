#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef DEARCHIVER_DECOMPRESSOR_H
#define DEARCHIVER_DECOMPRESSOR_H
long int findSizeOfFIle(const char *filePath);
int fileDecompression(const char *compressedFilePath);
void getStr(char **string);
void checkTransitionToANewLine(char *temp, const char *token);
void deleteSymbol(char *temp);
void inputSpaces(const char *buffer, char *temp, int i);
void token(char *buffer, char *temp, char **array, int size);
#endif //DEARCHIVER_DECOMPRESSOR_H
