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

    canvasView = new CanvasView();
    ui->Canvas->addWidget(canvasView);

    canvasView->setInteractive(true);

    if(!ifstart){
        //ui->Start->setEnabled(false);
        ui->Stop->setEnabled(false);
        ui->Save->setEnabled(false);
        ui->ImSaveB->setEnabled(false);
        ui->starL->setText("Disconnected");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


// *** Mouse Status ***

// Change the mouse status to ERASER
void MainWindow::on_MS_eraser_clicked()
{
    canvasView->setEraser();
    ui->MStatus->setText("Eraser");
}

// Change the mouse status to PAINTER
void MainWindow::on_MS_painter_clicked()
{
    canvasView->setPainter();
    ui->MStatus->setText("Painter");
}

// Change the mouse status to MOUSEㄋ
void MainWindow::on_MS_mouse_clicked()
{
    canvasView->setMouse();
    ui->MStatus->setText("Mouse");
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
        ui->starL->setText("Connected");
        ui->Stop->setEnabled(true);
        ui->Save->setEnabled(true);
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
    ui->starL->setText("Disconnected");
    ui->Stop->setEnabled(false);
    ui->Save->setEnabled(false);
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

void MainWindow::on_Save_clicked()
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
