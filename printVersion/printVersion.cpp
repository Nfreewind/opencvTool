#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void version()
{
#if CV_MAJOR_VERSION == 2
    cout << "OpenCV 2\n";
#elif CV_MAJOR_VERSION == 3
    cout << "OpenCV 3\n";
#else
#error "Unrecognized OpenCV version!"
#endif
    cout << CV_VERSION << endl;
    cout << "Major: " << CV_MAJOR_VERSION
        << "\nMinor: " << CV_MINOR_VERSION
        << "\nSubminor: " << CV_SUBMINOR_VERSION << endl;
}

int main(int argc, const char *argv[])
{
    version();
    return 0;
}
