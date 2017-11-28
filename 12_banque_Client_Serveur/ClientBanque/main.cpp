#include "clientbanquewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientBanqueWindow w;
    w.show();

    return a.exec();
}
