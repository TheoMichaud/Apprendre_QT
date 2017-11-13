#include <QCoreApplication>
#include "sockettest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socketTest unTest;
    unTest.Connect();

    return a.exec();
}
