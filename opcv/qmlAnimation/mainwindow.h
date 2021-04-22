#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMetaObject>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>
#include <QMainWindow>

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
    QObject *pRoot;
    QVariant CarId = "88";  // 返回值
    int state = 1;  // 方法参数
signals:
    void layerStateSignal(QString carId,int state);
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
