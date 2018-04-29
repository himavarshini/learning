I = imread('pout.tif') % read an image
imhist(I) % display histogram of it
imshow(I) % show image as well
whos I
I2 = histeq(I) % histogram equaliser Spreads intensity equally between the full range of image
imshow(I2)
imhist(I2)
imwrite(I2, 'pout2.png')
imfinfo('pout2.png')