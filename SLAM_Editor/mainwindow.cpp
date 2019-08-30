#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Canvas->setGeometry(180, 20, 1000, 1000);
    scene = new CanvasScene(
                0,
                0,
                1984,
                1984
                );
   ui->Canvas->setScene(scene);
   ui->Canvas->setInteractive(true);
   ui->Canvas->horizontalScrollBar()->setEnabled(false);
   ui->Canvas->verticalScrollBar()->setEnabled(false);
   ui->Canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->Canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->Eraser_THICKNESS->setRange(10, 100);
   ui->Painter_THICKNESS->setRange(5, 30);
   ui->Doors->setGeometry(QRect(0, 0, this->width(), this->height()));
   qDebug()<<ui->Doors->geometry();
   ui->Doors->setEnabled(false);
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
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// Change the mouse status to PAINTER
void MainWindow::on_MS_painter_clicked()
{
    ui->MStatus->setText("Painter");
    scene->setPainter();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// Change the mouse status to MOUSE
void MainWindow::on_MS_mouse_clicked()
{
    ui->MStatus->setText("Mouse");
    scene->setMouse();
    ui->Canvas->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::on_Door_clicked()
{
    ui->MStatus->setText("Door");
    scene->setDoor();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
    ui->Doors->setEnabled(true);
}

void MainWindow::on_Sensor_clicked()
{
    ui->MStatus->setText("Sensor");
    scene->setSensor();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}


// Save image of what shows in Canvas
void MainWindow::on_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.pgm);;All files (*.*)"));
    QFile file(fileName + "_withIcons");
    file.open(QIODevice::WriteOnly);
    QImage pixmap(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter painter(&pixmap);
    scene->render(&painter);
    pixmap.save(&file, "PGM");
    file.close();

    scene->hideIcons();

    QFile file2(fileName);
    file2.open(QIODevice::WriteOnly);
    QImage pixmap2(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter painter2(&pixmap2);
    scene->render(&painter2);
    pixmap2.save(&file2, "PGM");
    file2.close();
}

// Scale Canvas view with wheel
void MainWindow::wheelEvent(QWheelEvent *event){

    double degree = event->delta() / 1000.0;
    ui->Canvas->scale(1+degree, 1+degree);
}

// Load pgm picture into canvas
void MainWindow::on_Load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.pgm);;All files (*.*)"));
    scene->setBackground(fileName);
}

void MainWindow::on_Eraser_THICKNESS_sliderMoved(int position)
{
    scene->setEraserThickness(position);
}

void MainWindow::on_Painter_THICKNESS_sliderMoved(int position)
{
    scene->setPainterThickness(position);
}


