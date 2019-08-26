#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new CanvasScene(
                ui->Canvas->x(),
                ui->Canvas->y(),
                ui->Canvas->width()-2,
                ui->Canvas->height()-2
                );
   ui->Canvas->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// *** Mouse Status ***

// Change the mouse status to ERASER
void MainWindow::on_MS_eraser_clicked()
{
    ui->MStatus->setText("Eraser");
    scene->setEraser();
}

// Change the mouse status to PAINTER
void MainWindow::on_MS_painter_clicked()
{
    ui->MStatus->setText("Painter");
    scene->setPainter();
}

// Change the mouse status to MOUSEㄋ
void MainWindow::on_MS_mouse_clicked()
{
    ui->MStatus->setText("Mouse");
    scene->setMouse();
}

void MainWindow::on_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QPixmap pixmap = ui->Canvas->grab();
    pixmap.save(&file, "PNG");
}
