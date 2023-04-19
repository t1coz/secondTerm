#include "menuFunctions.h"
#include "binaryTree.h"
void functionsSelection(Node** root, Node*** answers, int* sizeOfAnswers, int choice){
    char *dataBasePath;
    switch (choice) {
        case 1:
            if (*sizeOfAnswers > 0)
                clearStructHistory(answers, sizeOfAnswers);
            if(root != NULL && answers != NULL)
                actualGame(*root, answers, sizeOfAnswers);
            else
                printf("Error during loading database :/");
            break;
        case 2:
            printf("Enter the path of the database you want to load: ");
            getStr(&dataBasePath);
            (*root) = loadDatabase(dataBasePath);
            break;
        case 3:
            printf("Enter the path for saving the database: ");
            getStr(&dataBasePath);
            savingDatabase(*root, dataBasePath);
            break;
        case 4:
            if(root != NULL)
                showTree(*root, *answers, 0, *sizeOfAnswers);
            else
                printf("\n\033[0;31mDatabase is not loaded or empty.\033[0m\n");
            break;
        default:
            printf("");
    }
}
void menuInterface(Node* root, Node** answers){
    int sizeOfAnswers = 0;
    printf("\nTheme: \033[0;36mOutfit.\033[0m\n");
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
            if(root!=NULL){
                freeStructure(root);
            }
            free(answers);
            exit(0);
        }
        printf("\n");
        functionsSelection(&root, &answers, &sizeOfAnswers, choice);
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
