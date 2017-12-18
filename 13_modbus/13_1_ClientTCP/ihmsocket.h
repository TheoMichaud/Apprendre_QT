#ifndef IHMSOCKET_H
#define IHMSOCKET_H

#include <QWidget>
#include <QTcpSocket>
#include <QErrorMessage>
#include "modbustcp.h"

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

    void on_lineEditAdresse_textEdited(const QString &arg1);
    void on_lineEditNumeroPort_textEdited(const QString &arg1);
    void on_pushButtonConnexionAuServeur_clicked();

    void on_pushButtonF5_clicked();
    void on_pushButtonF1_clicked();
    void on_pushButtonF6_clicked();
    void on_pushButtonF3_clicked();

    void OnReponse(QString reponse);

private:
    Ui::IhmSocket *ui;
    QTcpSocket *socketDeDialogueAvecServeur;
    modbusTcp *modbus;
    QChar typeDeDemande;

};

#endif // IHMSOCKET_H
