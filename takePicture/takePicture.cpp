#include <iostream>
#include <string>
#include <sstream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to take picture\n"
        "Usage:\n"
        "  Save image:        press s\n"
        "  Exit the program:  press q or ESC\n";
}

void saveImage(Mat image)
{
    static int count = 1;
    string filename;
    stringstream ss;

    ss << count;
    filename = "image" + ss.str() + ".jpg";
    imwrite(filename, image);
    cout << "write to " << filename << " ..." << endl;
    count++;
}

int main()
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
    fps = cap.get(CAP_PROP_FPS);
    cout << "Width: " << width << ", Height: " << height << ", FPS: " << fps << endl;

    namedWindow("view", WINDOW_AUTOSIZE);

    while (1) {
        cap.read(image);
        imshow("view", image);

        int key;
        key = waitKey(1);
        if (key == 'q' || key == 27)
            break;
        if (key == 's') {
            saveImage(image);
        }
    }

    return 0;
}
