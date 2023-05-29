#ifndef INC_5LAB_MENUCOMMANDS_H
#define INC_5LAB_MENUCOMMANDS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cache.h"
#include "functionsForFile.h"
void findingIP(Cache* cache);
void showAllTheIPs();
void addDns();
void addCNameAddress();

void functionsSelection(Cache** cache, int choice);
int methodOfInput(int size);
void getStr(char **string);
#endif
