#include <iostream>
#include <limits>
#include <numeric>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Point2f> left_image;      // Stores 4 points(x,y) of the logo image. Here the four points are 4 corners of image.
vector<Point2f> right_image;    // stores 4 points that the user clicks(mouse left click) in the main image.

Mat imageMain;
Mat imageLogo;

void help()
{
    cout << "\nThis program is used to make a perspective transformation on an image using homography and overlay it onto the other image.\n"
        "Usage:\n"
        "./findHomography [main_image_name] [image_name]\n\n";
}

// Function to add main image and transformed logo image and show final output.
// Icon image replaces the pixels of main image in this implementation.
void showFinal(Mat src1,Mat src2)
{
    Mat gray, gray_inv, src1final, src2final;
    cvtColor(src2, gray, CV_BGR2GRAY);
    threshold(gray, gray, 0, 255, CV_THRESH_BINARY);
    //adaptiveThreshold(gray, gray, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);
    bitwise_not(gray, gray_inv);
    src1.copyTo(src1final, gray_inv);
    src2.copyTo(src2final, gray);
    Mat finalImage = src1final + src2final;
    namedWindow("output", WINDOW_AUTOSIZE);
    imshow("output", finalImage);
    //imwrite("sample_out.jpg", finalImage);
    waitKey(0);
}

// Here we get four points from the user with left mouse clicks.
// On 5th click we output the overlayed image.
static void onMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN) {
        if(right_image.size() < 4) {
            right_image.push_back(Point2f(x, y));
            int pointId = right_image.size();
            printf("%d (%d, %d)\n", pointId, x, y);
            if (right_image.size() == 4) {
                printf("Calculating Homography ...\n");

                setMouseCallback("Display window", NULL, NULL);
                // once we get 4 corresponding points in both images calculate homography matrix
                Mat H = findHomography(left_image, right_image, 0);
                //Mat H = getPerspectiveTransform(left_image, right_image);
                Mat logoWarped;
                // Warp the logo image to change its perspective
                warpPerspective(imageLogo, logoWarped, H, imageMain.size());
                showFinal(imageMain, logoWarped);
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        help();
        return 1;
    }

    // Load images from arguments passed.
    imageMain = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    imageLogo = imread(argv[2], CV_LOAD_IMAGE_COLOR);
    // Push the 4 corners of the logo image as the 4 points for correspondence to calculate homography.
    left_image.push_back(Point2f(0, 0));
    left_image.push_back(Point2f(0, imageLogo.rows));
    left_image.push_back(Point2f(imageLogo.cols, imageLogo.rows));
    left_image.push_back(Point2f(imageLogo.cols, 0));

    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", imageMain);

    setMouseCallback("Display window", onMouse, NULL);

    printf("We need 4 corresponding 2D points(x,y) to calculate homography.\n");
    printf("Use left mouse button to choose 4 points on the image.\n");

    while (1) {
        int key;
        key = waitKey(1);
        if (key == 27)
            break;
    }

    return 0;
}
