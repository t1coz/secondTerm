#ifndef INC_5LAB_FUNCTIONSFORFILE_H
#define INC_5LAB_FUNCTIONSFORFILE_H
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int wordComparison(char* word, char* str);
int IPValidation(const char* ip);
void addDNSToFile(const char* DNSName, char* IPAddress);
void DNSByIPAddress(const char* IPAddress);
void printDNS(const char* IPAddress, FILE* file);
char* wordSearching(FILE* file, Cache* cache);

#endif
