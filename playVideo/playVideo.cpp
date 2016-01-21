#include <iostream>
#include <string>
#include <sstream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to play video\n"
        "Usage:\n"
        "./playVideo [video_name]\n"
        "  Save image:        press s\n"
        "  Exit the program:  press q or ESC\n\n";
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

int main(int argc, char** argv)
{
    Mat image;
    string filename;
    VideoCapture cap;

    if (argc != 2) {
        help();
        return 1;
    }

    filename = argv[1];
    cap.open(filename);
    int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));
    char EXT[] = {(char)(ex & 0XFF),
        (char)((ex & 0XFF00) >> 8),
        (char)((ex & 0XFF0000) >> 16),
        (char)((ex & 0XFF000000) >> 24),
        0};
    Size size = Size((int) cap.get(CAP_PROP_FRAME_WIDTH), (int) cap.get(CAP_PROP_FRAME_HEIGHT));
    cout << "Input resolution: Width=" << size.width << " Height=" << size.height << endl;
    cout << "Input frame count: " << cap.get(CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;
    namedWindow("view", WINDOW_AUTOSIZE);

    while (1) {
        cap.read(image);
        if (image.empty())
            break;
        imshow("view", image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
        if (key == 's') {
            saveImage(image);
        }
    }

    return 0;
}
