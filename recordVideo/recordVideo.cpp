#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to record video\n"
        "Usage:\n"
        "  Record video:      press r\n"
        "  Exit the program:  press q or ESC\n";
}

int main(int argc, char** argv)
{
    Mat image;
    string filename;
    VideoCapture cap;
    VideoWriter outputVideo;
    int start_record = 0;
    int fourcc;
    int fps;
    Size size;

    help();
    cap.open(0);

    filename = "output.avi";
    fourcc = CV_FOURCC('D', 'I', 'V', 'X');
    fps = cap.get(CAP_PROP_FPS);
    size = Size((int) cap.get(CAP_PROP_FRAME_WIDTH), (int) cap.get(CAP_PROP_FRAME_HEIGHT));
    cout << "Width: " << size.width << " Height: " << size.height << endl;
    cout << "fps: " << fps << endl;
    if (fps == 0)
        fps = 30;
    outputVideo.open(filename, fourcc, fps, size, true);
    namedWindow("view", WINDOW_AUTOSIZE);
    while (1) {
        cap.read(image);
        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
        if (key == 'r') {
            start_record ^= 1;
        }

        if (start_record) {
            outputVideo.write(image);
            cout << "write to " << filename << " ..." << endl;
        }
    }

    return 0;
}
