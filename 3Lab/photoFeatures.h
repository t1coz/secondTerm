#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structures.h"
#ifndef INC_3LAB_PHOTOFEATURES_H
#define INC_3LAB_PHOTOFEATURES_H

void convertion(const BMPImage *image, const char *fileName, int choice);

void convertBlackAndWhite(const BMPImage *image, unsigned int  height, unsigned int  width);
void convertNegative(const BMPImage *image, unsigned int  height, unsigned int  width);

int comparePixelsBrightnesses(const void *a, const void *b);
Pixel **memoryAllocationForPixels(BMPImage tempParam);
void getMedian(BMPImage tempParam, Pixel frame[], int *index, int x, int y, int frameWidth , int frameHeight);
void medianFilter(const BMPImage *bmp, int frameSize, unsigned int height, unsigned int width);
int findingMedian(unsigned char arr[], int n);
void medianFilter2(BMPImage image, int median);

void gammaCorrection(const BMPImage *image, unsigned int  height, unsigned int  width, double gamma);
double power(double base, int exp);
int comparisonIfMin(int a, int b);
int comparisonIfMmax(int a, int b);

#endif
