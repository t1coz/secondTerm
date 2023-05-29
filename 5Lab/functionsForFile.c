#include "functionsForFile.h"
int wordComparison(char* word, char* str){
    return strcmp(word, str) == 0;
}
int IPValidation(const char* ip){
    int octet = 0;
    int num_octets = 0;
    char* line = strdup(ip);
    char* savePtr = NULL;
    char* ptr = strtok_r(line, ".\n", &savePtr);
    while (ptr != NULL){
        num_octets++;
        octet = atoi(ptr);
        if (octet < 0 || octet > 255 || (num_octets == 1 && octet == 0)) {
            free(line);
            return 0;
        }
        ptr = strtok_r(NULL, ".\n", &savePtr);
    }
    if (num_octets != 4){
        free(line);
        return 0;
    }
    free(line);
    free(ptr);
    return 1;
}
void addDNSToFile(const char* DNSName, char* IPAddress){
    FILE* file = fopen("dns.txt", "r+");
    if (file == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        char* savePtr = NULL;
        const char* DNSFromFile = strtok_r(buffer, " ", &savePtr);
        if (strcmp(DNSFromFile, DNSName) == 0){
            printf("Error: DNS '%s' already exists in file.\n", DNSName);
            fclose(file);
            return;
        }
    }
    if(IPValidation(IPAddress) == 0) {
        printf("Invalid IP Address\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    fprintf(file, "\n%s %s", DNSName, IPAddress);
    fclose(file);
}
void DNSByIPAddress(const char* IPAddress){
    FILE* file = fopen("dns.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    printDNS(IPAddress, file);
    fclose(file);
}
void printDNS(const char* IPAddress, FILE* file){
    char buffer[MAX_WORD_LENGTH];
    rewind(file);
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        char* savePtr = NULL;
        char* fileDNS = strtok_r(buffer, " \n", &savePtr);
        const char* IP = strtok_r(NULL, " \n", &savePtr);
        if (strcmp(IP, IPAddress) == 0){
            printf("%s\n", fileDNS);
            long pos = ftell(file);
            printDNS(fileDNS, file);
            fseek(file, pos, SEEK_SET);
        }
    }
}
char* wordSearching(FILE* file, Cache* cache){
    char dns[MAX_WORD_LENGTH];
    scanf("%99s", dns);
    int addNew = 0;
    char* result = findFromCache(cache, file, dns, &addNew);
    if (result != NULL)
        addToCache(cache, dns, result);
    return result;
}