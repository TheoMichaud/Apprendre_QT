#ifndef SERVEURMAINWINDOW_H
#define SERVEURMAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>

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
    QTcpSocket *clientConnexion;
    QProcess   *process;

private slots:
    void slotNewConnection();
    void slotReadyRead();
    void slotDisconnected();
    void slotReadFromStdOutput();
};

#endif // SERVEURMAINWINDOW_H
