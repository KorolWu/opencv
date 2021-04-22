#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QDebug>
using namespace std;
using namespace cv;
void meanStd(Mat image)
{
    double minv,maxv;
    Point minLoc,maxLoc;
    vector<Mat> mv;
    split(image,mv);
    for (int i = 0; i<(static_cast<int>(mv.size()));i++) {
        minMaxLoc(mv.at(i),&minv,&maxv,&minLoc,&maxLoc);
       qDebug()<<"channels:"<<i<<"min value: "<<minv<<"max value: "<<maxv<<"minPosition:["<<minLoc.x<<","<<minLoc.y<<"]"<<"maxPosition: ["<<maxLoc.x<<maxLoc.y<<"]";
    }

    Mat mean,stddve;
    meanStdDev(image,mean,stddve);
    std::cout<<"means:"<<mean<<std::endl;
    std::cout<<"stddve:"<<stddve<<std::endl;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Mat image;// = Mat::zeros(512,512,CV_8UC3);
    image = imread("/root/图片/IdPicture.jpeg");
    imshow("resouce",image);
//    Mat hsv;
//    cvtColor(image,hsv,COLOR_BGR2HSV);
//    Mat mark;
//    inRange(hsv,Scalar(100,43,46),Scalar(124,255,255),mark);

//    Mat reback = Mat::zeros(image.size(),image.type());
//    reback = Scalar(20,20,255);
//    imshow("reback",reback);

//    bitwise_not(mark,mark);
//    imshow("mark",mark);
    //是将image中的mark部分复制到reback中
//    image.copyTo(reback,mark);
//    imshow("result",reback);


    meanStd(image);
    return a.exec();
}
