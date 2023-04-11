#include "fileFunctions.h"
//BMPImage *readingImageData(const char *filePath){
//    BMPImage *image = (BMPImage *)malloc(sizeof(BMPImage));
//    if (image == NULL || !image){
//        printf("Error during memory allocation.\n");
//        return NULL;
//    }
//    FILE *file = fopen(filePath, "rb");
//    if (file == NULL || !file){
//        printf("Can't open the file.\n");
//        free(image);
//        return NULL;
//    }
//    fread(&image->fileHeader, sizeof(BMPFileHeader), 1, file);
//    if (image->fileHeader.ID[0] != 'B' || image->fileHeader.ID[1] != 'M') {
//        printf("Error, invalid format.\n");
//        fclose(file);
//        free(image);
//        return NULL;
//    }
//    fread(&image->imageHeader, sizeof(BMPImageHeader), 1, file);
//    image->pixels = pixelsInformation(file, image);
//    fclose(file);
//    if (!image->pixels) {
//        printf("Cannot read the data.\n");
//        free(image);
//        return NULL;
//    }
//    return image;
//}
//Pixel *pixelsInformation(FILE *file, const BMPImage *image){
//    unsigned dataSize = image->imageHeader.width * image->imageHeader.height;
//    unsigned bytesPerPixel = image->imageHeader.bitsPerPixel / 8;
//    unsigned rowSize = bytesPerPixel * image->imageHeader.width;
//    unsigned rowPadding = (4 - (rowSize % 4)) % 4;
//    unsigned pixelOffset = (int)image->fileHeader.pixelOffset + rowPadding;
//    fseek(file, pixelOffset, SEEK_SET);
//
//    Pixel *pixels = (Pixel *)malloc(dataSize * sizeof(Pixel));
//    char *buffer = (char *)malloc(bytesPerPixel * sizeof(char));
//    memset(buffer, 0, bytesPerPixel * sizeof(unsigned char));
//    for (int i = 0; i < dataSize; i++) {
//        fread(buffer, bytesPerPixel, 1, file);
//        if (buffer != NULL && bytesPerPixel == 3) {
//            pixels[i].blue = buffer[0];
//            pixels[i].green = buffer[1];
//            pixels[i].red = buffer[2];
//        }
//    }
//    free(buffer);
//    return pixels;
//}
BMPImage *readBMPFile(const char *filePath){
    BMPImage *image = malloc(sizeof(BMPImage));
    FILE *initialFile = fopen(filePath, "rb");
    if (initialFile == NULL || !initialFile){
        printf("Can't open the file.\n");
        free(image);
        return NULL;
    }
    fread(&image->fileHeader, sizeof(BMPFileHeader), 1, initialFile);
    if (image->fileHeader.ID[0] != 'B' || image->fileHeader.ID[1] != 'M') {
        printf("Error, invalid format.\n");
        fclose(initialFile);
        free(image);
        return NULL;
    }
    fread(&image->imageHeader, sizeof(BMPImageHeader), 1, initialFile);
    unsigned int width = image->imageHeader.width;
    unsigned int height = image->imageHeader.height;
    if(image->imageHeader.bitsPerPixel != 24){
        printf("Cannot process the file: not 24 bpp.");
        free(image);
        fclose(initialFile);
        return NULL;
    }
    if (image->imageHeader.pixelCompression) {
        printf("Cannot process the file: Compression not supported.");
        free(image);
        fclose(initialFile);
        return NULL;
    }
    image->pixels = malloc(sizeof(Pixel *) * height);
    for (int i = 0; i < height; i++) {
        image->pixels[i] = malloc(sizeof(Pixel) * width);
    }

    unsigned int offset = image->fileHeader.pixelOffset;
    fseek(initialFile, offset, SEEK_SET);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fread(&image->pixels[i][j], sizeof(Pixel), 1, initialFile);
        }
    }
    fclose(initialFile);
    return image;
}
void writeBMP(const char *outputFilePath, const BMPImage *image){
    FILE *outputFile = fopen("editedFile.bmp", "wb");
    if (outputFile == NULL) {
        printf("Error: Failed to open output file.");
        return;
    }
    unsigned int width = image->imageHeader.width;
    unsigned int height = image->imageHeader.height;

//    BMPImage tempParam;
//    tempParam.fileHeader = image->fileHeader;
//    tempParam.imageHeader = image->imageHeader;
//    tempParam.pixels = malloc(sizeof(Pixel *) * height);
//    for (int i = 0; i < height; i++) {
//        tempParam.pixels[i] = malloc(sizeof(Pixel) * width);
//    }
//    unsigned int dataSize = image->imageHeader.width * image->imageHeader.height;
//    memcpy(tempParam.pixels, image->pixels, dataSize * sizeof(Pixel));

    fwrite(&image->fileHeader, sizeof(image->fileHeader), 1, outputFile);
    fwrite(&image->imageHeader, sizeof(image->imageHeader), 1, outputFile);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&image->pixels[i][j], sizeof(Pixel), 1, outputFile);
        }
    }
    unsigned int padding = (4 - (width * 3) % 4) % 4;
    for (int j = 0; j < padding; j++) {
        fputc(0x00, outputFile);
    }
    fclose(outputFile);
}
void freeStructure(BMPImage *image){
    if (image->pixels)
        free(image->pixels);
    free(image);
}