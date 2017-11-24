#ifndef SERVEURBANQUE_H
#define SERVEURBANQUE_H
#include <QTcpServer>
#include "compteclient.h"
#include "interfaceaccesbdbanque.h"

class ServeurBanque : public QTcpServer
{
    Q_OBJECT
private:
    QList <CompteClient*> lesConnexionsClients;    

private slots:
    void onServeurBanque_newConnection();
    void onCompteClient_disconnected();
    void onCompteClient_readyRead();

public:
    ServeurBanque(QObject *parent=0);
    void Start();
    void Stop();
    void EnvoyerMessage(QString msg,CompteClient*client);



};

#endif // SERVEURBANQUE_H
