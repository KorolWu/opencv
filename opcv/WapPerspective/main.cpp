#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QApplication>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


Mat img ;

void getContours(Mat image)
{
    std::vector<std::vector<cv::Point> > vec;
    vector<vector<Point>> polyContours(1);
    cv::findContours(image,vec,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    for(int i = 0; i< static_cast<int>(vec.size());i++)
    {
        Mat m = static_cast<Mat>(vec.at(i));
        double area = cv::contourArea(m);
       // cv::drawContours(img,m,-1,Scalar(255,0,0),3); //画出轮廓
        double peri = cv::arcLength(m,true); //计算闭合曲线的周长
        if(peri > 179)
        {   qDebug()<<"arcLength:["<<i<<"]"<<peri;
//            Mat outImage;
//            cv::approxPolyDP(m,outImage,0.001*peri,true);

            Rect r = cv::boundingRect(m); //用一个矩形去包裹一个mat返回一个矩形
            approxPolyDP(m,polyContours[0],10,true); //逼近一个轮廓，得到一个轮廓的mat
            drawContours(img, polyContours, 0, Scalar(0,0,255/*rand() & 255, rand() & 255, rand() & 255*/), 2);

            vector<int>  hull;
            convexHull(polyContours[0], hull, false);    //检测该轮廓的凸包


            for (int i = 0; i < hull.size(); ++i){
                    circle(img, polyContours[0][i], 10, Scalar(rand() & 255, rand() & 255, rand() & 255), 3);
                }

            qDebug()<<r.x<<r.y<<r.height<<r.width;
            cv::rectangle(img,r,Scalar(255,0,0),1);
            cv::line(img,Point(r.x+(r.width/2),r.y+(r.height/2)),Point(r.x+(r.width/2),r.y+(r.height/2)),Scalar(255,0,0),13);
            //qDebug()<<"The center point[ "<<r.x+(r.width/2)<<","<<r.y+(r.height/2)<<" ]";
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    img = cv::imread("/root/图片/rectangle.png");

    Mat gray;
    cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);

    Mat blurImage ;
    cv::GaussianBlur(gray,blurImage,Size(27,27),0.5);

    Mat canny;

    cv::Canny(blurImage,canny,80,80);
    Mat erodeImage;
    cv::dilate(canny,erodeImage,cv::Mat());
    getContours(erodeImage);
    imshow("origin",img);
//    imshow("gray",gray);
    imshow("blurImage",blurImage);
    imshow("canny",canny);
  imshow("erod",erodeImage);

    return a.exec();
}
