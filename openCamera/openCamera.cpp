#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to open camera\n"
        "Usage:\n"
        "  Exit the program:  press q or ESC\n";
}

int main(int argc, char** argv)
{
    Mat image;
    VideoCapture cap;
    int width = 640;
    int height = 480;
    int fps;

    help();

    cap.open(0);

    cap.set(CAP_PROP_FRAME_WIDTH, width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    cout << "Width: " << width << " Height: " << height << endl;
    fps = cap.get(CAP_PROP_FPS);
    cout << "fps: " << fps << endl;
    
    namedWindow("view", WINDOW_AUTOSIZE);
    while (1) {
        cap.read(image);
        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
    }

    return 0;
}
