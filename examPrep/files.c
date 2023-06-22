#include <stdlib.h>
#include <io.h>
#include "files.h"
int chsize(int handle, long size);
void deleteFromTheRange(int argc,char* argv[]){
    if (argc<3) return;
    FILE* file = fopen (argv[1], "rb+");
    if (file == NULL) return;
    int min = atoi (argv[2]);
    int max = atoi (argv[3]);
    int fr = 0;
    int initialOffset = 0;
    for (;;){
        int symb = fgetc(file);
        if (symb == EOF) break;
        fseek (file, initialOffset, 0);
        fputc (symb, file);
        fseek (file, ++fr, 0);
        if (symb < min || symb > max) initialOffset++;
    }
    chsize (fileno(file), initialOffset);
    fclose(file);
}
void binarySelectionSort(){
    FILE *f;
    int i, j, i1, i2;
    long l,step;
    f=fopen("ccc.bin","r+b");
    rewind(f);
    fseek(f, 0L, SEEK_END);
    l = ftell(f);
    rewind(f);
    step= l / sizeof(int);
    for(i=0; i < step; i++){
        fseek (f,i*sizeof(int),0);
        fread (&i1,sizeof(int),1,f);
        j=i-1;
        if(j>=0){
            fseek (f,j*sizeof(int),0);
            fread (&i2,sizeof(int),1,f);
        }
        while(j>=0 && i1<i2){
            fseek (f,(j+1)*sizeof(int),0);
            fwrite (&i2,sizeof(int),1,f);
            j--;
            fseek (f,j*sizeof(int),0);
            fread (&i2,sizeof(int),1,f);
        }
        j++;
        fseek (f,j*sizeof(int),0);
        fwrite(&i1,sizeof(int),1,f);
    }
    fclose(f);
}
void selectionSort(){
    int i = 1, j, k, kk, flag=0, ind;
    FILE* f = fopen("aboba.txt", "r+");
    while (1){
        fseek(f,3*i,0);
        fscanf(f,"%3d",&k);
        if(feof(f)) flag = 1;
        j = i--;
        fseek(f, 3*j, 0);
        fscanf(f, "%3d", &kk);
        ind = 0;
        while(j>=0 && k<kk){
            fseek(f, 3*(j+1), 0);
            fprintf(f,"%3d", kk);
            j--;
            if(j<=0) rewind(f);
            else fseek (f, 3*j, 0);
            fscanf(f, "%3d", &kk);
            ind = 1;
        }
        if(ind){
            fseek(f, 3*(j+1), 0);
            fprintf(f, "3d",k);
        }
        if(flag)break;
        i++;
    }
    fclose(f);
}
void ascendingDecreasingSortToDecreasing(){
    int t1, t2, flag = 0;
    fpos_t *n1 = 0, *n2 = 0;
    FILE *file1, *file2, *file3;
    file1 = fopen("vozr.txt", "rb");
    file2 = fopen("ub.txt", "rb");
    file3 = fopen("vozr.txt", "w+b");
    fread(&t1, sizeof(int), 1, file1);
    fseek(file2, -sizeof(int), 2);
    fgetpos(file2, n2);
    fsetpos(file2, n2);
    fread(&t2, sizeof(int), 1, file2);
    do{
        if(t1<t2){
            while (!feof(file1) && t1<t2){
                fwrite(&t1, sizeof(int), 1, file3);
                fread(&t1, sizeof(int), 1, file1);
            }
            if(feof(file1)&&t1<t2){
                fwrite(&t1, sizeof(int), 1, file3);
                t1 = flag;
            }
        }else{
            while (*n2!=0 && t1>=t2){
                fwrite(&t2, sizeof(int), 1, file3);
                *n2-=sizeof(int);
                fsetpos(file2, n2);
                fread(&t2, sizeof(int), 1, file2);
            }
            if(*n2 == 0 && t1>=t2){
                fwrite(&t2, sizeof(int), 1, file3);
                t2 = flag;
            }
        }
    } while (!feof(file1) || *n2!=0);
    if(t1!=flag) fwrite(&t1, sizeof(int), 1, file3);
    if(t2!=flag) fwrite(&t2, sizeof(int), 1, file3);
    fclose(file1);
    fclose(file2);
    fclose(file3);
}
void reverseInFile(FILE* file, fpos_t pos1, fpos_t pos2){
    if(pos1>pos2){
        return;
    }
    char l1, l2;
    fsetpos(file, &pos1);
    fscanf(file,"%c", &l1);
    fsetpos(file, &pos2);
    fscanf(file,"%c", &l2);
    fsetpos(file, &pos2);
    fprintf(file, "%c", &l1);
    fsetpos(file, &pos1);
    fprintf(file, "%c", &l2);
    pos1++;
    pos2--;
    reverseInFile(file, pos1, pos2);
}
void fileSortSelection(){
    FILE* file = fopen("text.txt", "r+");
    fpos_t pos1, pos2, pos3, pos4, posmin1, posmin2;
    int n1, n2;
    int min, fl=1;
    while(1){
        fgetpos(file, &pos1);
        fscanf(file, "%d", &min);
        fgetpos(file, &pos2);
        if(feof(file))break;
        posmin1 = pos1;
        fgetc(file);
        while(!feof(file)){
            fgetpos(file, &pos3);
            fscanf(file, "%d", &n2);
            fgetpos(file, &pos4);
            if(min > n2){
                min = n2;
                posmin1 = pos3;
                posmin2 = pos4;
            }
            if(feof(file)){
                break;
            }
            fgetc(file);
            if(posmin1 != pos1){
                reverseInFile(file, pos1, posmin2-1);
                reverseInFile(file, pos1, pos1+posmin2-1-posmin1);
                reverseInFile(file, pos1+posmin2-posmin1, posmin2-1-pos2+pos1);
                reverseInFile(file, posmin2-pos2+pos1, posmin2-1);
                pos1 = pos1 + posmin2 + posmin1;
                pos1++;
                fsetpos(file, &pos1);
            }else{
                pos2++;
                fsetpos(file, &pos2);
            }
        }
        fclose(file);
    }
}
void removeNumbersFromFile(const char* fileName){
    int number, fileNumber;
    FILE* file = fopen(fileName, "rb+");
    if (file == NULL){
        printf("Error;\n");
        return;
    }
    printf("Enter the numbers to delete: ");
    while(1){
        scanf("%d", &number);
        if(number == 0){
            break;
        }
        fseek(file, 0, SEEK_SET);
        while(fileNumber = fread(&fileNumber, sizeof(int), 1, file)){
            if(fileNumber == number){
                fseek(file, -sizeof(int), SEEK_CUR);
                fwrite(&number, sizeof(int), 1, file);
            }
        }
    }
    fclose(file);
}