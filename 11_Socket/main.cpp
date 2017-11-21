#include <QCoreApplication>
#include "sockettest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socketTest test1;
    test1.FixerHostname("Exemple.com");
    test1.LireEntete();

    socketTest test2;
    test2.FixerHostname("google.fr");
    test2.LireEntete();


    socketTest test3;
    test3.FixerHostname("www.google.fr");
    test3.LireEntete();

    return a.exec();
}
