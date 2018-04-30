% optical char recognition using matlab from the matlab central http://in.mathworks.com/help/vision/ref/ocr.html

businessCard = imread('businessCard.png');

% predict the text based on the image
ocrResult = ocr(businessCard);

recognisedText = ocrResult.Text;
figure;
imshow(businessCard);
text(600, 150, recognisedText, 'BackgroundColor', [1 1 1]);