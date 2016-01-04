#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap;
    Size boardSize;
    boardSize.width = 9;
    boardSize.height = 6;

    cout << "board width: " << boardSize.width << "\nboard height: " << boardSize.height << endl;
    cap.open(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    namedWindow("view", WINDOW_AUTOSIZE);

    while (1) {
        Mat image, gray;
        vector<Point2f> points;

        cap >> image;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        bool found;
        found = findChessboardCorners(image, boardSize, points,
                CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

        if (found)
            drawChessboardCorners(image, boardSize, Mat(points), found);

        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
    }

    return 0;
}
