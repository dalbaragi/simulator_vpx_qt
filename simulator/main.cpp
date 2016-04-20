//--------------------------------------------------------------------------------------
//++++ edit by LRH ++++
//20151027
//can send UDP datagram, automatically select 本地连接
//--------------------------------------------------------------------------------------

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
