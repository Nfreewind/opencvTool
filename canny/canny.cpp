#include <stdio.h>
#include <cv.h>
#include <highgui.h>

IplImage* image = NULL;
IplImage* cannyImage = NULL;
int threshold1 = 50;
int threshold2 = 150;

void help()
{
    printf("\nThis program is used to do canny algorithm\n"
            "Usage:\n"
            "./canny image_name\n\n");
}

void onTrackbar1(int /*position*/)
{
    cvCanny(image, cannyImage, threshold1, threshold2, 3);
    cvShowImage("canny", cannyImage);
}

void onTrackbar2(int /*position*/)
{
    cvCanny(image, cannyImage, threshold1, threshold2, 3);
    cvShowImage("canny", cannyImage);
}

int main(int argc, char** argv)
{
    char *filename;
    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

    if (image == NULL)
        return 1;

    cannyImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

    cvCanny(image, cannyImage, threshold1, threshold2, 3);

    cvNamedWindow("origin image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("canny image", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("origin image", 0, 0);
    cvMoveWindow("canny image", 500, 0);
    cvShowImage("origin image", image);
    cvShowImage("canny image", cannyImage);

    cvCreateTrackbar("Threshold1", "canny image", &threshold1, 255, onTrackbar1);
    cvCreateTrackbar("Threshold2", "canny image", &threshold2, 255, onTrackbar2);

    while (1) {
        int key;
        key = cvWaitKey(1);
        if (key == 'q' || key == 27)
            break;
        if (key == 's')
            cvSaveImage("CannyImage.jpg", cannyImage);
    }

    cvDestroyWindow("origin image");
    cvDestroyWindow("canny image");
    cvReleaseImage(&image);
    cvReleaseImage(&cannyImage);

    return 0;
}
