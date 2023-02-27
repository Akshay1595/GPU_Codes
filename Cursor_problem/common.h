#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define XY_INVALID      (0u)
#define XY_VALID        (1u)

#define MAX_8BIT        (0xFFu)

/* Function prototypes */
void overlay_mouse_pointer(uint8_t* frame_buffer, uint8_t* mouse_pointer_buffer,
                           uint8_t  x_coordinate, uint8_t  y_coordinate);
#endif