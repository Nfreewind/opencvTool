#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void help()
{
    cout << "\nThis program is used to match template\n"
        "Usage:\n"
        "./matchTemplate image_name template_image_name\n\n";
}

int compareImage(char* image_name, char* templ_name, CvPoint* point, int method = 1)
{
    int ret = 0;
    IplImage* image;
    IplImage* templ;
    IplImage* result;
    int width, height;

    image = cvLoadImage(image_name, CV_LOAD_IMAGE_COLOR);
    templ = cvLoadImage(templ_name, CV_LOAD_IMAGE_COLOR);

    width = image->width - templ->width + 1;
    height = image->height - templ->height + 1;

    result = cvCreateImage(cvSize(width, height), IPL_DEPTH_32F, 1);

    cvMatchTemplate(image, templ, result, CV_TM_SQDIFF_NORMED);

    if (method == 1) {
        // use cvMinMaxLoc() to get the result (by minimum value)
        double min_val;
        double max_val;
        CvPoint min_loc;
        CvPoint max_loc;
        cvMinMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, NULL);
        cvRectangle(image, cvPoint(min_loc.x, min_loc.y), cvPoint(min_loc.x + templ->width, min_loc.y + templ->height),
                cvScalar(0, 0, 255));
        point->x = min_loc.x;
        point->y = min_loc.y;
        printf("found (%d, %d)\n", point->x, point->y);
        ret = 1;
    } else {
        // use threshold to get the result
        float threshold = 0.01f; // change this value to get the good result
        CvScalar s;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // get an element value
                s = cvGet2D(result, i, j);

                // if value below the threshold, similar objects was found
                if (s.val[0] <= threshold) {
                    cvRectangle(image, cvPoint(j, i), cvPoint(j + templ->width, i + templ->height),
                            cvScalar(0, 0, 255));
                    point->x = j;
                    point->y = i;
                    printf("found (%d, %d)\n", point->x, point->y);
                    ret = 1;
                }
            }
        }
    }

    cvNamedWindow("view", CV_WINDOW_AUTOSIZE);
    cvShowImage("view", image);
    cvWaitKey(0);
    cvDestroyWindow("view");

    cvReleaseImage(&image);
    cvReleaseImage(&templ);
    cvReleaseImage(&result);

    return ret;
}

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        help();
        return 1;
    }

    int result;
    CvPoint point;
    point.x = -1;
    point.y = -1;

    result = compareImage((char *)argv[1], (char *)argv[2], &point, 2);
    if (result) {
        cout << "x: " << point.x << ", y: " << point.y << endl;
    }

    return 0;
}
