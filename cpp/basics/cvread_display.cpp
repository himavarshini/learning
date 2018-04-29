#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    int image_flags;

    if (argc != 3) {
        printf("%s <image name> <flags>\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[2], "unchanged") == 0)
        image_flags = CV_LOAD_IMAGE_UNCHANGED;
    else if (strcmp(argv[2], "grayscale") == 0)
        image_flags = CV_LOAD_IMAGE_GRAYSCALE;
    else if (strcmp(argv[2], "color") == 0)
        image_flags = CV_LOAD_IMAGE_COLOR;

    Mat img = imread(argv[1], image_flags);

    if (img.empty()) {
        cout << "Error: Image can't be loaded "<< endl;
        return -1;
    }

    namedWindow("Display", CV_WINDOW_AUTOSIZE);
    imshow("Display", img);

    waitKey(0);

    destroyWindow("Display");

    return 0;
}

