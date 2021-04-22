#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,1000);
    Mat image = Mat::zeros(Size(510,512),CV_8UC3);
    image = imread("/root/图片/IdPicture.jpeg");
    //imshow("resouce",image);

    m_label = new QLabel(this);
    m_label->resize(this->width(),this->height());
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    QPixmap pix;
    Mat resizeIm = imageResize(image);
    pix.convertFromImage(convert(resizeIm));
    m_label->setPixmap(pix);


//    QImage i("/root/图片/IdPicture.jpeg");
//    Mat src = QImage2Mat(i);
//    imshow("src",src);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::convert(Mat &src)
{
    cvtColor(src,mat,COLOR_BGR2RGB);
    QImage im(mat.data,mat.cols,mat.rows,static_cast<int>(mat.step),QImage::Format_RGB888);
    return im;
}

Mat MainWindow::QImage2Mat(QImage &image)
{
    image = image.convertToFormat(QImage::Format_RGB888);
    Mat mat = Mat(image.height(),image.width(),CV_8UC3,image.bits(),static_cast<unsigned long>(image.bytesPerLine()));

    cvtColor(mat,matbgr,COLOR_RGB2BGR);

    return matbgr;
}

Mat MainWindow::imageResize(Mat &image)
{
    cv::resize(image,resize_dst,Size(),0.5,0.5);
    return resize_dst;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
       m_point = event->pos();
       qDebug()<<m_point.x()<<m_point.y();

    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}
