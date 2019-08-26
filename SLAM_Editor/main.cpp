#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QProcess process;
    process.start("touch hello.txt");

    return a.exec();
}
