#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(/*int argc, char** argv*/)
{
    Mat src, dst;
    string filename = "lena.jpg";

    src = imread(filename);

    // start time
    double t = (double)getTickCount();

    medianBlur(src, dst, 5);

    // end time
    t = ((double)getTickCount() - t)/getTickFrequency();
    printf("%f second\n", t);

    imshow("origin", src);
    imshow("medianBlur", dst);
    waitKey(0);

    return 0;
}
