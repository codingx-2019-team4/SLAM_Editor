#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "canvasscene.h"
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QScrollBar>l

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

private slots:
    // Change the type of the cursor
    void on_MS_eraser_clicked();
    void on_MS_painter_clicked();
    void on_MS_mouse_clicked();
    void wheelEvent(QWheelEvent *);

    void on_Save_clicked();
<<<<<<< Updated upstream
    //void on_pushButton_clicked();
=======
    void on_Load_clicked();
    void on_Eraser_THICKNESS_sliderMoved(int position);
    void on_Painter_THICKNESS_sliderMoved(int position);


    void on_Door_clicked();

    void on_Sensor_clicked();

protected:
>>>>>>> Stashed changes
};

#endif // MAINWINDOW_H
