#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QScrollBar>
#include <stdio.h>
#include "canvasscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    CanvasScene *scene;
    double *viewSize;

private slots:
    // Change the type of the cursor
    void on_MS_mouse_clicked();
    void on_MS_pen_clicked();
    void on_MS_eraser_clicked();
    void on_Door_clicked();
    void on_Sensor_clicked();

    // Image IO
    void on_Save_clicked();
    void on_Load_clicked();

    // Drawing features
    void wheelEvent(QWheelEvent *);
    void on_Eraser_THICKNESS_sliderMoved(int position);
    void on_Pen_THICKNESS_sliderMoved(int position);

};

#endif // MAINWINDOW_H
