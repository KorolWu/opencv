#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QQuickView *view = new QQuickView;

    view->rootContext()->setContextProperty("MainWindow",this);
//    QString  str = "mainwindow str";
//    view->rootContext()->setContextProperty("str",str);
    QWidget *widget = QWidget::createWindowContainer(view,this);
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl("/root/Studying/opcv/qmlAnimation/LayerState.qml"));

    widget->resize(250,120);
    widget->move(70,60);
    pRoot = static_cast<QObject*>(view->rootObject());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(state > 3)
        state = 1;
    // 调用 QML 方法
    QMetaObject::invokeMethod(pRoot, "carReadyIn",
                              Q_ARG(QVariant, CarId),
                              Q_ARG(QVariant, state));
    state = state +1;;






}
