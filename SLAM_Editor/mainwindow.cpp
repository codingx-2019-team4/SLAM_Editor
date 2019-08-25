#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <stdlib.h>
#include <stdio.h>

#include <qnode.h>

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
    close();
}


void MainWindow::on_Start_clicked(bool checked)
{
    if ( !qnode.init() ) {
        showNoMasterMessage();
    }else {
        ui->starL->setText("Connected");
    }
}


