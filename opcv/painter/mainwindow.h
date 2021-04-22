#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintDevice>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QBrush>

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
    void onTimeout();
private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    void drawRangtale();
    int getRandomValue();
    QPointF pointGennerator();
    QRectF rectGennerator(int width);
    QPainter m_painter;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
