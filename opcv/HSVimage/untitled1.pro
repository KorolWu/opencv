#-------------------------------------------------
#
# Project created by QtCreator 2021-03-01T14:45:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

#--add OPENCV include
INCLUDEPATH += -I /usr/local/include/opencv4
DEPENDPATH +=/usr/local/include/opencv4

INCLUDEPATH += -I /usr/local/opencv/include/
DEPENDPATH +=/usr/local/opencv/include

 LIBS += -L /usr/local/opencv/lib/ -lopencv_videoio
 LIBS += -L /usr/local/opencv/lib/ -lopencv_video
 LIBS += -L /usr/local/opencv/lib/ -lopencv_stitching
 LIBS += -L /usr/local/opencv/lib/ -lopencv_photo
 LIBS += -L /usr/local/opencv/lib/ -lopencv_objdetect
 LIBS += -L /usr/local/opencv/lib/ -lopencv_ml
 LIBS += -L /usr/local/opencv/lib/ -lopencv_imgproc
 LIBS += -L /usr/local/opencv/lib/ -lopencv_imgcodecs
 LIBS += -L /usr/local/opencv/lib/ -lopencv_highgui
 LIBS += -L /usr/local/opencv/lib/ -lopencv_gapi
 LIBS += -L /usr/local/opencv/lib/ -lopencv_flann
 LIBS += -L /usr/local/opencv/lib/ -lopencv_features2d
 LIBS += -L /usr/local/opencv/lib/ -lopencv_dnn
 LIBS += -L /usr/local/opencv/lib/ -lopencv_core
 LIBS += -L /usr/local/opencv/lib/ -lopencv_calib3d
