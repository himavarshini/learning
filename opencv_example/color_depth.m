rgb = imread('peppers.png');
imshow(rgb);
title('original');

[im, map] = rgb2ind(rgb, 8000, 'nodither'); % nodither will not smoother to pxies
imshow(im, map)

figure
[im1, map1] = rgb2ind(rgb, 8000, 'dither'); % dither will smooth
imshow(im1, map1)