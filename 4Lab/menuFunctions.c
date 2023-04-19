#include "menuFunctions.h"
#include "binaryTree.h"
void functionsSelection(Node** root, Node*** answers, int* sizeOfAnswers, int choice, char* userName){
    char *dataBasePath;
    switch (choice) {
        case 1:
            if (*sizeOfAnswers > 0)
                clearStructHistory(answers, sizeOfAnswers);
            if(root != NULL && answers != NULL) {
                logger(userName, "started the game", "y");
                actualGame(*root, answers, sizeOfAnswers, userName);
            }else{
                printf("Error during loading database :/");
                logger(userName, "Error during loading database", "n");
            }
            break;
        case 2:
            printf("Enter the path of the database you want to load: ");
            getStr(&dataBasePath);
            (*root) = loadDatabase(dataBasePath);
            logger(userName, "loaded the database", "y");
            break;
        case 3:
            printf("Enter the path for saving the database: ");
            getStr(&dataBasePath);
            savingDatabase(*root, dataBasePath);
            logger(userName, "saved the database", "y");
            break;
        case 4:
            if(root != NULL){
                showTree(*root, *answers, 0, *sizeOfAnswers);
                logger(userName, "printed the database", "y");
            }else{
                printf("\n\033[0;31mDatabase is not loaded or empty.\033[0m\n");
                logger(userName, "Error during printing database", "n");
            }
            break;
        default:
            break;
    }
}
void menuInterface(Node* root, Node** answers){
    int sizeOfAnswers = 0;
    printf("\nTheme: \033[0;36mOutfit.\033[0m\n");
    char* userName;
    printf("\nEnter the username: ");
    getStr(&userName);
    printf("\n");
    logger(userName, "user has signed up","y");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Play the game;"
               "\n2. Load an existing tree;"
               "\n3. Save the tree;"
               "\n4. Print the tree."
               "\n\033[0;31m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        int choice;
        choice = methodOfInput(4);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            logger(userName, "finished the program", "y");
            return;
        }
        printf("\n");
        functionsSelection(&root, &answers, &sizeOfAnswers, choice, userName);
    }
}
int methodOfInput(int size){
    int num;
    while (scanf("%d", &num) != 1 || (!(num >=1 && num <=size)&& num != 99) || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
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
void logger(const char* username, const char* action, const char* message){
    FILE* file = fopen("log.log", "a");
    time_t now;
    time(&now);
    fprintf(file, "%s[%s]: %s(%s)\n", ctime(&now), username, action, message);
    fclose(file);
}