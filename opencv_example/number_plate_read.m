% numberPlate = imread('rod-fountain-7813-low-res.jpg');
numberPlate = imread('Hong_Kong_number_plates_2009.png');
ocrData = ocr(numberPlate);
recognisedText = ocrData.Text;
figure
text(600, 600, recognisedText, 'BackgroundColor', [1 1 1]);