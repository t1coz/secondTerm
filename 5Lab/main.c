#include "menuCommands.h"
#include "cache.h"
int main(){
    Cache* cache = cacheCreation(MAX_CACHE_SIZE);
    int choice;
    printf("\nTheme: \033[0;36mDNS and IP searching (cache).\033[0m\n");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Searching with DNS or IP in file;"
               "\n2. Add new address to the table;"
               "\n3. Add new CName to the table;"
               "\n4. Print existing cache;"
               "\n5. Clear cache;"
               "\n6. Show all the IPs entries."
               "\n\033[0;31m(Type 99 to exit the program)\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        choice = methodOfInput(6);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            cacheDeletion(cache);
            return 0;
        }
        printf("\n");
        functionsSelection(&cache, choice);
    }
}
