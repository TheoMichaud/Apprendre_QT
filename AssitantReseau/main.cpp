#include "assitantreseau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AssitantReseau w;
    w.show();

    return a.exec();
}
