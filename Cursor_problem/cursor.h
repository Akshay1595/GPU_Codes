#ifndef CURSOR_H
#define CURSOR_H

/* Necessary Includes */
#include <stdint.h>

/* Defines */
#define CUR_IMAGE_COL   (32u)
#define CUR_IMAGE_ROW   (32u)
#define CUR_IMAGE_SIZE  (4u)
#define CUR_TOTAL_SIZE  (CUR_IMAGE_SIZE * CUR_IMAGE_ROW * CUR_IMAGE_COL)

/* Data Types*/
typedef struct _cursorImage
{
    uint8_t      alpha;
    uint8_t      red;
    uint8_t      green;
    uint8_t      blue;
} cursorImage;

/* Global functions */
void cursor_PrintPixByPix(const uint8_t* buffer);
void cursor_PrintRowByCol(const uint8_t* buffer);
void cursor_GetBlackTestCursor (uint8_t** buffer);
void cursor_GetWhiteTestCursor (uint8_t** buffer);
void cursor_GetGrayTestCursor  (uint8_t** buffer);
#endif