
import numpy as np
import cv2

img = cv2.imread("./beach-exotic-holiday-248797.jpg")

# get pixel @ 100, 100 (i think this is grayscale)

#px = img[100, 100]

# print the value of pixel at 100, 100
#print px

px = img[100, 100, 2]
print px

# get image size

imagesize = img.shape
print "image size is " + str(imagesize)

# access set element
print imagesize[0], imagesize[1], imagesize[2]

# same pixel count for a BGR image
print imagesize[0] * imagesize[1] * imagesize[2]

pixelcount = img.size
print "pixel count " + str(pixelcount)

# get image data type
dtype= img.dtype
print "data type " + str(dtype)

# split the b,g,r channels
b,g,r = cv2.split(img)

# merge b,g,r channels
img = cv2.merge((b,g,r))
