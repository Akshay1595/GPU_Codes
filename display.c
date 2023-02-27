#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "image.h"
#include "cursor.h"
#include "display.h"

void display_PrintImage(const uint8_t* buffer,const uint8_t type)
{
    if (TYPE_IMAGE == type) {
        image* pImage = (image *)buffer;
        printf("\t\tr = 0x%X |\t g = 0x%X |\t b = 0x%X |\n", pImage->red, pImage->green, pImage->blue);
    } else if (TYPE_CURSOR == type) {
        cursorImage* pCurImage = (cursorImage *)buffer;
        printf("\t\talpha = 0x%X |\t r = 0x%X |\t g = 0x%X |\t b = 0x%X |\n", pCurImage->alpha ,pCurImage->red, pCurImage->green, pCurImage->blue);
    } else {
        printf("Unexpected Type\n");
        assert(0);
    }
}