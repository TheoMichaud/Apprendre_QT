#ifndef CLIENTBANQUEWINDOW_H
#define CLIENTBANQUEWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
    class ClientBanqueWindow;
}

class ClientBanqueWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientBanqueWindow(QWidget *parent = 0);
    ~ClientBanqueWindow();


private:
    Ui::ClientBanqueWindow *ui;
    QTcpSocket *tcpSocket;

private slots:
    void on_pushButtonEnvoyer_clicked();
    void on_pushButtonNumero_clicked();
    void on_pushButtonConnexion_clicked();

    void slotReadyRead();
    void slotConnected();
    void slotDisconnected();
};

#endif // CLIENTBANQUEWINDOW_H
