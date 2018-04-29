#!/usr/bin/python

import cv2
import numpy as np

img = cv2.imread("./car_in_road.jpg")

print  img.shape

# capture a roi of 20x20 in size
roi = img[200:300, 220: 320]

# set previous pixels to this new ROI
img[180:280, 200:300] = roi

# write image to a new file
cv2.imwrite("./car_in_road_with_roi.jpg", img)

# display image
newimg = cv2.imread("./car_in_road_with_roi.jpg")

cv2.imshow("./car_in_road_with_roi.jpg", newimg)
cv2.waitKey(0)
cv2.destroyAllWindows()
