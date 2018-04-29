#!/usr/bin/python

import numpy as np

# load cv2 lib
import cv2

# load an image
img = cv2.imread("./beach-exotic-holiday-248797.jpg", 0)

# display an image ..
cv2.imshow('image', img)

# hold it otherwise the image quickly moves out .. so hold it till we press 0
cv2.waitKey(0)

# cleanup
cv2.destroyAllWindows()
