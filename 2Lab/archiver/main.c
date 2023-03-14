//#include <stdio.h>
//#include <stdlib.h>
//#include "functions.h"
//int main() {
//    FILE *initial, *compressed;
//    initial = fopen("/Users/hanna/Documents/labi/2Sem/2Laba/archiver/initialTextFile.txt", "r");
//    compressed = fopen("compressed.txt", "w");
//
//    if(initial == NULL || compressed == NULL){
//        printf("There is smth wrong with one of the files.\n");
//        exit(1);
//    }
//    printf("Beginning of the compression.\n");
//
//    fclose(initial);
//    fclose(compressed);
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS   1000

int main(){
    FILE *fptr;
    char path[100];
    int i, len, index, isUnique;

    // List of distinct words
    char words[MAX_WORDS][50];
    char word[50];
    int count[MAX_WORDS];
    fptr = fopen("/Users/hanna/Documents/labi/2Sem/2Laba/archiver/initialTextFile.txt", "r");
    if (fptr == NULL){
        printf("Unable to open file.\n");
        exit(1);
    }
    for (i=0; i<MAX_WORDS; i++)
        count[i] = 0;
    index = 0;
    while (fscanf(fptr, "%s", word) != EOF){
        len = strlen(word);
        if (ispunct(word[len - 1]))
            word[len - 1] = '\0';
        isUnique = 1;
        for (i=0; i<index && isUnique; i++){
            if (strcmp(words[i], word) == 0)
                isUnique = 0;
        }
        if (isUnique){
            strcpy(words[index], word);
            count[index]++;
            index++;
        }else{
            count[i - 1]++;
        }
    }
    fclose(fptr);
    printf("\nOccurrences of all distinct words in file: \n");
    for (i=0; i<index; i++){
        printf("%-15s => %d\n", words[i], count[i]);
    }
    return 0;
}