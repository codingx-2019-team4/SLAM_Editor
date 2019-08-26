#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QProcess>
#include "canvasScene.h"
#include "canvasView.h"
#include "qnode.h"

#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>

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

bool ifstart=false;
QProcess *process;
QProcess *process2;

private slots:
    // Change the type of the cursor
    void on_MS_eraser_clicked();
    void on_MS_painter_clicked();
    void on_MS_mouse_clicked();

    void on_Start_clicked();

    void on_Stop_clicked();

    void on_Save_clicked();


    void on_ImLoadB_clicked();

    void on_ImSaveB_clicked();

private:
    rosnode::QNode qnode;
    Ui::MainWindow *ui;
    CanvasView *canvasView;





    // QWidget interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#endif // MAINWINDOW_H
