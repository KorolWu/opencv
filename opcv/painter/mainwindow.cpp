#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::onTimeout);
    this->resize(800,800);
    m_timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout()
{
    update();
}

void MainWindow::drawRangtale()
{
}

int MainWindow::getRandomValue()
{
    return QRandomGenerator::global()->bounded(0,255);
}

QPointF MainWindow::pointGennerator()
{
    int x = QRandomGenerator::global()->bounded(0,800);
    int y = QRandomGenerator::global()->bounded(0,800);
    QPointF p(x,y);
    return p;
}

QRectF MainWindow::rectGennerator(int width)
{
    //QPointF();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter m_painter(this);

    m_painter.drawLine(QPointF(50,700),QPointF(50,50));
    m_painter.drawLine(QPointF(25,75),QPointF(50,50));
    m_painter.drawLine(QPointF(75,75),QPointF(50,50));

    m_painter.drawLine(QPointF(50,700),QPointF(700,700));
    m_painter.drawLine(QPointF(675,675),QPointF(700,700));
    m_painter.drawLine(QPointF(675,725),QPointF(700,700));

    int rect_w = 5;
    int invator = 2;
    int width = 30;
    QVector<QPoint> lines;
    for(int i = 0; i < 15; i++)
    {
        QPoint left_top(60 + i*(width+rect_w+invator),700);
        QPoint right_bottom(60+width + i*(width+rect_w+invator),QRandomGenerator::global()->bounded(400,700));
        m_painter.setBrush(Qt::cyan); //添加画刷
        m_painter.drawRect(QRect(left_top,right_bottom));
        right_bottom.setY(right_bottom.y()-50);

        if(i == 0 || i ==14 )
        {

            lines.append(right_bottom);
        }
 lines.append(right_bottom); lines.append(right_bottom);
    }
    m_painter.setPen(QPen(QColor(255,0,0),3));
    m_painter.drawLines(lines);


    //m_painter.drawLine(pointGennerator(),pointGennerator());

}
