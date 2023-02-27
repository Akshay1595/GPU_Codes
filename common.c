#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "image.h"
#include "cursor.h"
#include "common.h"
#include "display.h"

/* ----------------------------- Declarations ----------------------------- */
static void             common_Blend(image *const backgroundPixel, const cursorImage *foregroundPixel);
static inline bool      common_CheckValidXY(uint8_t x, uint8_t y);
static inline           common_Min(uint32_t num1, uint32_t num2);
static inline uint8_t   common_GetEndRow(uint8_t y_coordinate);
static inline uint8_t   common_GetEndCol(uint8_t x_coordinate);

/* ---------------------------------- Code -------------------------------- */

/* Static functions*/
static inline uint8_t common_GetEndRow(uint8_t y_coordinate)
{
    return common_Min(IMAGE_ROW, (y_coordinate + CUR_IMAGE_ROW));
}

static inline uint8_t common_GetEndCol(uint8_t x_coordinate)
{
    return common_Min(IMAGE_COL, (x_coordinate + CUR_IMAGE_COL));
}

static inline common_Min(uint32_t num1, uint32_t num2)
{
    return ((num1 < num2) ? num1 : num2);
}

static inline bool common_CheckValidXY(uint8_t x, uint8_t y)
{
    return ((x < IMAGE_COL) && (y < IMAGE_ROW)) ? true : false;
}

static void common_Blend(image *const backgroundPixel, const cursorImage *foregroundPixel)
{
    float blendFactor       = ((float)(foregroundPixel->alpha) / MAX_8BIT) *  ((float)1u);
    //printf("blendFactor = %0.2f\n", blendFactor);

    /* Get 5-bit and 6-bit equivalent value of Red Green and Blue value of Cursor/Forground Pixel */
    uint8_t fg_Rvalue = (foregroundPixel->red);     fg_Rvalue = (fg_Rvalue >> 3);
    uint8_t fg_Gvalue = (foregroundPixel->green);   fg_Gvalue = (fg_Gvalue >> 2);
    uint8_t fg_Bvalue = (foregroundPixel->blue);    fg_Bvalue = (fg_Bvalue >> 3);
    //printf("before fg_Rvalue = 0x%X\t fg_Gvalue = 0x%X\t fg_Bvalue = 0x%X\n", fg_Rvalue, fg_Gvalue, fg_Bvalue);

    uint8_t bg_Rvalue = backgroundPixel->red;
    uint8_t bg_Bvalue = backgroundPixel->blue;
    uint8_t bg_Gvalue = backgroundPixel->green;
    //printf("before bg_Rvalue = 0x%X\t bg_Bvalue = 0x%X\t bg_Gvalue = 0x%X\n", bg_Rvalue, bg_Gvalue, bg_Bvalue);

    fg_Rvalue = (fg_Rvalue * blendFactor); fg_Bvalue = (fg_Bvalue * blendFactor); fg_Gvalue = (fg_Gvalue * blendFactor);
    blendFactor = (1 - blendFactor);
    bg_Rvalue = (bg_Rvalue * blendFactor); bg_Bvalue = (bg_Bvalue * blendFactor); bg_Gvalue = (bg_Gvalue * blendFactor);
    //printf("After fg_Rvalue = 0x%X\t fg_Gvalue = 0x%X\t fg_Bvalue = 0x%X\n", fg_Rvalue, fg_Gvalue, fg_Bvalue);
    //printf("After bg_Rvalue = 0x%X\t bg_Bvalue = 0x%X\t bg_Gvalue = 0x%X\n", bg_Rvalue, bg_Gvalue, bg_Bvalue);

    backgroundPixel->blue       = bg_Bvalue + fg_Bvalue;
    backgroundPixel->green      = bg_Gvalue + fg_Gvalue;
    backgroundPixel->red        = bg_Rvalue + fg_Rvalue;
}

void overlay_mouse_pointer(uint8_t* frame_buffer, uint8_t* mouse_pointer_buffer,
                           uint8_t  x_coordinate, uint8_t  y_coordinate)
{
    uint8_t end_row             = 0u;
    uint8_t end_col             = 0u;

    uint8_t cur_row             = 0u;
    uint8_t cur_col             = 0u;

    image * ptrImagePix         = NULL;
    cursorImage* pCurImagePix   = NULL;

    //printf("[%s][%d] x = %d y = %d  \n", __FILE__, __LINE__, x_coordinate, y_coordinate);

    /* Check if valid pointers are passed */
    if ((NULL == frame_buffer) || (NULL == mouse_pointer_buffer)) {
        printf("[%s][%d] Pointer to buffer is Invalid \n", __FILE__, __LINE__);
        return;
    }

    /* Check Valid Co-ordinates are passed or not */
    if (XY_INVALID == common_CheckValidXY(x_coordinate, y_coordinate)) {
        printf("[%s][%d] x = %d y = %d is Invalid \n", __FILE__, __LINE__, x_coordinate, y_coordinate);
        return;
    }

    /* Get last row and col to blend */
    end_row = common_GetEndRow(y_coordinate);
    end_col = common_GetEndCol(x_coordinate);

    //printf("[%s][%d] x = %d\t\t y = %d  \n", __FILE__, __LINE__, x_coordinate, y_coordinate);
    //printf("[%s][%d] end_col = %d\t end_row = %d\n", __FILE__, __LINE__, end_col, end_row);

    /* Blend each pixel in row by col fashion */
    for (uint8_t row = y_coordinate; row < end_row; row++) {
        for (uint8_t col = x_coordinate; col < end_col; col++) {
            //printf("[%s][%d] Image row = %d col = %d\t\t| Cursor row = %d col = %d \n", __FILE__, __LINE__, row, col, cur_row, cur_col);

            /* Get pointer to BackGround Pixel */
            ptrImagePix = (image *)frame_buffer;
            ptrImagePix = (ptrImagePix + (row * IMAGE_COL) + col);
            //printf("[%s][%d] ImagePixel before blend = ", __FILE__, __LINE__);
            //display_PrintImage((uint8_t* )ptrImagePix, TYPE_IMAGE);

            /* Get pointer to ForeGround Pixel */
            pCurImagePix = (cursorImage *)mouse_pointer_buffer;
            pCurImagePix = (pCurImagePix + (cur_row * CUR_IMAGE_COL) + cur_col);
            //printf("[%s][%d] CursorPixel before blend = ", __FILE__, __LINE__);
            //display_PrintImage((uint8_t* )pCurImagePix, TYPE_CURSOR);

            /* Blend Pixel */
            common_Blend(ptrImagePix, pCurImagePix);

            //printf("[%s][%d] ImagePixel After blend = ", __FILE__, __LINE__);
            //display_PrintImage((uint8_t* )ptrImagePix, TYPE_IMAGE);
            cur_col++;
        }
        /* Increament the cursor row */
        cur_row++;
        /* Start from column zero */
        cur_col = 0u;
    }

    return;
}