'''
@file   : image_resize.py
@Author : Akshay Godase
@Brief  : Script to implement Resizng of image by %
@Date   : 13/03/2023
'''


# Necessary Imports
import cv2
import os
import sys
import numpy as np
from PIL import Image

def color_average_by_ratio(List):

    # Create a new pixel to return updated pixel value
    newPixel = np.zeros(3, dtype=np.uint8)
    sumOfGreenValues = 0
    sumOfRedValues = 0
    sumOfBlueValues = 0
    nCount = 0
    for element in List:
        sumOfRedValues      += int(element[0])
        sumOfGreenValues    += int(element[1])
        sumOfBlueValues     += int(element[2])
        nCount              += 1
    
    # Average out the RGB value to get updated value
    newPixel[0] = (sumOfRedValues   / nCount)
    newPixel[1] = (sumOfGreenValues / nCount)
    newPixel[2] = (sumOfBlueValues  / nCount)

    return newPixel

def get_average_by_ratio(image, row, col, ratio):

    # List to hold the number of pixels need to averaged out
    lt = []
    for r in range(ratio):
        for c in range(ratio):
            rowIndex = (row * ratio) + r
            colIndex = (col * ratio) + c
            pixel = image[rowIndex][colIndex]
            lt.append(pixel)

    # Find the final averaged out pixel for list of pixels created 
    final_pixel = color_average_by_ratio(lt)
    return final_pixel

def GetImageInArray(filename):

    # Using cv2 library converts image into numpy Array
    path = os.getcwd()
    image = path + filename
    im = cv2.imread(image)
    img = cv2.cvtColor(im, cv2.COLOR_BGR2RGB)
    return img

def GetNewImage(array, ratio):

    # Current image shape
    shapeTuple = array.shape
    height_old = shapeTuple[0]
    width_old = shapeTuple[1]

    # New Image shape
    width = int(width_old/ratio)
    height = int(height_old/ratio)

    newImageArray = np.zeros((width*height*3), dtype=np.uint8)
    newImageArray = newImageArray.reshape(height, width, 3)

    # Update pixel by pixel of new Image
    for row in range(height):
        for col in range(width):
            newImageArray[row][col] = get_average_by_ratio(array, row, col, ratio)

    # Return the result Image
    return newImageArray

def SaveImage(filename, ImageArray):

    # Use of PIL library to save image in RGB format 
    img = Image.fromarray(ImageArray, "RGB")
    img.show()
    image_filename = "resized_" + filename
    img.save(image_filename)

    print('Resized image stored in same directory with filename: ' + image_filename)
    return

if __name__ == "__main__":

    if len(sys.argv) == 3:
        filename = sys.argv[1]
        ratio_in_pc = int(sys.argv[2])
        print('Resizing filename = ' + filename + ' by = ' + str(ratio_in_pc) + '%')
    else :
        print('usage: ./image_resize.py <image_filename.png> <value_in_percentage_without % >')
        exit()

    # ratio value used for selecting (Ratio * Ratio) pixels average out to 1 pixel
    ratio = int(100/ratio_in_pc)

    # filename used to read the image file in the current folder
    true_filename = "\\" + filename
    # Reads the image into numpy array format
    array = GetImageInArray(true_filename)

    # Get New Image Numpy Array and store updated pixels 
    newImageArray = GetNewImage(array, ratio)

    # Finally save the image
    SaveImage(filename, newImageArray)