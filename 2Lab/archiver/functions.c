#include "functions.h"
#include "functionsForWords.h"
#include "words.h"
void getStr(char **string){
    int size = 0;
    int realSize = 16;
    *string = (char *)malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (1) {
        check = (char)getchar();
        if (check == '\n') {
            if (size + 1 < realSize) {
                *string = (char *) realloc(*string, (size + 1) * sizeof(char));
            }
            (*string)[size] = '\0';
            return;
        }
        (*string)[size] = check;
        size++;
        if (size + 1 == realSize) {
            realSize *= 2;
            *string = (char *) realloc(*string, realSize * sizeof(char));
        }
    }
}
int cycleWord(const char *token, char *temp){
    int i = 0;
    for (int j = 0; token[j]; j++){
        if (isalnum(token[j])) {
            temp[i++] = token[j];
        }
    }
    temp[i] = '\0';
    return i;
}
void readFile(struct Node *node, const char *fileName){
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("Opening error.");
        return;
    }
    char *savingPtr;
    char buffer[1000];
    char temp[1000];
    while (fgets(buffer, 1000, fp) != NULL){
        temp[0] = '\0';
        const char *token = strtok_r(buffer, " \t\n", &savingPtr);
        while (token != NULL){
            int i;
            i = cycleWord(token, temp);
            if (i > 0){
                addNode(node, temp);
            }
            token = strtok_r(NULL, " \t\n", &savingPtr);
        }
    }
    fclose(fp);
}
char *findMaxLenPopularWord(const struct Node *node){
    if (node == NULL || node->head == NULL)
        return NULL;
    int maxCount = 0;
    char *tempWord = NULL;
    struct Words *tempIterator = node->head;
    while (tempIterator != NULL){
        if (strlen(tempIterator->word) > 3 && tempIterator->count >= maxCount){
            maxCount = tempIterator->count;
            tempWord = tempIterator->word;
        }
        tempIterator = tempIterator->next;
    }

    return tempWord;
}
int getMaxCount(const struct Node *node){
    int maxCount = 0;
    struct Words *tempIterator = node->head;
    while (tempIterator != NULL) {
        if (tempIterator->count > maxCount){
            maxCount = tempIterator->count;
        }
        tempIterator = tempIterator->next;
    }
    return maxCount;
}
char *findMinLenRareWord(const struct Node *node){
    if (node == NULL || node->head == NULL) return NULL;
    int minCount = node->head->count + 1;
    char *tempArray = NULL;
    struct Words* tempIterator = node->head;
    while (tempIterator != NULL) {
        if (strlen(tempIterator->word) < 3 && tempIterator->count <= minCount &&
            tempIterator->count < getMaxCount(node)) {
            minCount = tempIterator->count;
            tempArray = tempIterator->word;
        }
        tempIterator = tempIterator->next;
    }
    return tempArray;
}
int getMinCount(const struct Node *node){
    int minCount = node->head->count + 1;
    struct Words *tempIterator = node->head;
    while (tempIterator != NULL) {
        if (tempIterator->count < minCount){
            minCount = tempIterator->count;
        }
        tempIterator = tempIterator->next;
    }
    return minCount;
}
void deleteSymbol(char *temp){
    while (strlen(temp) > 0 && !isalpha(temp[strlen(temp) - 1])
    && (temp[strlen(temp) - 1] != '.' && temp[strlen(temp) - 1] != ',')){
        temp[strlen(temp) - 1] = '\0';
    }
}
void checkTransitionToANewLine(char *temp, const char *token){
    if (token[strlen(token) - 1] != '\n'){
        strcat(temp, " ");
    }else{
        temp[strlen(temp) - 1] = '\0';
    }
}
void inputSpaces(const char *buffer, char *temp, int i){
    int numSpaces = 0;
    while (buffer[i] != '\0' && isspace(buffer[i])){
        if (!isalpha(buffer[i])){
            numSpaces++;
        }
        i++;
    }
    for (int j = 0; j < numSpaces; j++){
        strcat(temp, " ");
    }
}
void token(char *buffer, char *temp, char **array, int size){
    char *savePtr;
    const char *token = strtok_r(buffer, " \t\n", &savePtr);
    while (token != NULL) {
        int founded = 0;
        for (int i = 0; i < size; i += 2) {
            if (strcmp(token, array[i]) == 0) {
                founded = 1;
                strcat(temp, array[i + 1]);
            }else if (strcmp(token, array[i + 1]) == 0){
                founded = 1;
                strcat(temp, array[i]);
            }
            if (founded == 1)
                break;
        }
        if (founded == 0) {
            strcat(temp, token);
        }
        if (temp[0] != '\0') {
            checkTransitionToANewLine(temp, token);
        }
        token = strtok_r(NULL, " \t\n", &savePtr);
        if (token != NULL && token[0] == '\0') {
            token = strtok_r(NULL, " \t\n", &savePtr);
        }
    }
}
char** fillingVocabulary(const char *filePath, struct Node *node, int *size){
    FILE *initialFile = fopen(filePath, "r");
    if (initialFile == NULL){
        printf("Opening error.");
        return NULL;
    }
    char* wordA;
    char* wordB;
    char** vocabularyWords = NULL;
    printf("\n\033[0;34mWord pairs:\033[0m\n");
    while (1){
        if ((wordA = findMaxLenPopularWord(node)) == NULL)
            break;
        if ((wordB = findMinLenRareWord(node)) == NULL){
            popNode(node, wordA);
            continue;
        }
        if (strlen(wordA) * getMaxCount(node) < strlen(wordB) * (getMinCount(node))){
            fclose(initialFile);
            return vocabularyWords;
        }
        printf("%s --> %s;\n", wordA, wordB);
        vocabularyWords = realloc(vocabularyWords, (*size + 2) * sizeof(char*));
        vocabularyWords[*size] = strdup(wordA);
        vocabularyWords[*size + 1] = strdup(wordB);
        *size += 2;
        popNode(node, wordA);
        popNode(node, wordB);
    }
    fclose(initialFile);
    return vocabularyWords;
}
int fileCompression(const char *fileName, struct Node *node){
    FILE *initialFile = fopen(fileName, "r");
    FILE *compressedFile = fopen("compressedFile.txt", "w");
    if (initialFile == NULL || compressedFile == NULL) {
        printf("Failed to open");
        if (initialFile != NULL) {
            fclose(initialFile);
        }
        if (compressedFile != NULL) {
            fclose(compressedFile);
        }
        return 1;
    }
    int size = 0;
    char **vocabularyWords = fillingVocabulary(fileName, node, &size);
    for (int i = 0; i < size; i++) {
        fprintf(compressedFile, "%s ", vocabularyWords[i]);
    }
    fprintf(compressedFile, "\n");
    char buffer[4000];
    while (fgets(buffer, 4000, initialFile) != NULL) {
        char *temp = (char *) calloc(4000, sizeof(char));
        inputSpaces(buffer, temp, 0);
        token(buffer, temp, vocabularyWords, size);
        deleteSymbol(temp);
        strcat(temp, "\n");
        temp = (char *) realloc(temp, (strlen(temp) + 2) * sizeof(char));
        fprintf(compressedFile, "%s", temp);
        free(temp);
    }
    fclose(initialFile);
    free(vocabularyWords);
    fclose(compressedFile);
    return 0;
}