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
        temp[i++] = (char)tolower(token[j]);
    }
    temp[i] = '\0';
    return i;
}
void readFile(FILE* textFile, struct Unit *unit, const char *filePath){
    char *savePtr;
    char buffer[50];
    char temp[50];
    while (fscanf(textFile, "%s", buffer) != EOF){
        temp[0] = '\0';
        const char *token = strtok_r(buffer, " \t\n", &savePtr);
        while (token != NULL) {
            int i;
            i = cycleWord(token,temp);
            if (i > 0) {
                newNode(unit,temp);
            }
            token = strtok_r(NULL, " \t\n",&savePtr);
        }
    }
    fclose(textFile);
}
char* findMaxLenWord(const struct Unit *unit){
    if (unit == NULL || unit->head == NULL)
        return NULL;
    int maxCount = 0;
    char *tempArray = NULL;
    struct Words *tempIterator = unit->head;
    while (tempIterator != NULL) {
        if (strlen(tempIterator->word) > 4 && tempIterator->count >= maxCount) {
            maxCount = tempIterator->count;
            tempArray = tempIterator->word;
        }
        tempIterator = tempIterator->next;
    }
    if (tempArray == NULL)
        return "tempArray is NULL";
    return tempArray;
}
int getMaxCount(const struct Unit *unit){
    int maxCount = 0;
    struct Words *tempIteration = unit->head;
    while (tempIteration != NULL) {
        if (tempIteration->count > maxCount) {
            maxCount = tempIteration->count;
        }
        tempIteration = tempIteration->next;
    }
    return maxCount;
}
char* findMinLenWord(const struct Unit *unit){
    if (unit == NULL || unit->head == NULL)
        return NULL;
    int minCount = unit->head->count + 1;
    char *tempArray = NULL;
    struct Words *tempIterator = unit->head;
    while (tempIterator != NULL) {
        if (strlen(tempIterator->word) < 3 && tempIterator->count <= minCount && tempIterator->count < getMaxCount(unit)) {
            minCount = tempIterator->count;
            tempArray = tempIterator->word;
        }
        tempIterator = tempIterator->next;
    }
    if (tempArray == NULL)
        return "tempArray is NULL";
    return tempArray;
}
void deleteSymbol(char *temp) {
    while (strlen(temp) > 0 && !isalpha(temp[strlen(temp) - 1]) &&
           (temp[strlen(temp) - 1] != '.' && temp[strlen(temp) - 1] != ',')){
        temp[strlen(temp) - 1] = '\0';
    }
}
void checkTransitionToANewLine(char *temp, const char *token) {
    int hasNewline = 0;
    if (token[strlen(token) - 1] != '\n') {
        strcat(temp, " ");
    }else{
        temp[strlen(temp) - 1] = '\0';
        hasNewline = 1;
    }
    if (token == NULL && !hasNewline) {
        strcat(temp, "\n");
    }
}
void inputSpaces(const char *buffer, char *temp, int i) {
    int numSpaces = 0;
    while (buffer[i] != '\0' && isspace(buffer[i])){
        if (!isalpha(buffer[i])) {
            numSpaces++;
        }
        i++;
    }
    for (int j = i; j < numSpaces; j++) {
        strcat(temp, " ");
    }
}
void token(char *buffer, char *temp, const char *word, const char *nWord){
    char *savePtr;
    const char *token = strtok_r(buffer, " \t\n", &savePtr);
    while (token != NULL){
        unsigned long len = strlen(token);
        if (len == 0){
            continue;
        }
        char lastChar = token[len - 1];
        if (!isalnum(lastChar)){
            char *wordOnly = malloc(len);
            strncpy(wordOnly, token, len - 1);
            wordOnly[len - 1] = '\0';
            if(strcmp(wordOnly, word) == 0){
                strcat(temp, nWord);
            }else if(strcmp(token, nWord) == 0) {
                strcat(temp, word);
            }else{
                strcat(temp, token);
            }
            free(wordOnly);
        }else{
            if(strcmp(token, nWord) == 0) {
                strcat(temp, word);
            }else if(strcmp(token, word) == 0) {
                strcat(temp, nWord);
            }else{
                strcat(temp, token);
            }
        }
        checkTransitionToANewLine(temp, token);
        token = strtok_r(NULL, " \t\n", &savePtr);
    }
}
int strangeCompression(const char *filePath, const char *word, const char *newWord){
    if (word == NULL || newWord == NULL) {
        printf("textFile is NULL.\n");
        return 1;
    }
    FILE *initialFile = fopen(filePath, "r");
    FILE *compressedFile = fopen("compressedFile.txt", "w");
    if (initialFile == NULL || compressedFile == NULL) {
        printf("Error during opening files in compression.");
        if (initialFile != NULL) {
            fclose(initialFile);
        }
        if (compressedFile != NULL) {
            fclose(compressedFile);
        }
        return 1;
    }
    fprintf(compressedFile, "%s %s ", word, newWord);
    char buffer[1000];
    while (fgets(buffer, 1000, initialFile) != NULL) {
        char *temp = (char *) calloc(1000, sizeof(char));
        inputSpaces(buffer, temp, 0);
        token(buffer, temp, word, newWord);
        deleteSymbol(temp);
        strcat(temp, "\n");
        temp = (char *) realloc(temp, (strlen(temp) + 2) * sizeof(char));
        fprintf(compressedFile, "%s", temp);
        free(temp);
    }
    fclose(initialFile);
    fclose(compressedFile);
    return 0;
}
int findLongPopWord(struct Unit* unit, int wordsCount){
    int mostPopularIndex = -1;
    int maxLengthCount = -1;
    int i = 0;
    struct Words *tempIterator = unit->head;
    while(tempIterator != NULL && i < wordsCount){
        if (strlen(pursuePos(unit, i)->word) > 4){
            int lengthCount = (int)strlen(pursuePos(unit, i)->word) * pursuePos(unit, i)->count;
            if (lengthCount > maxLengthCount) {
                maxLengthCount = lengthCount;
                mostPopularIndex = i;
            }
        }
        tempIterator = tempIterator->next;
        i++;
    }
    return mostPopularIndex;
}
int findMinRareWord(struct Unit* unit, int wordsCount){
    int mostRareIndex = -1;
    int minLengthCount = 100;
    int i = 0;
    struct Words *tempIterator = unit->head;
    while(tempIterator != NULL && i < wordsCount){
        if (strlen(pursuePos(unit, i)->word) <= 4 && strlen(pursuePos(unit, i)->word) > 0) {
            int lengthCount = (int)strlen(pursuePos(unit, i)->word) * pursuePos(unit, i)->count;
            if (lengthCount < minLengthCount) {
                minLengthCount = lengthCount;
                mostRareIndex = i;
            }
        }
        tempIterator = tempIterator->next;
        i++;
    }
    return mostRareIndex;
}
int getPopularLongWord(struct Unit* unit, int numWords){
    int maxLength = 0;
    int count = 0;
    int pos = -1;
    int i = 0;
    struct Words *tempIterator = unit->head;
    while (tempIterator != NULL && i < numWords){
        if (strlen(tempIterator->word) > maxLength) {
            maxLength = (int)strlen(tempIterator->word);
        }
        i++;
        tempIterator = tempIterator->next;
    }
    tempIterator = unit->head;
    for(i = 0; tempIterator != NULL && i < numWords; i++){
        if (strlen(tempIterator->word) != maxLength) {
            tempIterator = tempIterator->next;
            continue;
        }
        if (tempIterator->count > count) {
            count = tempIterator->count;
            pos = i;
        }
        tempIterator = tempIterator->next;
    }
    return pos;
}
int getUnpopularShortWord(struct Unit* unit, int numWords, int longWordCount){
    int minLength = -1;
    int pos = -1;
    int i = 0;
    struct Words *tempIterator = unit->head;
    while(tempIterator != NULL && i < numWords){
        if (tempIterator->count >= longWordCount) {
            tempIterator = tempIterator->next;
            continue;
        }
        if (strlen(tempIterator->word) < minLength || minLength == -1) {
            minLength = (int)strlen(tempIterator->word);
        }
        i++;
        tempIterator = tempIterator->next;
    }
    int minCount = -1;
    tempIterator = unit->head;
    for(i = 0; tempIterator != NULL && i < numWords; i++){
        if (strlen(tempIterator->word) == minLength && (minCount > tempIterator->count || minCount == -1)) {
            minCount = tempIterator->count;
            pos = i;
        }
        tempIterator = tempIterator->next;
    }
    return pos;
}
void compression(FILE* initialFile, struct Unit* unit, int* maxLenWordPos, int* minLenWordPos){
    FILE* compressedFile = fopen("compressedFile.txt", "w");
    if (compressedFile == NULL) {
        printf("aboba.\n");
        exit(1);
    }
    while(1){
        *maxLenWordPos = getPopularLongWord(unit, unit->size);
        if(*maxLenWordPos == -1) break;
        *minLenWordPos = getUnpopularShortWord(unit, unit->size, pursuePos(unit, *maxLenWordPos)->count);
        if(*minLenWordPos == -1){
            popAt(&unit, *maxLenWordPos);
            continue;
        }
        char* wordA = (char*)malloc(strlen(pursuePos(unit, *maxLenWordPos)->word) * sizeof(char));
        char* wordB = (char*)malloc(strlen(pursuePos(unit, *minLenWordPos)->word) * sizeof(char));
        strcpy(wordA, pursuePos(unit, *maxLenWordPos)->word);
        strcpy(wordB, pursuePos(unit, *minLenWordPos)->word);
        printCompressedFile(initialFile, compressedFile, wordA, wordB);
        printVocabSeparatorAt(compressedFile, wordA, wordB);
//        fprintf(compressedFile, "%s", pursuePos(unit, *minLenWordPos)->word);
//        fprintf(compressedFile, "%c", '@');
//        fprintf(compressedFile, "%s", pursuePos(unit, *maxLenWordPos)->word);
//        fprintf(compressedFile, "%c", '@');
//    for(int i = 0; i < unit->size; i++) {
//            if(strcmp(words[i], pursuePos(unit, *minLenWordPos)->word) == 0){
//                words[i] = pursuePos(unit, *maxLenWordPos)->word;
//            }else if(strcmp(words[i], pursuePos(unit, *maxLenWordPos)->word) == 0) {
//                words[i] = pursuePos(unit, *minLenWordPos)->word;
//            }
        //printCompressedFile(initialFile, compressedFile, wordA, wordB);
//    }
//        popAt(&unit, *minLenWordPos);
//        if(maxLenWordPos > minLenWordPos)
//            popAt(&unit, *maxLenWordPos-1);
//        else
//            popAt(&unit, *maxLenWordPos);
    }
//    fprintf(compressedFile, "\n");
//    for (int i = 0; i < unit->size; i++) {
//        if(i == unit->size-1)
//            fprintf(compressedFile, "%s", words[i]);
//        else
//            fprintf(compressedFile, "%s ", words[i]);
//    }
    fclose(compressedFile);
}
void printCompressedFile(FILE* initialFile, FILE* compressedFile, char* wordA, char* wordB){
    int size = 50;
    char* word = (char*)calloc(size,sizeof(char));
    printf("\nWordA::%s, WordB::%s", wordA, wordB);
    while (fscanf(initialFile, "%50s", word) == 1){
        unsigned long len = strlen(word);
        if (ispunct(word[len - 1])){
            char lastChar = word[len - 1];
            word[len - 1] = '\0';
            if (strcmp(word, wordA) == 0){
                fprintf(compressedFile, "%s%c ", wordB, lastChar);
            }
            else if (strcmp(word, wordB) == 0){
                fprintf(compressedFile, "%s%c ", wordA, lastChar);
            }else{
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
        }else{
            if (strcmp(word, wordA) == 0){
                fprintf(compressedFile, "%s ", wordB);
            }
            else if (strcmp(word, wordB) == 0){
                fprintf(compressedFile, "%s ", wordA);
            }
            else {
                fprintf(compressedFile, "%s ", word);
            }
        }
    }
    printf("\n");
    free(word);
}
void swapWordAAndB(FILE* initial, FILE* compressedFile, char* wordA, char* wordB){
    int size = 16;
    char* word = (char*)calloc(size,sizeof(char));
    printf("\nWordA::%s, WordB::%s", wordA, wordB);
    while (fscanf(initial, "%16s", word) == 1) {
        unsigned long len = strlen(word);
        if (ispunct(word[len - 1])) {
            char lastChar = word[len - 1];
            word[len - 1] = '\0';
            if (strcmp(word, wordA) == 0) {
                fprintf(compressedFile, "%s%c ", wordB, lastChar);
            }else if (strcmp(word, wordB) == 0) {
                fprintf(compressedFile, "%s%c ", wordA, lastChar);
            }else {
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
        }else{
            if(strcmp(word, wordA) == 0){
                fprintf(compressedFile, "%s ", wordB);
            }else if (strcmp(word, wordB) == 0){
                fprintf(compressedFile, "%s ", wordA);
            }else{
                fprintf(compressedFile, "%s ", word);
            }
        }
    }
    free(word);
}
void printVocabSeparatorAt(FILE* compressedFile, char* wordA, char* wordB){
    fseek(compressedFile, 0, SEEK_END);
    fprintf(compressedFile, "@!!!%s !!!%s ", wordA, wordB);
}
