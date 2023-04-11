#ifndef ARCHIVER_WORDS_H
#define ARCHIVER_WORDS_H
struct Words{
    char word[100];
    struct Words *next;
    struct Words *prev;
    int count;
};
struct Node{
    int size;
    struct Words *head;
    struct Words *tail;
};
#endif
