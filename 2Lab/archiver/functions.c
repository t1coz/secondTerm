#include "functions.h"
int isLetter(char s){
    if((s>='a'&&s<='z')||(s>='A'&&s<='Z'))
        return 1;
    return 0;
}
int strLen(char* str){
    int i=0;
    while (str[i]!='\0'){
        i++;
    }
    return i;
}
int countWords(char *s){
    int cnt = 0, i;
    int n = strLen(s);
    for (i = 0; i < n; i++) {
        if(isLetter(s[i])==1 && i == 0){
            cnt++;
        }
        if(isLetter(s[i])==0 && isLetter(s[i+1])==1){
            cnt++;
        }
    }
    return cnt;
}
void splittingInAnotherArray(char* str, char*** words){
    int i, j, k, wordLength , lastSymbol = 0;
    int n = strLen(str);
    int counter = 0;
    for (i = 0; i < n+1; i++) {
        if (isLetter(str[i]) == 0 || str[i] == EOF) {
            wordLength = i - lastSymbol;
            k = 0;
            for (j = lastSymbol; j <= i; j++) {
                if (j == i){
                    (*words)[counter][k] = ' ';
                    break;
                }
                (*words)[counter][k] = str[j];
                k++;
            }
            if (wordLength == 0)
                counter--;
            counter++;
            lastSymbol = i + 1;
        }
    }
}
int mostRepeated(char*arr, char** words){
    int repeatCount = 0, maxRepeat = 0, maxIndex = 0, flag = 1;
    int wordCount = countWords(arr);
    int n = strLen(arr);
    for (int j = 0; j < wordCount; j++){
        for (int i = 0; i < wordCount; i++) {
            for (int k = 0; k < n; k++){
                if (words[j][k] != words[i][k]){
                    flag = 0;
                    break;
                }
            }
            if (flag == 1){
                repeatCount++;
            }
            flag = 1;
        }
        if (maxRepeat < repeatCount){
            maxRepeat = repeatCount;
            maxIndex = j;
        }
        repeatCount = 0;
    }
    return maxIndex;
}
void outputOfTheMostFreqWord (char** words, int n, int maxIndex){
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (isLetter(words[maxIndex][i]) == 0)
            break;
        len++;
    }
    for (int i = 0; i < len ; i++)
        printf ("%c", words[maxIndex][i]);
    printf("\n");
}