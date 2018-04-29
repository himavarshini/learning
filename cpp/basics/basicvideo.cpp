#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture cap(argv[1]);

    if (!cap.isOpened()) {
        cout <<"Cannot open the video file" << endl;
        return -1;
    }

    double fps = cap.get(CV_CAP_PROP_FPS);

    cout << "FPS: " << fps << endl;

    namedWindow("Video", CV_WINDOW_AUTOSIZE);

    while (1) {
        Mat frame;
        bool bSuccess = cap.read(frame);

        if (!bSuccess) {
            cout << "Cannot read the frame from video file" <<endl;
            break;
        }

        imshow("Video", frame);
        waitKey(0);

        destroyWindow("Window");
    }

    return 0;
}
