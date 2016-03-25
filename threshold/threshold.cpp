#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat image;
Mat binaryImage;
int threshold_value = 128;

void help()
{
    cout << "\nThis program is used to threshold a picture.\n"
        "Usage:\n"
        "./threshold image_name\n\n";
}

void onTrackbar1(int /*position*/)
{
    threshold(image, binaryImage, threshold_value, 255, cv::THRESH_BINARY);
    imshow("thresholded image", binaryImage);
}

int main(int argc, char** argv)
{
    string filename;

    if (argc != 2) {
        help();
        return 1;
    }

    filename = argv[1];
    image = imread(filename, IMREAD_GRAYSCALE);

    if (image.empty()) {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    threshold(image, binaryImage, threshold_value, 255, cv::THRESH_BINARY);

    namedWindow("origin image", WINDOW_AUTOSIZE);
    imshow("origin image", image);

    namedWindow("thresholded image", WINDOW_AUTOSIZE);
    imshow("thresholded image", binaryImage);
    cvCreateTrackbar("Threshold", "thresholded image", &threshold_value, 255, onTrackbar1);

    while (1) {
        int key;
        key = waitKey(1);
        if (key == 'q' || key == 27)
            break;
    }

    image.release();
    binaryImage.release();

    return 0;
}
