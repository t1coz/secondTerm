#include <stdio.h>
#include "decompressor.h"
int main(){
    char *compressedFilePath;
    char *initialFilePath;
    printf("\033[0;31mWrite COMPRESSED text file path: \033[0m");
    getStr(&compressedFilePath);
    fileDecompression(compressedFilePath);
    printf("\033[0;31mWrite INITIAL text file path to compare sizes: \033[0m");
    getStr(&initialFilePath);
    printf("\nSize of INITIAL file is \033[0;33m%ld\033[0m bytes.\n", findSizeOfFIle(initialFilePath));
    printf("Size of COMPRESSED file is \033[0;33m%ld\033[0m bytes.\n", findSizeOfFIle(compressedFilePath));
    printf("Size of DECOMPRESSED file is \033[0;33m%ld\033[0m bytes.\n", findSizeOfFIle("deCompressedFile.txt"));
    printf("\n\033[0;33mDone!\nHave a nice day\033[0m \033[0;34m\nツ\033[0m\n");
    return 0;
}
