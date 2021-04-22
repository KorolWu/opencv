#include "mainwindow.h"
#include <QApplication>
//#include <QThread>
//#include "opencv2/opencv.hpp"
//#include <QTimer>
//#include <QDebug>
//using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Mat image = Mat::zeros(Size(510,512),CV_8UC3);
//    image = imread("/root/图片/IdPicture.jpeg");
//    imshow("resouce",image);
    return a.exec();
}
