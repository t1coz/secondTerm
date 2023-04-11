#include "decompressor.h"
long int findSizeOfFIle(const char *filePath){
    FILE *textFile = fopen(filePath, "r");
    if (textFile == NULL) {
        printf("textFile is NULL.\n");
        exit(0);
    }
    fseek(textFile, 0, SEEK_END);
    long int size = ftell(textFile);
    fseek(textFile, 0, SEEK_SET);
    return size;
}
int fileDecompression(const char *compressedFilePath){
    FILE *compressedFile = fopen(compressedFilePath, "r");
    FILE *decompressedFile = fopen("deCompressedFile.txt", "w");
    if (compressedFile == NULL || decompressedFile == NULL) {
        printf("Failed to open.");
        if (compressedFile != NULL){
            fclose(compressedFile);
        }
        if (decompressedFile != NULL){
            fclose(decompressedFile);
        }
        return 1;
    }
    char buffer[4000];
    int flag = 0;
    char** vocabularyWords = NULL;
    int size = 0;
    while (fgets(buffer, 4000, compressedFile) != NULL){
        if (flag == 0){
            char *savePtr;
            const char *token = strtok_r(buffer, " \t\n", &savePtr);
            while (token != NULL){
                vocabularyWords = realloc(vocabularyWords, (size + 1) * sizeof(char *));
                vocabularyWords[size] = strdup(token);
                size++;
                token = strtok_r(NULL, " \t\n", &savePtr);
                if (token != NULL && token[0] == '\0'){
                    token = strtok_r(NULL, " \t\n", &savePtr);
                }
            }
            flag = 1;
        }else{
            char *temp = (char *) calloc(4000, sizeof(char));
            inputSpaces(buffer, temp, 0);
            token(buffer, temp, vocabularyWords, size);
            deleteSymbol(temp);
            strcat(temp, "\n");
            temp = (char *) realloc(temp, (strlen(temp) + 2) * sizeof(char));
            fprintf(decompressedFile, "%s", temp);
            free(temp);
        }
    }
    free(vocabularyWords);
    fclose(compressedFile);
    fclose(decompressedFile);
    return 0;
}
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
void checkTransitionToANewLine(char *temp, const char *token){
    if (token[strlen(token) - 1] != '\n'){
        strcat(temp, " ");
    }else{
        temp[strlen(temp) - 1] = '\0';
    }
}
void deleteSymbol(char *temp){
    while (strlen(temp) > 0 && !isalpha(temp[strlen(temp) - 1])
           && (temp[strlen(temp) - 1] != '.' && temp[strlen(temp) - 1] != ',')){
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
