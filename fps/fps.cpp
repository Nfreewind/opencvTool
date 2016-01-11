#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap;
    Mat image;
    time_t start, end;
    double fps;
    int counter = 0;
    double sec;

    cap.open(0);
    namedWindow("view", WINDOW_AUTOSIZE);
    time(&start);

    while (1) {
        cap >> image;
        imshow("view", image);
        time(&end);
        counter++;
        sec = difftime(end, start);
        fps = counter / sec;
        cout << "Count: " << counter << ", FPS: " << fps << endl;

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
    }

    return 0;
}
