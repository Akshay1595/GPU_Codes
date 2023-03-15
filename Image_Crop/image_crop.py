'''
@file   : image_crop.py
@Author : Akshay Godase
@Brief  : Python script to crop the image from x and y co-ordinates passed by the user.
@Date   : 15/03/2023
'''

# Necessary Imports
import cv2
import os
import sys
import numpy as np
from PIL import Image

def GetCroppedImage(array, x_coordinate, y_coordinate):

    # Current image shape
    shapeTuple = array.shape
    height_old = shapeTuple[0]
    width_old = shapeTuple[1]

    # New Image shape
    if (x_coordinate < width_old) and (y_coordinate < height_old):
        width = width_old - x_coordinate
        height = height_old - y_coordinate 
    else :
        print('Width of Image = ' + str(width_old) + ' Height of Image = ' + str(height_old))
        print('x = ' + str(x_coordinate) + ' y = ' + str(y_coordinate))
        print('Error: Co-ordinates are out of range ')
        return None

    # Create new image
    newImageArray = np.zeros((width*height*3), dtype=np.uint8)
    newImageArray = newImageArray.reshape(height, width, 3)

    copy_row = y_coordinate
    # Update pixel by Pixel
    for row in range(height):
        copy_col = x_coordinate
        for col in range(width):
            newImageArray[row][col] = array[copy_row][copy_col]
            copy_col += 1
        copy_row += 1

    # Return the result Image
    return newImageArray

def GetImageInArray(filename):

    # Using cv2 library converts image into numpy Array
    path = os.getcwd()
    image = path + filename
    im = cv2.imread(image)
    img = cv2.cvtColor(im, cv2.COLOR_BGR2RGB)
    return img

def SaveImage(filename, ImageArray):

    # Use of PIL library to save image in RGB format 
    img = Image.fromarray(ImageArray, "RGB")
    img.show()
    image_filename = "Cropped_" + filename
    img.save(image_filename)

    print('Cropped image stored in same directory with filename: ' + image_filename)
    return

if __name__ == "__main__":

    if len(sys.argv) == 4:
        filename = sys.argv[1]
        x = int(sys.argv[2])
        y = int(sys.argv[3])
        print('Cropping Image = ' + filename + ' from x = ' + str(x) + ' and y = ' + str(y))
    else :
        print('usage: ./image_crop.py <image_filename.png> <x> <y>. \n Note: x and y need to be less than width and height of image')
        exit()

    # filename used to read the image file in the current folder
    true_filename = "\\" + filename
    # Reads the image into numpy array format
    array = GetImageInArray(true_filename)

    # Get New Image Numpy Array and store updated pixels 
    newImageArray = GetCroppedImage(array, x, y)

    # Finally save the image
    SaveImage(filename, newImageArray)