#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new CanvasScene(0, 0, 1984, 1984);  // Size of the input map

    // Variables initialize
    this->viewSize = new double(1000);

    // Canvas setup
    ui->Canvas->setGeometry(180, 20, *viewSize, *viewSize);     // Resize
    ui->Canvas->setScene(scene);                                // Set scene
    ui->Canvas->setDragMode(QGraphicsView::ScrollHandDrag);     // Set to hand drag
    ui->Canvas->horizontalScrollBar()->setEnabled(false);       // Turn off scroll bar moving
    ui->Canvas->verticalScrollBar()->setEnabled(false);
    ui->Canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Hide the scroll bar
    ui->Canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Slider setup
    ui->Eraser_THICKNESS->setRange(10, 100);
    ui->Pen_THICKNESS->setRange(5, 30);


}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

// *** Mouse Status ***

// To MOUSE
void MainWindow::on_MS_mouse_clicked()
{
    ui->MStatus->setText("Mouse");
    scene->setMouse();
    ui->Canvas->setDragMode(QGraphicsView::ScrollHandDrag);
}

// To PEN
void MainWindow::on_MS_pen_clicked()
{
    ui->MStatus->setText("Pen");
    scene->setPen();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// To ERASER
void MainWindow::on_MS_eraser_clicked()
{
    ui->MStatus->setText("Eraser");
    scene->setEraser();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// To DOOR
void MainWindow::on_Door_clicked()
{
    ui->MStatus->setText("Door");
    scene->setDoor();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}

// To SENSOR
void MainWindow::on_Sensor_clicked()
{
    ui->MStatus->setText("Sensor");
    scene->setSensor();
    ui->Canvas->setDragMode(QGraphicsView::NoDrag);
}


// *** File ***

// Save image of what shows in Canvas
void MainWindow::on_Save_clicked()
{
    // Set path
    QString fileName = QFileDialog::getSaveFileName(
                    this, tr("open image file"),
                    "../map", tr("Image files(*.pgm);;All files (*.*)"));

    // Save image
    QFile file(fileName + "_full");
    file.open(QIODevice::WriteOnly);
    QImage pixmap(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter painter(&pixmap);
    scene->render(&painter);
    pixmap.save(&file, "PGM");
    file.close();

    // Save image without marked
    scene->hideIcons();
    QFile file2(fileName);
    file2.open(QIODevice::WriteOnly);
    QImage pixmap2(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter painter2(&pixmap2);
    scene->render(&painter2);
    pixmap2.save(&file2, "PGM");
    file2.close();
}

// Load pgm picture into canvas
void MainWindow::on_Load_clicked()
{
    // Load image selected
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "../res/", tr("Image files(*.pgm);;All files (*.*)"));

    // Render to background of scene
    scene->setBackground(fileName);
}


// *** Drawing features ***

// Scale Canvas view with wheel
void MainWindow::wheelEvent(QWheelEvent *event){

    double degree = event->delta() / 2000.0;

    // Restrict the scaling of Canvas
    if(*viewSize / (1 + degree) < 1984){
        ui->Canvas->scale(1+degree, 1+degree);
        *viewSize /= (1 + degree);
    }
}

// Eraser's thickness adjustment
void MainWindow::on_Eraser_THICKNESS_sliderMoved(int position)
{
    scene->setEraserThickness(position);
}

// Pen's thickness adjustment
void MainWindow::on_Pen_THICKNESS_sliderMoved(int position)
{
    scene->setPenThickness(position);
}


