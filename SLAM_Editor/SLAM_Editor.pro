#-------------------------------------------------
#
# Project created by QtCreator 2019-08-14T10:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++11
TARGET = SLAM_Editor
TEMPLATE = app

INCLUDEPATH += -I /opt/ros/kinetic/include
DEPENDPATH +=  /opt/ros/kinetic/include
LIBS += -L/opt/ros/kinetic/lib -lroscpp -lrospack -lpthread -lrosconsole -lrosconsole_log4cxx -lrosconsole_backend_interface -lxmlrpcpp -lroscpp_serialization -lrostime  -lcpp_common  -lroslib -ltf  -lyaml-cpp -lkdl_conversions

message($${PWD})

SOURCES += main.cpp\
        mainwindow.cpp \
    canvasscene.cpp \
    door.cpp \
    sensor.cpp \
    qnode.cpp \
    json.hpp

HEADERS  += mainwindow.h \
    canvasscene.h \
    door.h \
    sensor.h \
    qnode.h

INCLUDEPATH += $${PWD}/yaml-cpp/include

LIBS += $${PWD}/yaml-cpp/build/libyaml-cpp.a


FORMS    += mainwindow.ui
