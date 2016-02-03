#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    vector<Point3f> objectPoints;
    vector<Point2f> imagePoints;
    Mat rvec = Mat(Size(3,1), CV_64F);
    Mat tvec = Mat(Size(3,1), CV_64F);
    Mat cameraMatrix, distCoeffs;
    cameraMatrix = (Mat_<double>(3,3) <<
            700, 0, 320,
            0, 700, 240,
            0, 0, 1);
    distCoeffs = (Mat_<double>(5,1) <<
            0,
            0,
            0,
            0,
            0);
    objectPoints.push_back(Point3f(0.0, 0.0, 0.0));
    objectPoints.push_back(Point3f(1.0, 0.0, 0.0));
    objectPoints.push_back(Point3f(0.0, 1.0, 0.0));
    objectPoints.push_back(Point3f(1.0, 1.0, 0.0));

    projectPoints(objectPoints, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

    cout << "Camera matrix=\n" << cameraMatrix << endl;
    cout << "Distortion coefficients=\n" << distCoeffs << endl;
    cout << "Rotation vector=" << rvec << endl;
    cout << "Translation vector=" << tvec << endl;
    cout << endl;

    for (int i = 0; i < (int)objectPoints.size(); i++) {
        printf("objectPoints=(%f, %f, %f) -> imagePoints=(%f, %f)\n",
                objectPoints[i].x, objectPoints[i].y, objectPoints[i].z,
                imagePoints[i].x, imagePoints[i].y);
    }
    return 0;
}
