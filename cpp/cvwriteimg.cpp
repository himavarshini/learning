#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img (650, 600, CV_16UC3, Scalar(0, 50000, 50000));

    if (img.empty()) {
        cout << "error: image cannot be loaded" <<endl;
        return -1;
    }

    vector<int> compression_params;

    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(98);

    bool bSuccess = imwrite(argv[1], img, compression_params);

    if (!bSuccess) {
        cout <<"error: failed to save image" <<endl;
        return -1;
    }

    namedWindow("Window", CV_WINDOW_AUTOSIZE);
    imshow("Window", img);

    waitKey(0);
    destroyWindow("Window");

    return 0;
}
