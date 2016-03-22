#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to show undistorted image\n"
        "Usage:\n"
        "./showUndistorted camera.yml\n"
        "  Show undistorted/distorted image:   press u\n"
        "  Exit the program:                   press q or ESC\n\n";
}

int main(int argc, const char *argv[])
{
    Mat image;
    VideoCapture cap;
    int width = 640;
    int height = 480;
    Mat cameraMatrix, distCoeffs;
    FileStorage fs;
    int undistortImage = 1;

    if (argc != 2) {
        help();
        return 1;
    }

    fs.open(argv[1], FileStorage::READ);
    fs["camera_matrix"] >> cameraMatrix;
    fs["distortion_coefficients"] >> distCoeffs;

    cap.open(0);
    cap.set(CAP_PROP_FRAME_WIDTH, width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);

    namedWindow("view", WINDOW_AUTOSIZE);
    cout << "undistortImage: " << undistortImage << endl
        << "cameraMatrix: " << cameraMatrix << endl
        << "distCoeffs: " << distCoeffs << endl;

    while (1) {
        cap.read(image);
        if (undistortImage) {
            Mat temp = image.clone();
            undistort(temp, image, cameraMatrix, distCoeffs);
        }
        imshow("view", image);

        int key;
        key = waitKey(1);
        if (key == 'q' || key == 27)
            break;
        if (key == 'u') {
            undistortImage ^= 1;
            cout << "undistortImage: " << undistortImage << endl;
        }
    }

    return 0;
}
