#include <QApplication>
#include "serveurbanquewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeurBanqueWindow w;
    w.show();

    return a.exec();
}
