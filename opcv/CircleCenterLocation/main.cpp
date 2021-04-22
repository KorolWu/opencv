#include "mainwindow.h"
#include <QApplication>
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <math.h>
using namespace cv;
void answerCard(Mat src)
{
    Mat gray,binary,gauiss,se;
    GaussianBlur(src,gauiss,Size(5,5),0);
    cvtColor(src,gray,cv::COLOR_BGR2GRAY);
    threshold(gray,binary,0,255,THRESH_BINARY | THRESH_OTSU);
    std::vector<std::vector<cv::Point>> contours;
    findContours(binary,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);
    for(unsigned long i = 0;i < contours.size();i++)
    {
        double area = contourArea(contours[i]);
        if(area < 10)
        {
            drawContours(binary, contours, i, (0), -1);
        }
    }
    imshow("binary",binary);
    //detect each roi
    se = getStructuringElement(MORPH_RECT,Size(8,1));
    morphologyEx(binary,binary, MORPH_CLOSE, se);//
    std::vector<std::vector<cv::Point>> contours1;
    findContours(binary, contours1,RETR_TREE, CHAIN_APPROX_SIMPLE);
    imshow("binaryEnd",binary);
    for(unsigned long cnt = 0;cnt < contours1.size();cnt++)
    {
         Rect r = boundingRect(contours1[cnt]);
         qDebug()<<r.x<<r.y<<r.width<<r.height;
         rectangle(src, Point(r.x, r.y), Point(r.x+r.width, r.y+r.height), (0, 0, 255), 2, 8, 0);
    }
    imshow("result",src);
}
void findCricl()
{
    Mat image = imread("/root/图片/zsxq_15.jpg");
    Mat gauiss,gray,binary,se;
    GaussianBlur(image,gauiss,Size(5,5),0);
    cvtColor(gauiss,gray,cv::COLOR_BGR2GRAY);
    threshold(gray,binary,0,255,THRESH_BINARY | THRESH_OTSU);
    imshow("binary0",binary);

    se = getStructuringElement(MORPH_RECT,Size(25,25));//返回指定形状和尺寸的结构元素
    morphologyEx(binary,binary,MORPH_OPEN,se);//开运算---先腐蚀，后膨胀。去除图像中小的亮点
    imshow("binary",binary);
    std::vector<std::vector<cv::Point>> contours;
    findContours(binary,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);
    for(unsigned long i = 0;i < contours.size();i++)
    {
      double area =  contourArea(contours[i]);
      if (area < 10000)
           continue;
     Rect rect = boundingRect(contours[i]);
     RotatedRect rotarect = fitEllipse(contours[i]);//根据一组数据拟合一个椭圆，底层调用最小2乘法
     rectangle(image,Point(rotarect.center.x-(rotarect.size.width/2),rotarect.center.y - (rotarect.size.height/2)),Point(rotarect.center.x+(rotarect.size.width/2),rotarect.center.y + (rotarect.size.height/2)),Scalar(255,0,0));
     circle(image, Point(rotarect.center.x,rotarect.center.y),(rotarect.size.width+rotarect.size.height)/4, Scalar(0, 0, 255));
     circle(image, Point(rotarect.center.x,rotarect.center.y),2, Scalar(0, 0, 255));
     imshow("detect-circle", image);


    }
}
///
/// \brief hough 霍夫变换
///
void hough(Mat src)
{
    Mat gaussi,gray,binary,edges,se,cicle,dst;
//    GaussianBlur(src,gaussi,Size(15,15),0);
//    cvtColor(gaussi,gray,cv::COLOR_BGR2GRAY);
//    threshold(gray,binary,0,255,THRESH_BINARY | THRESH_OTSU);
//    imshow("binary",binary);
    Canny(src,edges,150,300);
    se = getStructuringElement(MORPH_RECT,Size(2,2));//返回指定形状和尺寸的结构元素
    morphologyEx(edges,edges,MORPH_CLOSE,se);//开运算---先膨胀，后腐蚀
    //imshow("canny",edges);
    std::vector<std::vector<cv::Point>> contours;
    findContours(edges,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);
    for(unsigned long ctn = 0;ctn < contours.size();ctn ++)
    {
      RotatedRect rect = minAreaRect(contours[ctn]);
      circle(src,Point(rect.center.x,rect.center.y),(rect.size.width+rect.size.height)/4,Scalar(0,0,255));
    }

    GaussianBlur(src,gaussi,Size(15,15),0);
    cvtColor(gaussi,gray,cv::COLOR_BGR2GRAY);
    std::vector<Vec3f> circles;
    HoughCircles(gray,circles, HOUGH_GRADIENT, 1, 20, 50, 100, 150, 350);
    circle(src,Point(circles[0][0],circles[0][1]),circles[0][2],Scalar(0,255,255));

    HoughCircles(gray,circles, HOUGH_GRADIENT, 2, 20, 50, 100, 310, 325);
    circle(src,Point(circles[0][0],circles[0][1]),circles[0][2],Scalar(255,0,255));

    addWeighted(src, 0.7, src, 0.3,0, dst);
    imshow("src",dst);

}
///
/// \brief getCricleCente
///通过hsv获取 圆心
///
void getCricleCente(Mat src)
{
    Mat gaussi,gray,hsvImage,mark;
    GaussianBlur(src,gaussi,Size(3,3),0);
    cvtColor(gaussi,hsvImage,COLOR_BGR2HSV);
    inRange(hsvImage,Scalar(156, 43, 46), Scalar(180, 255, 255),mark);
    imshow("mark",mark);
    std::vector<std::vector<cv::Point>> contours;
    findContours(mark,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);
    for(unsigned long ctn = 0;ctn < contours.size();ctn ++)
    {
//        Point layer_idx = contours[0][ctn];
//        if (layer_idx. == -1)
//                continue;
        if(contours[ctn].size()<5)//#拟合椭圆至少需要三个点
            continue;
      Rect r = boundingRect(contours[ctn]);
      RotatedRect rotatedRect = fitEllipse(contours[ctn]);//得到椭圆最小外接矩形
      circle(src,Point(rotatedRect.center.x,rotatedRect.center.y),(rotatedRect.size.width+rotatedRect.size.height)/4,Scalar(0,255,0));
      circle(src,Point(rotatedRect.center.x,rotatedRect.center.y),2,Scalar(255,0,0));
    }
    imshow("src",src);
}
void fixPicture(Mat src)
{
    resize(src,src,Size(800,600));
    Mat hsv, inpaintMask,res,gray,thres;
    //GaussianBlur(src,src,Size(3,3),0);
    inpaintMask = Mat::zeros(src.size(),CV_8U);
    //cvtColor(src,hsv,COLOR_BGR2HSV);
    cvtColor(src,gray,COLOR_BGR2GRAY);
    threshold(gray,thres,135,255,THRESH_BINARY);
    //inRange(hsv, Scalar(0 ,0, 128),Scalar(120, 114, 128),inpaintMask);
    imshow("inpaintMask",thres);
    inpaint(src, inpaintMask, res, 3, INPAINT_TELEA);
    imshow("Inpaint Output using FMM", res);
}
const int maxCount = 2;
static int count = 1;
Mat pr;
int  findNeiborhood(Mat mark,int cx,int cy, int direct)
{
    //left
   if(direct == 1)
   {
       for (int i = cx -10; i > 0; i--) {
           if(mark.ptr(cy,i)[0] == 255)
           {
               if(count < maxCount)
               {
                   line(mark,Point(cx,cy),Point(i,cy),255);
                   qDebug()<<i<<cy;
                   count ++;
               }
               return cx -i;
           }
       }
   }
   if(direct == 2)
   {
       for(int i = cx +10; i < mark.cols;i++)
       {
           if(mark.ptr(cy,i)[0] == 255)
           {
               return i - cx;
           }
       }
   }
   return -1;
}

