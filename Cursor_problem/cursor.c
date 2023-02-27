#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cursor.h"
#include "display.h"

void cursor_GetBlackTestCursor(uint8_t** buffer)
{
    *buffer = malloc(CUR_TOTAL_SIZE);
    uint32_t size = CUR_TOTAL_SIZE;
    memset(*buffer, 0x00u, size);
}

void cursor_GetWhiteTestCursor(uint8_t** buffer)
{
    *buffer = malloc(CUR_TOTAL_SIZE);
    uint32_t size = CUR_TOTAL_SIZE;
    memset(*buffer, 0xFFu, size);  
}

void cursor_GetGrayTestCursor(uint8_t** buffer)
{
    uint32_t numOfPixels = CUR_IMAGE_ROW * CUR_IMAGE_COL;
    *buffer = malloc(numOfPixels * (sizeof(cursorImage)));

    cursorImage oImage = {
        .blue  = (0xFF >> 1),
        .red   = (0xFF >> 1),
        .green = (0xFF >> 1),
        .alpha = (0xFF >> 1)
    };

    cursorImage* pImage = (cursorImage *)(*buffer);

    for (int i = 0; i < numOfPixels; i++)
    {
        memcpy(pImage, &oImage, sizeof(cursorImage));
        pImage++;
    }
}

void cursor_PrintPixByPix(const uint8_t* curBuffer)
{
    uint32_t numOfPixels    = CUR_IMAGE_COL * CUR_IMAGE_ROW;
    cursorImage* ptrImage   = (cursorImage*)curBuffer;

    printf("\n--------- Cur Printing PixByPix-----------------\n");
    for (uint32_t index = 0u; index < numOfPixels; index++) {
        printf("pixel[%02d] |",index);
        display_PrintImage(ptrImage, TYPE_CURSOR);
        ptrImage++;
    }
}

void cursor_PrintRowByCol(const uint8_t* curBuffer)
{
    uint32_t numOfPixels      = CUR_IMAGE_COL * CUR_IMAGE_ROW;
    cursorImage* ptrImage     = NULL;

    printf("\n---------Cur Printing RowByCol-----------------\n");
    for (uint32_t row = 0u; row < CUR_IMAGE_ROW; row++) {
        for (uint32_t col = 0u; col < CUR_IMAGE_COL; col++) {
            printf("CurSor[%02d][%02d] |", row, col);
            ptrImage = (cursorImage *)curBuffer;
            ptrImage = (ptrImage + (row * CUR_IMAGE_COL) + col);
            display_PrintImage(ptrImage, TYPE_CURSOR);
        }
    }
}