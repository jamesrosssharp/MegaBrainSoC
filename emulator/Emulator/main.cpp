#include "mainwindow.h"
#include <QApplication>

#include "cortexm0cpu.h"
#include "rom.h"
#include "systembus.h"

#include "megabrain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
