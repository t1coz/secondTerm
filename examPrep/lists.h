#ifndef EXAMPREP2SEM_LISTS_H
#define EXAMPREP2SEM_LISTS_H
#include <stdio.h>
#include <string.h>
typedef struct list{
    int data;
    struct list *next;
}list;
typedef struct listTwo{
    int data;
    struct listTwo *next;
    struct listTwo *prev;
}listTwo;
typedef struct ringTwo{
    char inf[50];
    struct ringTwo *prev, *next;
}ringTwo;
#endif
