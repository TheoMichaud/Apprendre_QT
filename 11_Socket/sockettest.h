#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class socketTest : public QObject
{
    Q_OBJECT
public:
    explicit socketTest(QObject *parent = nullptr);

     void Connect();

signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // SOCKETTEST_H
