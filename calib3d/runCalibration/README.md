# Run Calibration
Run camera calibration from input images

# How to Use
it will read image from image dir  
ex: image/image0001.jpg, image/image0002.jpg, image/image0003.jpg...  
```
./runCalibration
```

# UseFul Function
```
CvMat matA;
printCvMat(matA, (char *)"matA");

Ptr<CvMat> matA
printCvMatPtr(matA, (char *)"matA");

vector<Point2f> points;
points.push_back(...);
drawCurve(points);
```
```
void printCvMat(CvMat m, char *p)
{
    printf("%s rows=%d cols=%d\n", p, m.rows, m.cols);
    int i;
    for (i = 0; i < m.rows*m.cols; i++) {
        printf("%lf ", m.data.db[i]);
        if (i%m.cols == m.cols-1)
            printf("\n");
    }
    printf("\n");
}

void printCvMatPtr(Ptr<CvMat> m, char *p)
{
    printf("%s rows=%d cols=%d\n", p, m->rows, m->cols);
    int i;
    for (i = 0; i < m->rows*m->cols; i++) {
        printf("%lf ", m->data.db[i]);
        if (i%m->cols == m->cols-1)
            printf("\n");
    }
    printf("\n");
}

void drawCurve(vector<Point2f> points)
{
    int i, j;
    Mat matM(300, 200, CV_8UC1);

    // init with zero
    for(int j = 0; j < matM.rows; j++)
        for(int i = 0; i < matM.cols; i++)
            matM.at<char>(j, i) = 0;

    // draw points
    for (i = 0; i < (int)points.size(); i++) {
        int x = points[i].x;
        int y = points[i].y;
        matM.at<char>(y, x) = 255;
    }

    // upside down
    Mat image = matM.clone();
    for (j = 0; j < image.rows; j++) {
        for(int i = 0; i < image.cols; i++) {
            image.at<char>(j, i) = matM.at<char>((matM.rows-1)-j, i);
        }
    }

    namedWindow("view", 0);
    imshow("view", image);
    waitKey(0);
}
```

# Reference
http://wycwang.blogspot.tw/2013/01/camera-calibration-part3-opencv.html
