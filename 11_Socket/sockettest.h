#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class socketTest : public QObject
{
    Q_OBJECT
public:
    explicit socketTest(QObject *parent = nullptr);

     void LireEntete();
     void FixerHostname(QString adresse);

signals:

public slots:
     void connected();
     void disconnected();
     void bytesWritten (qint64 bytes);
     void readyRead();

private:
    QTcpSocket *socket;
    QString hostname;
};

#endif // SOCKETTEST_H
