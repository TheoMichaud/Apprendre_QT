#include "serveurmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeurMainWindow w;
    w.show();

    return a.exec();
}
