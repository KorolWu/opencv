#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QImage>
#include <QThread>
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *m_label;
    Mat mat;
    Mat matbgr;
    Mat resize_dst;
    QPoint m_point;
    QImage convert(Mat &src);
    Mat QImage2Mat(QImage &image);
    Mat imageResize(Mat &image);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
