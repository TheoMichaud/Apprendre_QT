#include "ihmsocket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientDialogueWindows w;
    w.show();

    return a.exec();
}
