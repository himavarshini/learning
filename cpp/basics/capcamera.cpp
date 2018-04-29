#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // capture device is camera -> 0
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Cannot open the camera" <<endl;
        return -1;
    }

    // create a capture frame of width and height
    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Frame size: "<< dWidth << "x" << dHeight <<endl;

    // create a window
    namedWindow("Video", CV_WINDOW_AUTOSIZE);

    while (1) {
        Mat frame;
        bool bSuccess = cap.read(frame); // read the frame
        
        if (!bSuccess) {
            cout <<"Cannot read a frame from camera" <<endl;
            break;
        }

        imshow("Video", frame);
        if (waitKey(30) == 27) {
            cout << "esc key pressed .." <<endl;
            break;
        }
    }

    return 0;
}
