# Cursor Problem

To produce code for a system that has a frame buffer. The frame
buffer stores a 2D image which is automatically displayed on an LCD screen.

The LCD and framebuffer have a resolution of 640x480. All buffers’ pixels are
stored sequentially in rows, with each subsequent row immediately following
the previous in the buffer. The first pixel in the frame buffer is displayed
in the top-left most corner of the LCD.

The frame buffer uses 16-bits to encode each pixel, split into individual
blue, green & red components of sizes 5, 6 & 5 bits respectively
(red occupies the least significant bits).

A software renderer is required to blend a 32x32 pixel mouse pointer over the
frame buffer. The buffer containing the pointer uses 32-bits to encode each
pixel, split into individual 8-bit blue, green, red & alpha components,
respectively (alpha occupies the least significant byte).

A mouse pixel's transparency is defined by its alpha value, which may be
anywhere between 0 and 255 inclusive, where 0 is completely transparent
and 255 is completely opaque.

The mathematical equation for alpha blending, for each component C, is:

outputC = (foregroundC x alpha) +
(backgroundC x (1.0 – alpha))

Where all values are in the range 0.0-1.0.

Note the co-ordinates will always be within 640x480, but the mouse pointer
may overhang the end of the framebuffer.

Implement the 'overlay_mouse_pointer' function below. Any tests can be run
by adding them to the 'main' function.


Blends the image contained in the mouse pointer buffer over the provided frame
buffer, at the specified coordinates. The result of the blend should be written
back to the frame buffer.

Inputs:
frame_buffer: The provided frame buffer, over which the mouse pointer
image should be blended
mouse_pointer_buffer: Buffer containing mouse pointer image (with per
pixel alpha information)
x_coordinate: X coordinate of top left pixel of mouse pointer on frame
buffer. Only values within the range 0 -> 639 are permitted.
y_coordinate: Y coordinate of top left pixel of mouse pointer on frame
buffer. Only values within the range 0 -> 479 are permitted.

Output:
frame_buffer: The result of the blend is written back to frame_buffer

### Function to Implement:

Syntax of function to implement:
```c
/*
	\param 	[in]  frame_buffer				The provided frame buffer, over which the mouse pointer
											image should be blended
	\param 	[in]  mouse_pointer_buffer		Buffer containing mouse pointer image (with per
											pixel alpha information)
	\param 	[in]  x_coordinate				X coordinate of top left pixel of mouse pointer on frame
											buffer. Only values within the range 0 -> 639 are permitted.
	\param 	[in]  y_coordinate				Y coordinate of top left pixel of mouse pointer on frame
											buffer. Only values within the range 0 -> 479 are permitted.
 */
void overlay_mouse_pointer(uint8_t* frame_buffer, uint8_t* mouse_pointer_buffer,
                           uint8_t  x_coordinate, uint8_t  y_coordinate)
```

### Link for explaination :
Below excel sheet contains image that explains about how image is saved and what problem means.
This graphical explaination helps the solver to understad that problem.

[Problem](https://github.com/Akshay1595/GPU_Codes/blob/main/Cursor_problem/explaination.xlsx)

# Output Log File:
This is the log we obtained after executing the output.exe

[Output.log](https://github.com/Akshay1595/GPU_Codes/blob/main/Cursor_problem/terminal.log)
