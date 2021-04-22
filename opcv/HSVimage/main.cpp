#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "opencv2/opencv.hpp"
#include <QDebug>
using namespace std;
using namespace cv;

Mat HSVimage;
Mat Result;
int h_mini=0 , h_max =179, s_mini=0 , s_max=177 , v_mini =0  ,v_max=171;
//cv::Scalar inputArray (h_mini,s_mini,v_mini);
//cv::Scalar outputArray (h_max,s_max,v_max);
void updateImage()
{
    cv::Scalar inputArray (h_mini,s_mini,v_mini);
    cv::Scalar outputArray (h_max,s_max,v_max);
    cv::inRange(HSVimage,inputArray,outputArray,Result);
    imshow("result",Result);

}
void onHueChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    h_mini = v;
    updateImage();
}
void onHueMaxChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    h_max = v;
    updateImage();
}
void onsetChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    s_mini = v;
    updateImage();

}
void onsetMaxChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    s_max = v;
    updateImage();
}
void onVminiChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    v_mini = v;
    updateImage();
}
void onVmaxChange(int v,void* userdata)
{
    Q_UNUSED(userdata)
    v_max = v;
    updateImage();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();


    Mat img = imread("/root/图片/lanbo.jpeg");
    imshow("out",img);

    cv::namedWindow("TrackBars");
    cv::resizeWindow("TrackBars",640,240);
    int h_start = 0;
    int h_end = 19;
    int s_start = 100;
    int s_end = 240;
    int v_start = 0;
    int v_end = 100;
    cv::createTrackbar("Hue Min","TrackBars",&h_start,179,onHueChange);
    cv::createTrackbar("Hue Max","TrackBars",&h_end,179,onHueMaxChange);
    cv::createTrackbar("Sat Min","TrackBars",&s_start,255,onsetChange);
    cv::createTrackbar("Sat Max","TrackBars",&s_end,255,onsetMaxChange);
    cv::createTrackbar("Val Min","TrackBars",&v_start,100,onVminiChange);
    cv::createTrackbar("Val Max","TrackBars",&v_end,255,onVmaxChange);

    //         h_mini =  cv::getTrackbarPos("Hue Min","TrackBars");
    //         h_max =  cv::getTrackbarPos("Hue Max","TrackBars");
    //         s_mini =  cv::getTrackbarPos("Sat Min","TrackBars");
    //         s_max =  cv::getTrackbarPos("Sat Max","TrackBars");
    //         v_mini =  cv::getTrackbarPos("Val Min","TrackBars");
    //         v_max =  cv::getTrackbarPos("Val Max","TrackBars");


    cv::cvtColor(img,HSVimage,cv::COLOR_BGR2HSV);

    imshow("HSVimage",HSVimage);

    return a.exec();
}
