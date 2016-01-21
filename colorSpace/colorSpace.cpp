#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to convert color image to other color space\n"
        "Usage:\n"
        "./colorSpace [image_name]\n\n";
}

int main(int argc, char** argv)
{
	Mat image, hsv, ycbcr;
    string filename;

    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = imread(filename, IMREAD_COLOR);

    cvtColor(image, hsv, COLOR_BGR2HSV);
    cvtColor(image, ycbcr, COLOR_BGR2YCrCb);

    imshow("Image", image);
    imshow("HSV", hsv);
    imshow("YCbCr", ycbcr);
    waitKey(0);

    return 0;
}
