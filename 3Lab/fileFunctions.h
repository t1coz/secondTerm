#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#ifndef INC_3LAB_FILEFUNCTIONS_H
#define INC_3LAB_FILEFUNCTIONS_H
BMPImage *readingImageData(const char *filePath);
Pixel *pixelsInformation(FILE *file, const BMPImage *image);

BMPImage *readBMPFile(const char *filePath);
void writeBMP(const char *outputFilePath, const BMPImage *image);

void freeStructure(BMPImage *image);
#endif
