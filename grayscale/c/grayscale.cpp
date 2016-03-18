#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

void help()
{
    printf("\nThis program is used to convert color image to gray image\n"
            "Usage:\n"
            "./grayscale image_name\n\n");
}

void gray(IplImage *image, IplImage *image_gray)
{
    int width = image->width;
    int height = image->height;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width*3; j+=3) {
            int b = ((uchar*)image->imageData)[i*width*3 + j*3+0];
            int g = ((uchar*)image->imageData)[i*width*3 + j*3+1];
            int r = ((uchar*)image->imageData)[i*width*3 + j*3+2];

            //uchar grayscale = (r+g+b)/3;
            uchar grayscale = 0.299 * r + 0.587 * g + 0.114 * b;

            ((uchar*)image_gray->imageData)[i*width + j] = grayscale;
        }
    }
}

int main(int argc, char** argv)
{
    IplImage *image, *image_gray;
    char *filename;

    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);

    cvNamedWindow("view", CV_WINDOW_AUTOSIZE);
    cvShowImage("view", image);
    cvWaitKey(0);

    image_gray = cvCreateImage(cvGetSize(image), 8, 1);
    cvCvtColor(image, image_gray, CV_RGB2GRAY);
    //gray(image, image_gray);

    cvShowImage("view", image_gray);
    cvSaveImage("saved.jpg", image_gray);
    cvWaitKey(0);

    cvDestroyWindow("view");
    cvReleaseImage(&image);
    cvReleaseImage(&image_gray);
    return 0;
}
