# canny edge detector on video
import cv2
import numpy as np
from matplotlib import pyplot as plt

def show_cam(mirror=False):
    # capture the video input
    cam = cv2.VideoCapture(0)
    while True:
        ret_val, img = cam.read()
        if mirror:
            img = cv2.flip(img, 1)

        img = cv2.flip(img, 1)

        cv2.imshow('Original', img)

        edges = cv2.Canny(img, 100, 200)

        cv2.imshow('Canny', edges)
        #plt.subplot(121), plt.imshow(img, cmap='gray')
        #plt.title('original image'), plt.xticks([]), plt.yticks([])
        #plt.subplot(122), plt.imshow(edges, cmap = 'gray')
        #plt.title('Edge image'), plt.xticks([]), plt.yticks([])

        #plt.show()
        #cv2.imshow('my cam', img)
        # esc
        if cv2.waitKey(1) == 27:
            break;
    cv2.destroyAllWindows()

def main():
    show_cam()

if __name__ == '__main__':
    main()

