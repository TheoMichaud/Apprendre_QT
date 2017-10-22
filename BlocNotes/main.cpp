#include "blocnotes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    blocNotes w;
    w.show();

    return a.exec();
}
