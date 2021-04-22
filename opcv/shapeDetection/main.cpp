#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QApplication>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
Mat img;
void getContours(Mat image)
{
    std::vector<std::vector<cv::Point> > vec;
    cv::findContours(image,vec,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    for(int i = 0; i< static_cast<int>(vec.size());i++)
    {
        Mat m = static_cast<Mat>(vec.at(i));
        double area = cv::contourArea(m);
        // cv::drawContours(img,m,-1,Scalar(255,0,0),3); //画出轮廓
        double peri = cv::arcLength(m,true); //计算闭合曲线的周长
        qDebug()<<"arcLength:["<<i<<"]"<<peri;
        Mat outImage;
        cv::approxPolyDP(m,outImage,0.001*peri,true);

        Rect r = cv::boundingRect(m);
        qDebug()<<r.x<<r.y<<r.height<<r.width;
        Rect rect(r.x,r.y,r.x+r.width,r.y+r.height);
        cv::rectangle(img,r,Scalar(255,0,0),1);
        cv::line(img,Point(r.x+(r.width/2),r.y+(r.height/2)),Point(r.x+(r.width/2),r.y+(r.height/2)),Scalar(0,0,255),3);
        qDebug()<<"The center point[ "<<r.x+(r.width/2)<<","<<r.y+(r.height/2)<<" ]";
    }
}

void transform(Mat image)
{
    std::vector<std::vector<cv::Point> > vec;
    cv::findContours(image,vec,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    for(int i = 0; i< static_cast<int>(vec.size());i++)
    {
        Mat m = static_cast<Mat>(vec.at(i));
        double area = cv::contourArea(m);
        if(area > 2000)
        {
            std::cout<<m<<endl;
             cv::drawContours(img,m,-1,Scalar(255,0,0),3); //画出轮廓
            double peri = cv::arcLength(m,true); //计算闭合曲线的周长
            qDebug()<<"arcLength:["<<i<<"]"<<peri;
            Mat outImage;
            cv::approxPolyDP(m,outImage,0.001*peri,true);

            Rect r = cv::boundingRect(m);
            qDebug()<<r.x<<r.y<<r.height<<r.width;
            Rect rect(r.x,r.y,r.x+r.width,r.y+r.height);
            cv::rectangle(img,r,Scalar(255,0,0),1);
            cv::line(img,Point(r.x+(r.width/2),r.y+(r.height/2)),Point(r.x+(r.width/2),r.y+(r.height/2)),Scalar(0,0,255),3);
            qDebug()<<"The center point[ "<<r.x+(r.width/2)<<","<<r.y+(r.height/2)<<" ]";

            vector<Point2f> src_ret(4);
            src_ret[0] =Point2f(r.x,r.y);
            src_ret[1] =Point2f(r.x+r.width,r.y);
            src_ret[2] =Point2f(r.x,r.y+r.height);
            src_ret[3] =Point2f(r.x+r.width,r.y+r.height);

            vector<Point2f> dst_ret(4);
            dst_ret[0] = Point2f(0,0);
            dst_ret[1] = Point2f(460,0);
            dst_ret[2] = Point2f(0,380);
            dst_ret[3] = Point2f(460,380);
            //transform
            Mat cropped = img(r);
            Mat m1 = getPerspectiveTransform(src_ret,dst_ret);
            Mat resultImage;
            warpPerspective(cropped,resultImage,m1,Size(460,380),INTER_LINEAR);
            imshow("PerspectiveDemo",resultImage);

        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    img = cv::imread("/root/图片/left12.jpg");

    Mat grayImg;
    cv::cvtColor(img,grayImg,cv::COLOR_BGR2GRAY);

    Mat blurImage ;
    cv::GaussianBlur(grayImg,blurImage,Size(47,47),1);

    Mat canny;
    cv::Canny(blurImage,canny,50,50);

    transform(canny);

    cv::imshow("origin",img);
    //print(img);
    //    cv::imshow("gray",grayImg);
    //  cv::imshow("blur",blurImage);
    //  cv::imshow("canny",canny);
    return a.exec();
}
