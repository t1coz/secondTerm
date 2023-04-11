#include "functions.h"
#include "words.h"
#include "functionsForWords.h"
int main(){
    struct Node node = {0, NULL, NULL};
    char *filePath;
    printf("\033[0;31mWrite INITIAL text file path: \033[0m");
    getStr(&filePath);
    readFile(&node, filePath);
    fileCompression(filePath, &node);
    freeList(&node);
    printf("\n\033[0;33mDone!\nHave a nice day\033[0m \033[0;34m\nツ\033[0m\n");
    return 0;
}