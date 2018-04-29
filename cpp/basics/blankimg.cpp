#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img(500, 1000, CV_8UC3, Scalar(255, 0, 255));

    if (img.empty()) {
        cout << "Error: image cant be loaded" << endl;
        return -1;
    }

    namedWindow("Window", CV_WINDOW_AUTOSIZE);
    imshow("Window", img);

    waitKey(0);

    destroyWindow("Window");

    return 0;
}

