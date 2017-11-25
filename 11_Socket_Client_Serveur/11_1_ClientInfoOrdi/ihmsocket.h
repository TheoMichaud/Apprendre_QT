#ifndef IHMSOCKET_H
#define IHMSOCKET_H

#include <QWidget>
#include <QTcpSocket>
#include <QErrorMessage>

namespace Ui {
class IhmSocket;
}

class ClientDialogueWindows : public QWidget
{
    Q_OBJECT

public:
    explicit ClientDialogueWindows(QWidget *parent = 0);
    ~ClientDialogueWindows();

private slots:
    void 	onQTcpSocket_connected();
    void 	onQTcpSocket_disconnected();
    void 	onQTcpSocket_error(QAbstractSocket::SocketError socketError);
    void 	onQTcpSocket_hostFound();
    void 	onQTcpSocket_stateChanged(QAbstractSocket::SocketState socketState);
    void 	onQTcpSocket_aboutToClose();
    void 	onQTcpSocket_bytesWritten(qint64 bytes);
    void 	onQTcpSocket_readChannelFinished();
    void 	onQTcpSocket_readyRead();



    void on_lineEditAdresse_textEdited(const QString &arg1);

    void on_lineEditNumeroPort_textEdited(const QString &arg1);

    void on_pushButtonConnexionAuServeur_clicked();

    void on_pushButtonNomUtilisateur_clicked();

    void on_pushButtonNomMachine_clicked();

    void on_pushButtonNomDomaine_clicked();

    void on_pushButtonTypeDemarrage_clicked();




    void on_pushButtonHead_clicked();

    void on_pushButton_clicked();

private:
    Ui::IhmSocket *ui;
    QTcpSocket *socketDeDialogueAvecServeur;
    QChar typeDeDemande;
};

#endif // IHMSOCKET_H
