#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat image;
    string filename("lena.jpg");

    if (argc > 1) {
        filename = argv[1];
    }
    image = imread(filename, IMREAD_COLOR);

    namedWindow("view", WINDOW_AUTOSIZE);
    moveWindow("view", 100, 100);
    imshow("view", image);

    waitKey(0);

    return 0;
}
