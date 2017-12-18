/*--------------------------------------------------------------------------------------*/
/* 
 * File :		Serveur.h
 * Author :		Marc Fournier
 * Date :		12/07/10
 * Comment :	Modbus server
 */
/*--------------------------------------------------------------------------------------*/

#ifndef HEADER_Serveur_H
#define HEADER_Serveur_H

#include <QCoreApplication>
#include <QtNetwork>
#include "ModbusFrame.h"
#include "ModbusServer.h"


class Serveur : QObject
{
    Q_OBJECT

    public:
        Serveur();

    private slots:
        void nouvelleConnexion();
        void donneesRecues();
        void deconnexionClient();

    private:
        QTcpServer * serveur;
        QList<QTcpSocket *> clients;

        ModbusServer serverMB;
};

#endif

