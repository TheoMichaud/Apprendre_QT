#include <QCoreApplication>
#include "Serveur.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Serveur serveurMB;
	
    return app.exec();
}
