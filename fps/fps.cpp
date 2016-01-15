#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    int width = 640;
    int height = 480;
    Mat image;
    time_t start, end;
    double fps;
    int counter = 0;
    double sec;

    cap.open(0);
    cap.set(CAP_PROP_FRAME_WIDTH, width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    fps = cap.get(CAP_PROP_FPS);
    cout << "Width: " << width << ", Height: " << height << ", FPS: " << fps << endl;

    namedWindow("view", WINDOW_AUTOSIZE);
    time(&start);

    while (1) {
        cap.read(image);
        imshow("view", image);
        time(&end);
        counter++;
        sec = difftime(end, start);
        fps = counter / sec;
        cout << "Count: " << counter << ", FPS: " << fps << endl;

        int key;
        key = waitKey(1);
        if (key == 'q' || key == 27)
            break;
    }

    return 0;
}
