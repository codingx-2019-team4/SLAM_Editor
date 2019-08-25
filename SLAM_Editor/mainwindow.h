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

private slots:
    // Change the type of the cursor
    void on_MS_eraser_clicked();
    void on_MS_painter_clicked();
    void on_MS_mouse_clicked();

    void on_Start_clicked();

    void on_Stop_clicked();

private:
    Ui::MainWindow *ui;
    rosnode::QNode qnode;
    CanvasView *canvasView;





    // QWidget interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#endif // MAINWINDOW_H