void findMiss(Mat src)
{

    Mat gray,binary,mark;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    threshold(gray,binary,0,255,THRESH_OTSU|THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    findContours(binary, contours,RETR_TREE, CHAIN_APPROX_SIMPLE);
    //imshow("binaryEnd",binary);
    pr = Mat::zeros(src.rows,src.cols,binary.type());
    for(unsigned long cnt = 0;cnt < contours.size();cnt++)
    {
        if(contourArea(contours[cnt]) < 50)
            continue;
         Rect r = boundingRect(contours[cnt]);
         if(r.y+r.height > binary.rows -10)
             continue;
         circle(pr,Point(r.x + (r.width/2),r.y + (r.width/2)),6,255,4,8,0);

    }
   QList<int> buff;
   for(int i = 0;i <60;i++)
   {
       for(int j = pr.rows-60;j<pr.rows;j++)
       {
           int a = pr.ptr(j,i)[0] == 255? 1:0;
          buff.append(a);
       }
       qDebug()<<buff;
       buff.clear();
   }
   //qDebug()<<mark.ptr(58,563)[0];
    std::vector<std::vector<cv::Point>> contours1;
    findContours(pr,contours1,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for (unsigned long ctn = 0; ctn < contours1.size(); ctn ++) {
        Rect r = boundingRect(contours1[ctn]);
        //rectangle(src,Point(r.x,r.y),Point(r.x+r.width,r.y+r.height),Scalar(0,0,255));
//        String text = QString::number(ctn).toStdString();
//        putText(src,text,Point(r.x,r.y),1,1,Scalar(255,0,0));

        int cx = r.width/2 + r.x;
        int cy =  r.y + (r.height/2);
       // circle(mark,Point(cx,cy),1,0);

        int left = findNeiborhood(pr,cx,cy,1);
        int right = findNeiborhood(pr,cx,cy,2);
        //qDebug()<<" cnt="<<ctn<<"cx = "<<cx<<" cy="<<cy;
        //qDebug()<<"cnt = "<<ctn<<" left="<<left<<" right="<<right;
        if(left == -1 || right == -1)
            continue;
        if((right - left) > 21)
        {
            circle(src, Point(cx + left + 10, cy), 6, Scalar(0,0,255), 4, 8, 0);
        }
    }
    imshow("mark",pr);
      imshow("src",src);
}

void findCross(Mat src)
{
    //imshow("input",src);
    Mat gray,thres,ex1,ex2,ex3;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    threshold(gray,thres,0,255,THRESH_OTSU | THRESH_BINARY_INV);

    Mat x = getStructuringElement(MORPH_CROSS, Size(50, 1));
    Mat y = getStructuringElement(MORPH_CROSS, Size(1, 50));
    morphologyEx(thres,ex1,MORPH_OPEN,x);

    Mat mask = Mat::zeros(ex1.rows,ex1.cols,ex1.type());
    //ex1.copyTo(mask);
    morphologyEx(thres,ex2,MORPH_OPEN,y);
    std::vector<std::vector<cv::Point>> contours;
    findContours(ex1,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    int max_width = 0;
    int index = -1;
    qDebug()<<"contours size"<<contours.size();
    for (unsigned long int i = 0;i < contours.size();i++) {
        Rect c =  boundingRect(contours[i]);
        if(c.width > max_width)
        {
            max_width = c.width;
            index = i;
            qDebug()<<"contours i = "<<i;
        }
    }
    drawContours(mask,contours,index,255,-1,8);
    //imshow("x",mask);

    index = -1;
    int max_hight = 0;
    std::vector<std::vector<cv::Point>> contours1;
    findContours(ex2,contours1,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for(unsigned long i = 0;i < contours1.size();i++)
    {
        Rect r = boundingRect(contours1[i]);
        if((r.height > max_hight)  && (r.x < gray.cols *0.75))
        {
            max_hight = r.height;
            index = i;
        }
    }
    drawContours(mask,contours1,index,255,-1,8);
    //imshow("mask1",mask);

    Mat k = getStructuringElement(MORPH_CROSS, Size(13, 13));
    morphologyEx(mask,ex3,MORPH_OPEN,k);
    //imshow("corss", ex3);
     std::vector<std::vector<cv::Point>> contours2;
     findContours(ex3,contours2,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
     for(unsigned long i = 0; i< contours2.size();i++)
     {
         Rect r = boundingRect(contours2[i]);
         circle(src,Point(r.x + (r.width/2),(r.y + (r.height/2))),(r.width/2+r.height/2)/4,Scalar(0,0,255));
     }

    imshow("result",src);
}

void sort_box(std::vector<Rect> vr)
{
    size_t size = vr.size();
    for (size_t i = 0;i < size-1; i++) {
        for (size_t j = i;j <size;j++) {
            int y = vr[j].y;
            if(y < vr[i].y)
            {
                Rect temp = vr[i];
                vr[i] = vr[j];
                vr[j] = temp;
            }
        }
    }
}

Mat getTemplate(Mat binary,std::vector<Rect> rects)
{
    return binary(rects[0]);
}
///
/// \brief detect_defects 提取缺陷
/// \param binary
/// \param rects
/// \param tp1
/// \param defects
///
void detect_defects(Mat &binary,std::vector<Rect>rects, Mat &tp1, std::vector<Rect> &defects)
{
    int height = tp1.rows;
    int width = tp1.cols;
    int size = rects.size();
    for (int i = 0; i < size;i++) {
        Mat roi = binary(rects[i]);
        resize(roi,roi,tp1.size());
        Mat mask;
        subtract(tp1,roi,mask);
        Mat se = getStructuringElement(MORPH_RECT,Size(5,5),Point(-1,-1));
        morphologyEx(mask,mask,MORPH_OPEN,se);
        threshold(mask,mask,0,255,THRESH_BINARY);
        //imshow(QString("%1").arg(i).toStdString(),mask);
        int count = 0;
        for(int row = 0;row < height;row++)
        {
            for (int col = 0; col < width; col ++) {
                int pv = mask.at<uchar>(row,col);
                if(pv == 255)
                    count++;
            }
        }
        if(count > 0)
            defects.push_back(rects[i]);
    }
}

///
/// \brief defectDetection 缺陷检测
///
void defectDetection()
{
    Mat src = imread("/root/图片/delete.jpg");
    //imshow("src",src);
    Mat gray,binary;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    threshold(gray,binary,0,255,THRESH_BINARY_INV|THRESH_OTSU);
    imshow("binary",binary);
    Mat se = getStructuringElement(MORPH_RECT,Size(3,3));
    morphologyEx(binary,binary,MORPH_OPEN,se);

    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierachy;
    std::vector<Rect> rects;
    int height = binary.rows;
    findContours(binary.clone(),contours,hierachy,RETR_LIST,CHAIN_APPROX_SIMPLE);
    for (size_t t= 0; t < contours.size();t++) {
        Rect r = boundingRect(contours[t]);
        double area =contourArea(contours[t]);
        if(r.height > (height/2))
            continue;

        if(area < 150)
            continue;
        rects.push_back(r);
    }
    sort_box(rects);

    Mat tp1 = getTemplate(binary,rects);
    for (size_t t = 0; t <contours.size();t++) {
        Rect r = boundingRect(contours[t]);
        double area = contourArea(contours[t]);
        if(r.height > (height/2))
            continue;
        if(area < 150)
            continue;
        drawContours(binary,contours,t,Scalar(0),2,8);
    }
    imshow("binary1",binary);
    std::vector<Rect> defects;
    for(int i = 0;i <rects.size();i++)
    {
        putText(src,format("num: %d",i+1),Point(rects[i].x-40,rects[i].y+15),FONT_HERSHEY_PLAIN,1.0,Scalar(0,255,0),2);
    }
    detect_defects(binary,rects,tp1,defects);
    for (size_t i = 0;i < defects.size(); i++) {
        rectangle(src,defects[i],Scalar(0,0,255),1,8,0);
        putText(src,"bad",Point(defects[i].x,defects[i].y),FONT_HERSHEY_PLAIN,1.0,Scalar(0,255,0),2);
    }
    imshow("result",src);
    waitKey(0);
}

int max(int a,int b)
{
    return a >=b ? a:b;
}

void show2image()
{
    Mat src1 = imread("/root/图片/IdPicture.jpeg");
    Mat src2 = imread("/root/图片/ruiwen.jpeg");

    int width = src1.cols + src2.cols;
    int heitht = max(src1.rows , src2.rows);
    Mat two = Mat::zeros(Size(width,heitht),src1.type());
    //creat roi
    Rect r1(0,0,src1.cols,src1.rows);
    Rect r2(0,0,src2.cols,src2.rows);
    r2.x = src1.cols;
    //copy
    src1.copyTo(two(r1));
    src2.copyTo(two(r2));
    imshow("two",two);

    waitKey(0);
}

void detectCode(Mat src)
{
    Mat gray;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    //imshow("gray",gray);
    QRCodeDetector qrDetector;
    std::vector<Point> points;
    bool exist = qrDetector.detect(gray,points);
    if(exist)
    {
        String result = qrDetector.decode(gray,points);
//        qDebug()<<QString::fromStdString(result);
//        qDebug()<<points.size();
        circle(src,Point(points[0].x+((points[1].x-points[0].x)/2),(points[0].y+(points[2].y-points[0].y)/2)),3,Scalar(0,0,255));
        //绘制二维码的边框
        for (int i = 0; i < points.size(); i++)
        {
            if (i == points.size() - 1)
            {
                line(src, points[i], points[0], Scalar(0, 255,0), 2, 8);
                break;
            }
            line(src, points[i], points[i + 1], Scalar(0,255, 0 ), 2, 8);
        }
        //将解码内容输出到图片上
        putText(src, result.c_str(), Point(20, 30), 0, 0.8, Scalar(255,0, 0),2,8);

    }
    else {
        qDebug()<<"not have QRCode";
    }
    imshow("src",src);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
     //Mat src = imread("/root/图片/qr.png");
     //answerCard(src);
    //hough(src);
    // getCricleCente(src);
     //fixPicture(src);
     //findCross(src);
     //findMiss(src);
     //show2image();
     //defectDetection();
    for(int i = 1;i < 7;i++)
    {
        if(i ==6)
        {
            i = 1;
            continue;
        }
        QString fileName = QString("code%1").arg(i);
        fileName = "/root/图片/"+fileName+".png";
        Mat src = imread(fileName.toStdString());
        detectCode(src);
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
    }
     waitKey(0);
    //return a.exec();
}
