#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include "display.h"

void image_GetBlackTestImage (uint8_t** buffer)
{
    *buffer = malloc(IMAGE_TOTAL_SIZE);
    uint32_t size = IMAGE_TOTAL_SIZE;
    memset(*buffer, 0x00u, size);
}

void image_GetWhiteTestImage (uint8_t** buffer)
{
    *buffer = malloc(IMAGE_TOTAL_SIZE);
    uint32_t size = IMAGE_TOTAL_SIZE;
    memset(*buffer, 0xFFu, size);  
}

void image_GetGrayTestImage (uint8_t**   buffer)
{
    uint32_t numOfPixels = IMAGE_ROW * IMAGE_COL;
    *buffer = malloc(numOfPixels * (sizeof(image)));

    image oImage = {
        .blue  = (MAX_BLUE >> 1),
        .red   = (MAX_RED >> 1),
        .green = (MAX_GREEN >> 1)
    };

    image* pImage = (image *)(*buffer);

    for (int i = 0; i < numOfPixels; i++)
    {
        memcpy(pImage, &oImage, sizeof(oImage));
        pImage++;
    }
}

void image_PrintPixByPix(const uint8_t* buffer)
{
    uint32_t numOfPixels = IMAGE_COL * IMAGE_ROW;
    image* ptrImage = (image*)buffer;

    printf("\n-----------Printing PixByPix-----------------\n");
    for (uint32_t index = 0; index < numOfPixels; index++) {
        printf("pixel[%02d] |", index);
        display_PrintImage(ptrImage, TYPE_IMAGE);
        ptrImage++;
    }
}

void image_PrintRowByCol(const uint8_t* buffer)
{
    image* ptrImage = NULL;

    printf("\n-----------Printing RowByCol-----------------\n");
    for (uint32_t row = 0; row < IMAGE_ROW; row++) {
        for (uint32_t col = 0; col < IMAGE_COL; col++) {
            printf("image[%02d][%02d] |", row, col);
            ptrImage = (image *)buffer;
            ptrImage = (ptrImage + (row * IMAGE_COL) + col);
            display_PrintImage(ptrImage, TYPE_IMAGE);
        }
    }
}