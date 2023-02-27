#ifndef IMAGE_H
#define IMAGE_H

/* Necessary Includes */
#include <stdint.h>

/* Defines */
#define IMAGE_COL           (64u)
#define IMAGE_ROW           (48u)
#define IMAGE_SIZE          (2u)
#define IMAGE_TOTAL_SIZE    (IMAGE_SIZE * IMAGE_ROW * IMAGE_COL)

/* Bits for each color inside pixel */
#define BITS_FOR_RED        (5u)
#define BITS_FOR_GREEN      (6u)
#define BITS_FOR_BLUE       (5u)

/* Bit offset in 16 bit int for each color */
#define BIT_OFFSET_RED      (0u)
#define BIT_OFFSET_GREEN    (5u)
#define BIT_OFFSET_BLUE     (11u)

/* Max value for each color */
#define MAX_RED        (0x1Fu)
#define MAX_GREEN      (0x3Fu)
#define MAX_BLUE       (0x1Fu)

/* Data Type*/
typedef struct _image
{
    uint16_t    red:BITS_FOR_RED;
    uint16_t    green:BITS_FOR_GREEN;
    uint16_t    blue:BITS_FOR_BLUE;
} image;

/* Global functions */
void image_PrintPixByPix(const uint8_t*  buffer);
void image_PrintRowByCol(const uint8_t*  buffer);
void image_GetBlackTestImage(uint8_t**   buffer);
void image_GetWhiteTestImage(uint8_t**   buffer);
void image_GetGrayTestImage (uint8_t**   buffer);

#endif