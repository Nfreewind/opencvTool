#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to convert color image to gray image\n"
        "Usage:\n"
        "./readPicture [image_name]\n";
}

int main(int argc, char** argv)
{
    Mat image, image_gray;
    string filename;

    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = imread(filename, IMREAD_COLOR);
    cvtColor(image, image_gray, COLOR_BGR2GRAY);

    namedWindow("view", WINDOW_AUTOSIZE);
    moveWindow("view", 100, 100);
    imshow("view", image_gray);

    imwrite("saved.jpg", image_gray);
    waitKey(0);

    return 0;
}
