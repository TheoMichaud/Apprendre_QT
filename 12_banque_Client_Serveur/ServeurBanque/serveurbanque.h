#ifndef SERVEURBANQUE_H
#define SERVEURBANQUE_H

#include <QTcpServer>
#include "compteclient.h"


class ServeurBanque : public QTcpServer
{
    Q_OBJECT

public:
    explicit ServeurBanque(QObject *parent = 0);
    ~ServeurBanque();
    void start();
    void stop();

private:

    QList<CompteClient *> lesConnexionClients ;

private slots:
    void slotNewConnection();
    void slotClientDisconnected();
 };

#endif // SERVEURBANQUE_H
