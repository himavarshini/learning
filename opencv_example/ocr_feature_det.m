% I = imread('circuit.tif');
I = imread('Hong_Kong_number_plates_2009.png');
I_G = rgb2gray(I);
%corners = detectFASTFeatures(I_G, 'MinContrast', 0.1);
corners = detectHarrisFeatures(I_G);
J = insertMarker(I_G, corners, 'circle');
imshow(J);