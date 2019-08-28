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
   ui->Canvas->horizontalScrollBar()->setEnabled(false);
   ui->Canvas->verticalScrollBar()->setEnabled(false);
   ui->Canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->Canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    ui->Canvas->setInteractive(true);
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// Change the mouse status to PAINTER
void MainWindow::on_MS_painter_clicked()
{
    ui->MStatus->setText("Painter");
    scene->setPainter();
    ui->Canvas->setInteractive(true);
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// Change the mouse status to MOUSE
void MainWindow::on_MS_mouse_clicked()
{
    ui->MStatus->setText("Mouse");
    scene->setMouse();
    ui->Canvas->setInteractive(true);
    ui->Canvas->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::on_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.pgm);;All files (*.*)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QPixmap pixmap = ui->Canvas->grab();
    pixmap.save(&file, "PGM");
}

void MainWindow::wheelEvent(QWheelEvent *event){

    double degree = event->delta() / 1000.0;
    qDebug() << (1+degree);
    ui->Canvas->scale(1+degree, 1+degree);
}
