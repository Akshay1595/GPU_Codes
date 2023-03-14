'''
@file   : image_rotate.py
@Author : Akshay Godase
@Brief  : Script to implement Rotating of image by 90 degree direction in 
          Direction input given by the user
@Date   : 14/03/2023
'''

# Necessary Imports
import cv2
import os
import sys
import numpy as np
from PIL import Image

def RotateClockWiseNinetyDegree(array):

    # Current image shape
    shapeTuple = array.shape
    height_old = shapeTuple[0]
    width_old = shapeTuple[1]

    # New Image shape
    width = height_old
    height = width_old

    # Create new image
    newImageArray = np.zeros((width*height*3), dtype=np.uint8)
    newImageArray = newImageArray.reshape(height, width, 3)

    # Update pixel by Pixel
    for row in range(height):
        copy_col = row
        copy_row = (width - 1)
        for col in range(width):
            newImageArray[row][col] = array[copy_row][copy_col]
            #msg = 'For row = ' + str(row) + ' col = ' + str(col) + ' : Copying row = ' + str(copy_row) + ' col = ' + str(copy_col)
            #print(msg)
            copy_row -= 1

    # Return the result Image
    return newImageArray


def RotateAntiClockWiseNinetyDegree(array):

    # Current image shape
    shapeTuple = array.shape
    height_old = shapeTuple[0]
    width_old = shapeTuple[1]

    # New Image shape exchange dimensions
    width = height_old
    height = width_old

    # Create new image
    newImageArray = np.zeros((width*height*3), dtype=np.uint8)
    newImageArray = newImageArray.reshape(height, width, 3)

    # Update pixel by Pixel
    for row in range(height):
        copy_col = height - row - 1
        for col in range(width):
            copy_row = col
            newImageArray[row][col] = array[copy_row][copy_col]
            #msg = 'For row = ' + str(row) + ' col = ' + str(col) + ' : Copying row = ' + str(copy_row) + ' col = ' + str(copy_col)
            #print(msg)

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
    image_filename = "rotated_" + filename
    img.save(image_filename)

    print('Rotated image stored in same directory with filename: ' + image_filename)
    return

if __name__ == "__main__":

    if len(sys.argv) == 3:
        filename = sys.argv[1]
        direction = sys.argv[2]
        if direction == 'a':
            direction = 'Anticlockwise'
        else:
            direction = 'Clockwise'
        print('Rotating filename = ' + filename + ' Direction = ' + direction)
    else :
        print('usage: ./image_rotate.py <image_filename.png> <direction : a / c  a = anticlockwise and c = clockwise>')
        exit()

    # filename used to read the image file in the current folder
    true_filename = "\\" + filename
    # Reads the image into numpy array format
    array = GetImageInArray(true_filename)

    if direction == 'Anticlockwise' :
        # Get New Image Numpy Array and store updated pixels 
        newImageArray = RotateAntiClockWiseNinetyDegree(array)
    else :
        # Get New Image Numpy Array and store updated pixels 
        newImageArray = RotateClockWiseNinetyDegree(array)

    # Finally save the image
    SaveImage(filename, newImageArray)