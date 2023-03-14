#include "menuCommands.h"
#include "boilers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void menuInterface(){
    int number = 0;
    Boiler* boilers = NULL;
    while(1){
        if(number==0){
            printf("\n\033[0;31mThere is no elements in the structure yet.\033[0m\n");
        }
        printf("\n\033[0;31mChoose what to do with the structure:\033[0m"
               "\n1. Add new element."
               "\n2. Delete existing element."
               "\n3. Sort elements by TWO characteristics."
               "\n4. Print all the elements."
               "\n5. Show the number of elements."
               "\n6. Initialize the struct."
               "\n\033[0;33m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        int choice;
        choice = methodOfInput(6);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            freeStructAndArray(&boilers, number);
            exit(0);
        }
        switch (choice) {
            case 1:
                task1NewElement(&boilers, &number);
                break;
            case 2:
                task2RemoveElement(&boilers, &number);
                break;
            case 3:
                task3SortByTwo(&boilers, &number);
                break;
            case 4:
                task4Print(&boilers, &number);
                break;
            case 5:
                task5ShowTheNumberOfElements(&number);
                break;
            case 6:
                task6Initialization(&boilers, &number);
                break;
            default:
                freeStructAndArray(&boilers, number);
                return;
        }
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
int methodOfInputChoice(int size){
    int num;
    while (scanf("%d", &num) != 1 || (!(num >=1 && num <=size)) || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
double methodOfInputDouble(){
    double num;
    while (scanf("%lf", &num) != 1 || num <=0 || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
int methodOfInputInt(){
    int num;
    while (scanf("%d", &num) != 1 || num <=0 || getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
float methodOfInputFloat(){
    float num;
    while (scanf("%f", &num) != 1 || num <=0 ||getchar() != '\n') {
        printf("Try better:\n");
        rewind(stdin);
    }
    return num;
}
void getStr(char **string){
    int size = 0;
    int realSize = 16;
    *string = (char *) malloc(realSize * sizeof(char));
    rewind(stdin);
    char check;
    while (true) {
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