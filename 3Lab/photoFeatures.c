#include "photoFeatures.h"
#include "menuFunctions.h"
#include "structures.h"
void convertNegative(const BMPImage *image, unsigned int height, unsigned int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            Pixel pixel = image->pixels[i][j];
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            pixel.blue = 255 - pixel.blue;
            image->pixels[i][j] = pixel;
        }
    }
}
void convertBlackAndWhite(const BMPImage *image, unsigned int height, unsigned int width){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            Pixel pixel = image->pixels[i][j];
            char grayscalePixel = (char)((0.3 * pixel.red) + pixel.blue * 0.11 + pixel.green * 0.59);
            pixel.red = grayscalePixel;
            pixel.green = grayscalePixel;
            pixel.blue = grayscalePixel;
            image->pixels[i][j] = pixel;
        }
    }
}
void gammaCorrectionAboba(const BMPImage *image, unsigned int  height, unsigned int  width, double gamma){
    double invertedGamma = 1.0/gamma;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            image->pixels[i][j].red = (char)(pow(image->pixels[i][j].red / 255.0, invertedGamma) * 255.0);
            image->pixels[i][j].green = (char)(pow(image->pixels[i][j].green / 255.0, invertedGamma) * 255.0);
            image->pixels[i][j].blue = (char)(pow(image->pixels[i][j].blue / 255.0, invertedGamma) * 255.0);
        }
    }
}
int min(int a, int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
void gammaCorrection(const BMPImage *image, unsigned int height, unsigned int  width, double gamma){
    double invertedGamma = 1.0/gamma;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double red = (255.0 * pow(image->pixels[i][j].red / 255.0,  invertedGamma));
            double green = (255.0 * pow(image->pixels[i][j].green / 255.0, invertedGamma));
            double blue = (255.0 * pow(image->pixels[i][j].blue / 255.0, invertedGamma));
            image->pixels[i][j].red = (char)red;
            image->pixels[i][j].green = (char)green;
            image->pixels[i][j].blue = (char)blue;
        }
    }
}
int compareForMedian(const void *a, const void *b){
    const int *aa = (int *)a;
    const int *bb = (int *)b;
    return (*aa > *bb) - (*aa < *bb);
}
void medianFilter(const BMPImage *bmp, int frameSize, unsigned int height, unsigned int width){
    if (frameSize % 2 == 0) {
        frameSize++;
    }
    int pad = frameSize / 2;

    Pixel **pdPixels = malloc(sizeof(Pixel *) * (height + 2 * pad));
    for (int i = 0; i < height + 2 * pad; i++) {
        pdPixels[i] = malloc(sizeof(Pixel) * (width + 2 * pad));
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pdPixels[i + pad][j + pad] = bmp->pixels[i][j];
        }
    }
    for (int i = 0; i < pad; i++) {
        for (int j = 0; j < width + 2 * pad; j++) {
            pdPixels[i][j] = pdPixels[pad][j];
            pdPixels[height + 2 * pad - i - 1][j] = pdPixels[height + pad - 1][j];
        }
    }
    for (int i = 0; i < height + 2 * pad; i++) {
        for (int j = 0; j < pad; j++) {
            pdPixels[i][j] = pdPixels[i][pad];
            pdPixels[i][width + 2 * pad - j - 1] = pdPixels[i][width + pad - 1];
        }
    }
    for (int i = pad; i < height + pad; i++) {
        for (int j = pad; j < width + pad; j++) {
            unsigned int r[frameSize * frameSize];
            unsigned int g[frameSize * frameSize];
            unsigned int b[frameSize * frameSize];
            int k = 0;
            for (int ii = -pad; ii <= pad; ii++) {
                for (int jj = -pad; jj <= pad; jj++) {
                    r[k] = pdPixels[i + ii][j + jj].red;
                    g[k] = pdPixels[i + ii][j + jj].green;
                    b[k] = pdPixels[i + ii][j + jj].blue;
                    k++;
                }
            }

            qsort(r, frameSize * frameSize, sizeof(unsigned int), compareForMedian);
            qsort(g, frameSize * frameSize, sizeof(unsigned int), compareForMedian);
            qsort(b, frameSize * frameSize, sizeof(unsigned int), compareForMedian);

            bmp->pixels[i - pad][j - pad].red = r[frameSize * frameSize / 2];
            bmp->pixels[i - pad][j - pad].green = g[frameSize * frameSize / 2];
            bmp->pixels[i - pad][j - pad].blue = b[frameSize * frameSize / 2];
        }
    }

    for (int i = 0; i < height + 2 * pad; i++) {
        free(pdPixels[i]);
    }
    free(pdPixels);
}