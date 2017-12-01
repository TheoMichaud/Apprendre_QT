#ifndef SERVEURMAINWINDOW_H
#define SERVEURMAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include <QErrorMessage>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QComboBox>
#include <QLabel>


namespace Ui {
class ServeurMainWindow;
}

class ServeurMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServeurMainWindow(QWidget *parent = 0);
    ~ServeurMainWindow();

private:
    Ui::ServeurMainWindow *ui;
    QTcpServer *tcpServeur;
    QList <QTcpSocket *> lesConnexionsClients;  // liste des clients connectés
    QComboBox *myComboBoxClient; //La comboBox pour afficher les clients connectés
    QProcess   *process;

private slots:
    void slotNewConnection();
    void slotReadyRead();
    void slotDisconnected();
    void slotReadFromStdOutput();
    void on_actionQuitter_triggered();
    void on_actionA_propos_triggered();
    void on_actionD_connecter_le_client_triggered();
};

#endif // SERVEURMAINWINDOW_H
