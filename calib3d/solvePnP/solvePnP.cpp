#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Scalar red(0, 0, 255);
Scalar green(0,255,0);
Scalar blue(255,0,0);
Scalar yellow(0,255,255);

Mat image;
int nKeypoints = 4;
vector<Point2f> imageKeypoints;

void help()
{
    cout << "\nThis program is used to do PnP algorithm from an image.\n"
        "Usage:\n"
        "./solvePnP image_name\n"
        "  then choose four points"
        "  Exit the program:                   press q or ESC\n\n";
}

static void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (imageKeypoints.size() >= nKeypoints)
        return;

    if (event == EVENT_LBUTTONUP) {
        cout<< "imageKeypoints.size = " << imageKeypoints.size()
            << ", (" << x << ", " << y << ")" << endl;
        imageKeypoints.push_back(Point2f(x, y));
        circle(image, Point2f(x,y), 4, red, -1, 8);
    }
}

int main(int argc, const char *argv[])
{
    Mat intrinsics, distortion;
    Mat gray;
    Mat rvec = Mat(Size(3,1), CV_64F);
    Mat tvec = Mat(Size(3,1), CV_64F);
    vector<Point2f> imageFramePoints;
    vector<Point3f> model, framePoints;

    intrinsics = (Mat_<double>(3,3) <<
            700, 0, 320,
            0, 700, 240,
            0, 0, 1);
    distortion = (Mat_<double>(5,1) <<
            0,
            0,
            0,
            0,
            0);

    model.push_back(Point3f(0, 0, 0));
    model.push_back(Point3f(1, 0, 0));
    model.push_back(Point3f(0, 0, 1));
    model.push_back(Point3f(1, 0, 1));

    framePoints.push_back(Point3f(0.0, 0.0, 0.0));
    framePoints.push_back(Point3f(1.0, 0.0, 0.0));
    framePoints.push_back(Point3f(0.0, 1.0, 0.0));
    framePoints.push_back(Point3f(0.0, 0.0, 1.0));

    if (argc != 2) {
        help();
        return 1;
    }
    image = imread(argv[1], IMREAD_COLOR);
    namedWindow("view", CV_WINDOW_AUTOSIZE);
    setMouseCallback("view", onMouse, 0);

    cvtColor(image, gray, COLOR_BGR2GRAY);
    bool found = false;
    while(1) {
        if (imageKeypoints.size() >= nKeypoints) {
            found = true;
        }

        if (found) {
            solvePnP(Mat(model), Mat(imageKeypoints), intrinsics, distortion, rvec, tvec, false);

            projectPoints(framePoints, rvec, tvec, intrinsics, distortion, imageFramePoints);

            circle(image, (Point)imageFramePoints[0], 4 ,CV_RGB(255,0,0));

            Point one, two, three;
            one.x=10; one.y=10;
            two.x = 60; two.y = 10;
            three.x = 10; three.y = 60;

            line(image, one, two, CV_RGB(255,0,0));
            line(image, one, three, CV_RGB(0,255,0));

            line(image, imageFramePoints[0], imageFramePoints[1], CV_RGB(255,0,0), 2); // x red
            line(image, imageFramePoints[0], imageFramePoints[2], CV_RGB(0,255,0), 2); // y green
            line(image, imageFramePoints[0], imageFramePoints[3], CV_RGB(0,0,255), 2); // z blue

            cout << fixed << setprecision(2) << "rvec = ["
                << rvec.at<double>(0,0) << ", "
                << rvec.at<double>(1,0) << ", "
                << rvec.at<double>(2,0) << "] \t" << "tvec = ["
                << tvec.at<double>(0,0) << ", "
                << tvec.at<double>(1,0) << ", "
                << tvec.at<double>(2,0) << "]" << endl;
        }

        imshow("view", image);

        int key;
        key = waitKey(1);
        if (key == 'q' || key == 27)
            break;
    }
    return 0;
}
