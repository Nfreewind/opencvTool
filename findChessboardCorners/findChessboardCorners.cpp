#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void saveImage(Mat image)
{
    static int count = 1;
    string filename;
    stringstream ss;

    ss << setfill('0') << setw(4) << count;
    filename = "image" + ss.str() + ".jpg";
    imwrite(filename, image);
    cout << "write to " << filename << " ..." << endl;
    count++;
}

int main(void)
{
    VideoCapture cap;
    Mat image, show_image;
    vector<Point2f> points;
    Size boardSize;

    boardSize.width = 9;
    boardSize.height = 6;
    cout << "board width: " << boardSize.width << ", board height: " << boardSize.height << endl;
    cap.open(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    namedWindow("view", WINDOW_AUTOSIZE);

    while (1) {
        cap >> image;

        bool found;
        found = findChessboardCorners(image, boardSize, points,
                CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FAST_CHECK);

        cout << "found: " << found << ", points: " << points.size() << endl;
        image.copyTo(show_image);
        if (found)
            drawChessboardCorners(show_image, boardSize, Mat(points), found);

        imshow("view", show_image);

        int key;
        key = waitKey(10);
        if (key == 'q' || key == 27)
            break;
        if (key == 's' &&  found)
            saveImage(image);
    }

    return 0;
}
