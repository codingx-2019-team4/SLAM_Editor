#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QProcess>

#include <stdlib.h>
#include <stdio.h>

#include <qnode.h>

#include <ros/ros.h>
#include <ros/network.h>

using namespace std;
using namespace Qt;
using namespace rosnode;

MainWindow::MainWindow(int argc,
                       char** argv,
                       QWidget *parent) :
                        QMainWindow(parent),
                        qnode(argc,argv),
                        ui(new Ui::MainWindow){
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
    ui->Eraser_THICKNESS->setRange(6, 25);
    ui->Pen_THICKNESS->setRange(3, 10);


    if(!ifstart){
        ui->Stop->setEnabled(false);
        //ui->Start->setEnabled(false);
        ui->mapSaveBt->setEnabled(false);
        ui->Save->setEnabled(false);
        //ui->starL->setText("Disconnected");
    }

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

void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    //close();
}


void MainWindow::on_Start_clicked()
{
    //ros::init(qnode.init_argc,init_argv,"FireHouse");
    if ( !qnode.check_master() ) {
        showNoMasterMessage();
        ifstart = false;
    }else {
        //ui->starL->setText("Connected");
        ui->Stop->setEnabled(true);
        ui->mapSaveBt->setEnabled(true);
        ui->Start->setEnabled(false);
        ifstart = true;
        process = new QProcess();
        try{
            process->startDetached("rosrun fire_app core_controller.py");
            //process->start("roslaunch fire_house gazebo.launch");
        }catch (exception& e){
            cout << "[ERROR] fire_app core_controller.py " << endl;
        }
    }
}



void MainWindow::on_Stop_clicked()
{
    //ui->starL->setText("Disconnected");
    ui->Stop->setEnabled(false);
    ui->mapSaveBt->setEnabled(false);
    ui->Start->setEnabled(true);
    ifstart = false;
    qnode.stop_map();
    try{
        process->terminate();
        process->kill();
        delete process;
    }catch (exception& e){
        cout << "Mapping terminate. " << endl;
    }
}

void MainWindow::on_mapSaveBt_clicked()
{
    //if(ifstart){
    if(ifstart){
        //QString path = QFileDialog::getExistingDirectory(this, tr("Choose directories"), ".", QFileDialog::ReadOnly);
        QString path = QFileDialog::getSaveFileName(
                            this, tr("Choose directories"));
        cout<< "[Directory22]" <<path.data()<<endl;
        cout<< "[Directory]" <<path.toStdString()<<endl;
        process2 = new QProcess();
        string com = path.toStdString();
        com = "rosrun map_server map_saver -f "+com;
        try{
            process2->start(com.c_str());
            process2->waitForFinished();
            process2->close();
            delete process2;
            cout<<"[Message] map saved. " << endl;
        }catch (exception& e){
            cout << "[ERROR] map server crash." << endl;
        }
    }else {
        cout<<"[ERROR] core crash. " << endl;
    }

}



void MainWindow::on_ImLoadB_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                        this, tr("open image file"),
                        "./", tr("Image files(*.bmp *.pgm *.png *.ppm);;All files (*.*)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    //QPixmap pixmap = ui->Canvas->grab();
    //pixmap.save(&file, "PNG");
}

void MainWindow::on_ImSaveB_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                        this, tr("open image file"),
                        "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

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
    ui->Save->setEnabled(true);
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
    char str[10];
    sprintf(str, "%dpx", position);
    ui->EraserThickness->setText(str);
}

// Pen's thickness adjustment
void MainWindow::on_Pen_THICKNESS_sliderMoved(int position)
{
    scene->setPenThickness(position);
    char str[10];
    sprintf(str, "%dpx", position);
    ui->PenThickness->setText(str);
}



void MainWindow::on_Undo_clicked()
{
    this->scene->undo();
}
