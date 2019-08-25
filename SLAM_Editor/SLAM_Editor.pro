#-------------------------------------------------
#
# Project created by QtCreator 2019-08-24T17:06:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLAM_Editor
TEMPLATE = app

INCLUDEPATH += -I /opt/ros/kinetic/include
DEPENDPATH +=  /opt/ros/kinetic/include
LIBS += -L/opt/ros/kinetic/lib -lroscpp -lrospack -lpthread -lrosconsole -lrosconsole_log4cxx -lrosconsole_backend_interface -lxmlrpcpp -lroscpp_serialization -lrostime  -lcpp_common  -lroslib -ltf  -lyaml-cpp -lkdl_conversions

SOURCES += main.cpp\
        mainwindow.cpp \
    canvasscene.cpp

HEADERS  += mainwindow.h \
    canvasscene.h

FORMS    += mainwindow.ui
