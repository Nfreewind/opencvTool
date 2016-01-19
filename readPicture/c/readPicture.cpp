#include <stdio.h>
#include <cv.h>
#include <highgui.h>

void help()
{
    printf("\nThis program is used to read picture\n"
            "Usage:\n"
            "./readPicture [image_name]\n\n");
}

void printImageInfo(IplImage *image)
{
    printf("dataOrder: %d\n", image->dataOrder); // dataOrder=0, BGRBGR...
    printf("width: %d\n", image->width);
    printf("height: %d\n", image->height);
    printf("widthStep: %d\n", image->widthStep);
    printf("nChannels: %d\n", image->nChannels);
}

int main(int argc, char **argv)
{
    IplImage *image;
    char *filename;

    if (argc != 2) {
        help();
        return 1;
    }
    filename = argv[1];
    image = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);

    printImageInfo(image);

    cvNamedWindow("view", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("view", 100, 100);
    cvShowImage("view", image);

    cvWaitKey(0);

    cvDestroyWindow("view");
    cvReleaseImage(&image);

    return 0;
}
