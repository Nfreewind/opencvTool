#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat image;
    string filename;
    VideoCapture cap;

    cap.open(0);

    while(1) {
        cap.read(image);

        namedWindow("view", WINDOW_AUTOSIZE);
        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
        if (key == 's') {
            filename = "saved.jpg";
            imwrite(filename, image);
            cout << "write to " << filename << " ..." << endl;
        }
    }

    return 0;
}
