#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Mat image = imread("/root/图片/jihe2.png");
    int blockSize = 4;
    int aperureSize = 3;
    double k = 0.04;
    Mat gray,dst;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    cornerHarris(gray,dst,blockSize,aperureSize,k);

    //Normalizing
    Mat dst_borm = Mat::zeros(dst.size(),dst.type());
    normalize(dst,dst_borm,0,255,NORM_MINMAX);
    convertScaleAbs(dst_borm,dst_borm);

    //find maxvalue pixel
    double min,max;
    minMaxLoc(dst_borm,&min,&max);
    qDebug()<<"min pixel:"<<min<<"max pixel:"<<max;
    //Drawing acircle around corners
    for(int row = 0;row < dst_borm.rows;row++)
    {
        for(int clo= 0; clo < dst_borm.cols; clo++)
        {
             int rsp =  dst_borm.at<uchar>(row,clo);
            if(rsp > max*0.169)
            {
                int b = QRandomGenerator::global()->bounded(0,255);
                int g = QRandomGenerator::global()->bounded(0,255);
                int r = QRandomGenerator::global()->bounded(0,255);
                circle(image,Point(clo,row),5,Scalar(b,g,r),2);
            }
        }
    }
    imshow("Corner",image);

    return a.exec();
}
