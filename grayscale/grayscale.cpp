#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to convert color image to gray image\n"
        "Usage:\n"
        "./grayscale [image_name]\n\n";
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

    namedWindow("view", WINDOW_AUTOSIZE);
    imshow("view", image);
    waitKey(0);

    cvtColor(image, image_gray, COLOR_BGR2GRAY);

    imshow("view", image_gray);
    imwrite("saved.jpg", image_gray);
    waitKey(0);

    return 0;
}
