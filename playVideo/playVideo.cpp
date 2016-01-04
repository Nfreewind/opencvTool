#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat image;
    string filename;
    VideoCapture cap;

    if (argc < 2)
        return 1;
    
    filename = argv[1];
    cap.open(filename);
    namedWindow("view", WINDOW_AUTOSIZE);
    
    while(1) {
        cap.read(image);

        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
        if (key == 's') {
            filename = "saved.jpg";
            imwrite(filename, image);
            cout << "write to " << filename << " ..." << endl;
        }
    }

    return 0;
}
