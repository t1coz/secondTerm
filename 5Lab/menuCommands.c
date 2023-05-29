#include "menuCommands.h"
#include "cache.h"

void findingIP(Cache* cache){
    FILE *file = fopen("dns.txt", "r");
    if (file == NULL)
        printf("\nUnable to open the file.");
    printf("Write DNS or IP address: ");
    char* result = wordSearching(file, cache);
    if (result != NULL) {
        printf("Result: %s\n", result);
    }else{
        printf("No matches in the file.\n");
    }
    fclose(file);
}
void showAllTheIPs(){
    printf("Write IP address: ");
    char *IP;
    getStr(&IP);
    DNSByIPAddress(IP);
}
void addDns(){
    FILE *file = fopen("dns.txt", "a+");
    if (file == NULL) {
        printf("\nUnable to open the file.");
        return;
    }
    char *dns = NULL;
    char *IP = NULL;
    printf("Write DNS address: ");
    getStr(&dns);
    printf("Write IP address: ");
    getStr(&IP);
    addDNSToFile(dns, IP);
}
void addCNameAddress(){
    FILE *file = fopen("dns.txt", "a+");
    if (file == NULL) {
        printf("\nUnable to open the file.");
        exit(1);
    }
    char *dns = NULL;
    char* result = (char*)calloc(DNS, sizeof(char));
    printf("Write DNS address: ");
    getStr(&dns);
    char word[MAX_WORD_LENGTH];
    while(fscanf(file, "%s", word) == 1) {
        if(wordComparison(dns, word)) {
            printf("DNS repetition is found.\n");
            rewind(stdin);
            rewind(file);
            getStr(&dns);
        }
    }
    strcat(result, "\n");
    strcat(result, dns);
    strcat(result, " ");
    rewind(stdin);
    printf("Write CNAME address: ");
    getStr(&dns);
    int flag = 0;
    rewind(file);
    while(flag == 0) {
        while(fscanf(file, "%s", word) == 1) {
            if(wordComparison(dns, word)) {
                flag++;
            }
        }
        if(flag == 0) {
            printf("CNAME repetition is not found. Try again: ");
            rewind(stdin);
            rewind(file);
            getStr(&dns);
        }
    }
    strcat(result, dns);
    fprintf(file, "%s", result);
    free(dns);
    fclose(file);
}
//-----------------------------------------------------
void functionsSelection(Cache** cache, int choice){
    switch (choice){
        case 1:
            findingIP(*cache);
            break;
        case 2:
            addDns();
            break;
        case 3:
            addCNameAddress();
            break;
        case 4:
            cachePrinting(*cache);
            break;
        case 5:
            cacheDeletion(*cache);
            *cache = cacheCreation(MAX_CACHE_SIZE);
            break;
        case 6:
            showAllTheIPs();
            break;
        default:
            break;
    }
}
void menuInterface(Cache* cache){
    printf("\nTheme: \033[0;36mSearching in cache.\033[0m\n");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Searching with DNS first;"
               "\n2. Searching with IP first;"
               "\n3. Add DNS+IP address to the table;"
               "\n4. Write cache;"
               "\n5. Clear cache."
               "\n\033[0;31m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        int choice;
        choice = methodOfInput(5);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            return;
        }
        printf("\n");
        functionsSelection(&cache, choice);
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