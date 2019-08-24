#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
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

    //Mouse status
    void setMouse();
    void setEraser();
    void setPainter();

private:
    Ui::MainWindow *ui;
    CanvasScene *scene;

private slots:
    // Change the type of the cursor
    void on_MS_eraser_clicked();
    void on_MS_painter_clicked();
    void on_MS_mouse_clicked();

};

#endif // MAINWINDOW_H
