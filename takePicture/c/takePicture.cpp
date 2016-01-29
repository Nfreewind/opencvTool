#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;

void help()
{
    printf("\nThis program is used to take picture\n"
        "Usage:\n"
        "  Save image:        press s\n"
        "  Exit the program:  press q or ESC\n\n");
}

void saveImage(IplImage *image)
{
    static int count = 1;
    char filename[256];

    sprintf(filename, "%s%04d.jpg", "image", count);
    cvSaveImage(filename, image);
    printf("write to %s ...\n", filename);
    count++;
}

int main()
{
	IplImage *image;
    CvCapture *cap;
    int width = 640;
    int height = 480;
    int fps;

    help();

    cap = cvCreateCameraCapture(CV_CAP_ANY); //CV_CAP_ANY, CV_CAP_VFW, CV_CAP_DSHOW
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH, width);
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT, height);
	fps = cvGetCaptureProperty(cap, CV_CAP_PROP_FPS);
    printf("Width: %d, Height: %d, FPS: %d\n", width, height, fps);

    cvNamedWindow ("view", CV_WINDOW_AUTOSIZE);

    while (1) {
        image = cvQueryFrame(cap);
        cvShowImage ("view", image);

        int key;
		key = cvWaitKey (1);
        if (key == 'q' || key == 27)
            break;
        if (key == 's') {
			saveImage(image);
        }
    }

    cvDestroyWindow("view");
    cvReleaseCapture(&cap);
    cvReleaseImage(&image);
    return 0;
}
