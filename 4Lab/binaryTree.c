#include "binaryTree.h"
#include "menuFunctions.h"
Node* newNode(const char* question) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->question = strdup(question);
    node->yes = NULL;
    node->no = NULL;
    return node;
}
void insertingObject(Node* node, const char* question, const char* answer){
    if (strcmp(answer, "y") == 0){
        if (node->yes == NULL){
            node->yes = newNode(question);
        }else{
            insertingObject(node->yes, question, answer);
        }
    }else if (strcmp(answer, "n") == 0){
        if (node->no == NULL){
            node->no = newNode(question);
        }else{
            insertingObject(node->no, question, answer);
        }
    }
}
void actualGame(Node* node, Node*** answers, int* answersSize){
    if(node == NULL){
        printf("\n\033[0;31mThere is no data.\033[0m\n");
        return;
    }
    if(node->yes == NULL){
        printf("\033[0;33mIs it\033[0m \033[0;34m%s\033[0m (y/n)\n", node->question);
    }else{
        printf("\033[0;33m%s\033[0m (y/n)\n", node->question);
    }
    char* answer;
    while(strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0){
        getStr(&answer);
    }
    if (strcmp(answer, "y") == 0){
        *answers = realloc(*answers, (*answersSize + 1) * sizeof(Node*));
        (*answers)[*answersSize] = node;
        (*answersSize)++;
        if(node->yes != NULL){
            actualGame(node->yes, answers, answersSize);
        }else{
            printf("\n\033[0;35m---------------------------------------------\n");
            printf("\nI got it right! (*^‿^*)\n");
            printf("\n---------------------------------------------\033[0m\n");
        }
    }else if (strcmp(answer, "n") == 0) {
        if(node->no != NULL){
            actualGame(node->no, answers, answersSize);
        }else{
            printf("\n\033[0;35mI lost (￣ヘ￣)\033[0m\nWhat did you guess?\n");
            char* additionalObject;
            char* newQuestion;
            getStr(&additionalObject);
            printf("Write an distinguishing question for your object: ");
            getStr(&newQuestion);
            Node* newQuestionNode = newNode(newQuestion);
            Node* newObjectNode = newNode(additionalObject);
            newQuestionNode->yes = newObjectNode;
            node->no = newQuestionNode;
            printf("Ok, got it.\nThe database's been updated.\n");
        }
    }
}
int findClosingBracket(const char* row){
    int bracketsCount = 0;
    int endIndex = 0;
    for(int i = 0; i < (int)strlen(row); i++){
        if(row[i] == '[')
            bracketsCount++;
        if(row[i] == ']'){
            bracketsCount--;
            if(bracketsCount == 0){
                endIndex = i;
                break;
            }
        }
    }
    return endIndex;
}
void furtherParsing(Node** node, const char* fileRow, const char* yesBeginning, const char* answerChecking) {
    if(yesBeginning != NULL && strcmp(answerChecking, "yes") == 0){
        int finalBracket = findClosingBracket(yesBeginning);
        char* yesEnd = calloc(finalBracket - 5, sizeof(char));
        strncpy(yesEnd, yesBeginning + 6, finalBracket - 5);
        if(yesEnd != NULL){
            (*node)->yes = nodeParsing(yesEnd);
            free(yesEnd);
        }
        char* followingResponce = calloc(strlen(fileRow) - finalBracket - 2, sizeof(char));
        strncpy(followingResponce, yesBeginning + finalBracket + 2, strlen(fileRow) - finalBracket - 2);
        const char* noBeginning = strstr(followingResponce, "\"no\":[");
        if(noBeginning != NULL){
            finalBracket = findClosingBracket(noBeginning);
            char* noEnd = calloc(finalBracket - 5, sizeof(char));
            strncpy(noEnd, noBeginning + 5, finalBracket - 4);
            if(noEnd != NULL){
                (*node)->no = nodeParsing(noEnd);
                free(noEnd);
            }
        }
    }else{
        const char* noBeginning = strstr(fileRow, "\"no\":[");
        if(noBeginning != NULL){
            int end = findClosingBracket(noBeginning);
            char* noEnd = calloc(end-5, sizeof(char));
            strncpy(noEnd, noBeginning + 5, end - 5);
            if(noEnd != NULL){
                (*node)->no = nodeParsing(noEnd);
                free(noEnd);
            }
        }
    }
}
Node* nodeParsing(const char* fileRow){
    const char* questionBeginning = strstr(fileRow, "\":\"");
    if (questionBeginning == NULL)
        return NULL;
    questionBeginning += 3;
    const char* questionEnd = strchr(questionBeginning, '\"');
    if (questionEnd == NULL)
        return NULL;
    char* question = strndup(questionBeginning, questionEnd - questionBeginning);
    Node* node = newNode(question);
    const char* yesBeginning = strstr(fileRow, "\"yes\":[");
    char* answerChecking = strndup(questionEnd + 3, 3);
    furtherParsing(&node, fileRow, yesBeginning, answerChecking);
    free(question);
    free(answerChecking);
    return node;
}
Node* loadFromFile(FILE* file){
    char* fileRow = NULL;
    size_t len = 0;
    if (getline(&fileRow, &len, file) == -1)
        return NULL;
    return nodeParsing(fileRow);
}
Node* loadDatabase(const char* filePath){
    FILE* file = fopen(filePath, "r");
    if(file == NULL){
        printf("\033[31mError! File not found\033[0m\n");
        return NULL;
    }
    Node* root = loadFromFile(file);
    fclose(file);
    if(root!=NULL){
        printf("\n\033[0;32mThe database has been loaded.\033[0m\n");
    }else{
        printf("\nERROR: thr root is NULL.\n");
    }
    return root;
}
void saveToFile(Node* node, FILE* file){
    if (node == NULL)
        return;
    fprintf(file, "[");
    fprintf(file, "\"question\":\"%s\"", node->question);
    if (node->yes != NULL){
        fprintf(file, ",\"yes\":");
        saveToFile(node->yes, file);
    }
    if (node->no != NULL){
        fprintf(file, ",\"no\":");
        saveToFile(node->no, file);
    }
    fprintf(file, "]");
}
void savingDatabase(Node* root, const char* databasePath){
    FILE* file = fopen(databasePath, "w");
    if(file != NULL){
        saveToFile(root, file);
        fclose(file);
    }
    printf("\n\033[0;32mThe database has been saved.\033[0m\n");
}
void showTree(struct Node* root, Node** answers, int level, int sizeOfAnswers){
    if (root == NULL){
        return;
    }
    for (int i = 0; i < level; i++){
        printf("    ");
    }
    printf("\033[0;35m- %s\033[0m\n", root->question);
    showTree(root->yes, answers, level+1, sizeOfAnswers);
    showTree(root->no, answers, level, sizeOfAnswers);
}
void clearStructHistory(Node*** answers, int* answersSize){
    char* answer;
    printf("Do you want to clear the history? (y/n)\n");
    getStr(&answer);
    if(strcmp(answer, "y") == 0){
        free(*answers);
        *answers = malloc(sizeof(Node*));
        *answersSize = 0;
    }
}
void freeStructure(Node* node){
    if(node->question != NULL)
        free(node->question);
    if(node->yes != NULL)
        freeStructure(node->yes);
    if(node->no != NULL)
        freeStructure(node->no);
    free(node);
}
