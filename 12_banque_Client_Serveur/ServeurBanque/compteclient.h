#ifndef COMPTECLIENT_H
#define COMPTECLIENT_H

#include <QTcpSocket>
#include <QObject>

class CompteClient : public QObject
{
    Q_OBJECT
public:
    explicit CompteClient(QTcpSocket *_socketClient);
    void EnvoyerMessage(QString message);
    int getNumCompte();
    void setNumCompte(int compte);
    void deposer(float val);
    bool retirer(float val);
    float getSolde();

signals:
    void disconnected();

private slots:
    void slotReadyRead();
    void slotDisconnected();

private:
    int numCompte ;
    float solde ;
    QTcpSocket *socketClient;

};

#endif // COMPTECLIENT_H
