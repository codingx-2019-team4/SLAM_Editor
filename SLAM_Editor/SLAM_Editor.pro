#-------------------------------------------------
#
# Project created by QtCreator 2019-08-24T17:06:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLAM_Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvasscene.cpp \
    door.cpp \
    sensor.cpp

HEADERS  += mainwindow.h \
    canvasscene.h \
    door.h \
    sensor.h

FORMS    += mainwindow.ui
