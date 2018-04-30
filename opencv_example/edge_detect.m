% I = imread('Hong_Kong_number_plates_2009.png')
I = imread('rod-fountain-7813-low-res.jpg');
I_2d = rgb2gray(I);
Edge_Canny = edge(I_2d, 'canny');
Edge_Sobel = edge(I_2d, 'sobel');
% figure('Name', 'Canny Detector');
% imshow(Edge_Canny);
% figure('Name', 'Sobel Detector');
% imshow(Edge_Sobel);
Edge_roberts = edge(I_2d, 'roberts');
% figure('Name', 'Roberts detector');
% imshow(Edge_roberts);
Edge_prewitt = edge(I_2d, 'prewitt');
% figure('Name', 'Prewitt detector');
% imshow(Edge_prewitt);



ocrData = ocr(Edge_Sobel);
recognisedText= ocrData.Text;
figure;
imshowpair(I, Edge_Canny, 'montage');

text(564, 100, recognisedText, 'BackgroundColor', [1 1 1]);
