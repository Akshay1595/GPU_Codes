#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "common.h"
#include "image.h"
#include "cursor.h"
#include "test.h"
#include "display.h"

void test1()
{
    printf("############################################## Test 1 ##############################################\n");
    uint8_t *buffer = NULL;
    image_GetGrayTestImage(&buffer);
    image_PrintRowByCol(buffer);

    uint8_t *curBuffer = NULL;
    cursor_GetGrayTestCursor(&curBuffer);
    cursor_PrintRowByCol(curBuffer);

    overlay_mouse_pointer(buffer, curBuffer, 0, 0);
    image_PrintRowByCol(buffer);    
}

void test2()
{
    printf("############################################## Test 2 ##############################################\n");
    uint8_t *buffer = NULL;
    image_GetWhiteTestImage(&buffer);
    image_PrintRowByCol(buffer);

    uint8_t *curBuffer = NULL;
    cursor_GetBlackTestCursor(&curBuffer);
    cursor_PrintRowByCol(curBuffer);

    overlay_mouse_pointer(buffer, curBuffer, IMAGE_COL-1, IMAGE_ROW-1);
    image_PrintRowByCol(buffer);
}

void test3()
{
    printf("############################################## Test 3 ##############################################\n");
    uint8_t *buffer = NULL;
    image_GetBlackTestImage(&buffer);
    image_PrintRowByCol(buffer);

    uint8_t *curBuffer = NULL;
    cursor_GetWhiteTestCursor(&curBuffer);
    cursor_PrintRowByCol(curBuffer);

    overlay_mouse_pointer(buffer, curBuffer, 0, (IMAGE_ROW-CUR_IMAGE_ROW));
    image_PrintRowByCol(buffer);
}