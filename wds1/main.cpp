#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>
#include<QDebug>
int main(int argc, char *argv[])
{
    qDebug()<<"qergerg";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
