#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
    Mat image;
    int count = 1;
    char filename[256];
    Size boardSize(9, 6);
    Size imageSize(640, 480);
    vector<Point2f> imageCorners;
    vector<Point3f> objectCorners;
    vector<vector<Point3f> > objectPoints;
    vector<vector<Point2f> > imagePoints;
    Mat cameraMatrix;
    Mat distCoeffs;

    distCoeffs = Mat::zeros(8, 1, CV_64F);
    // The corners are at 3D location (X,Y,Z)= (i,j,0)
    for (int i=0; i<boardSize.height; i++) {
        for (int j=0; j<boardSize.width; j++) {
            objectCorners.push_back(Point3f(i, j, 0.0f));
        }
    }

    while (1) {
        sprintf(filename, "image/image%04d.jpg", count++);
        image = imread(filename, 0);

        if (image.empty())
            break;
        printf("Read image: %s\n", filename);

        bool found = findChessboardCorners(image, boardSize, imageCorners);

        cornerSubPix(image, imageCorners, Size(5,5), Size(-1,-1),
                TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS,
                    30,      // max number of iterations
                    0.1));   // min accuracy

        if ((int)imageCorners.size() == (int)boardSize.area()) {
            imagePoints.push_back(imageCorners);
            objectPoints.push_back(objectCorners);
        }

        if (!found)
            printf("Unable to find corners: %s\n", filename);
    }

    printf("Calibrate Camera ...\n");
    vector<Mat> rvecs, tvecs;
    calibrateCamera(objectPoints, // the 3D points
            imagePoints, // the image points
            imageSize,   // image size
            cameraMatrix,// output camera matrix
            distCoeffs,  // output distortion matrix
            rvecs, tvecs,// Rs, Ts
            0);       // set options

    printf("Save to camera.yml ...\n");
    FileStorage fs("camera.yml", FileStorage::WRITE);
    time_t t;
    time(&t);
    struct tm *tm = localtime(&t);
    char buf[1024];
    sprintf(buf, "%d-%d-%d %d:%d:%d",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);
    fs << "calibration_time" << buf;
    fs << "image_width" << imageSize.width;
    fs << "image_height" << imageSize.height;
    fs << "board_width" << boardSize.width;
    fs << "board_height" << boardSize.height;
    fs << "camera_matrix" << cameraMatrix;
    fs << "distortion_coefficients" << distCoeffs;

    printf("Done.\n");
}
