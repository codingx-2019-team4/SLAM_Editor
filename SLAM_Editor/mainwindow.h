#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qnode.h"
#include "canvasscene.h"

#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QScrollBar>
#include <QMessageBox>

#include <stdlib.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <string>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();

void showNoMasterMessage();

bool ifstart = false;
QProcess *process;
QProcess *process2;

private:
    Ui::MainWindow *ui;
    CanvasScene *scene;
    rosnode::QNode qnode;
    double *viewSize;

private slots:
    // Change the type of the cursor
    void on_MS_mouse_clicked();
    void on_MS_pen_clicked();
    void on_MS_eraser_clicked();
    void on_Door_clicked();
    void on_Sensor_clicked();

    // Image IO
    void on_imgSaveBt_clicked();
    void on_imgLoadBt_clicked();

    // Drawing features
    void wheelEvent(QWheelEvent *);
    void on_Eraser_THICKNESS_sliderMoved(int position);
    void on_Pen_THICKNESS_sliderMoved(int position);

    void on_Undo_clicked();


    
    void on_mapStartBt_clicked();
    void on_mapSaveBt_clicked();
    void on_mapStopBt_clicked();
    
    // void on_ImLoadB_clicked();
    // void on_ImSaveB_clicked();


    // QWidget interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#endif // MAINWINDOW_H
