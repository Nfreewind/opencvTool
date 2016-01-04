#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to read picture\n"
        "Usage:\n"
        "./readPicture [image_name]\n";
}

int main(int argc, char** argv)
{
    Mat image;
    string filename;

    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = imread(filename, IMREAD_COLOR);

    namedWindow("view", WINDOW_AUTOSIZE);
    moveWindow("view", 100, 100);
    imshow("view", image);

    waitKey(0);

    return 0;
}
