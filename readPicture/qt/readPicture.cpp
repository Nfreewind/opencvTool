#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

using namespace cv;

static QImage Mat2QImage(Mat& mat)
{
    QImage qimg;

    if (mat.channels() == 3) {
        cvtColor(mat, mat, CV_BGR2RGB);
        qimg = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.cols*mat.channels(), QImage::Format_RGB888);
    } else if (mat.channels() == 1) {
        qimg = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.cols*mat.channels(), QImage::Format_ARGB32);
    } else {
        qimg = QImage((const unsigned char *)(mat.data), mat.cols, mat.rows,
                mat.cols*mat.channels(), QImage::Format_RGB888);
    }

    return qimg;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget *widget = new QWidget;
    widget->setWindowTitle("Display image");

    QString filename = QFileDialog::getOpenFileName(0, "Open Image", "", "*.jpg *.png *.bmp", 0);
    if (filename.isNull()) {
        return 1;
    }

    Mat mat = imread(filename.toStdString(), IMREAD_COLOR);
    QImage image = Mat2QImage(mat);

    QLabel *label = new QLabel("", 0);
    label->setPixmap(QPixmap::fromImage(image));

    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    widget->setLayout(layout);

    widget->show();

    return app.exec();
}
