#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

/* Type of image to print */
#define TYPE_CURSOR     (1u)
#define TYPE_IMAGE      (0u)

void display_PrintImage(const uint8_t* buffer,const uint8_t type);

#endif