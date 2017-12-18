#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include <QObject>
#include <QTcpSocket>

class modbusTcp : public QObject
{
    Q_OBJECT
public:
    explicit modbusTcp(QObject *parent = nullptr);
    void PresetSingleRegister(quint16 adresse, quint16 valeur);
    void ReadHoldingRegisters(quint16 adresse, quint16 nb);
    void WriteMultipleRegisters(quint16 adresse, QList<quint16> data);
    void ForceSingleCoil(quint16 adresse, bool valeur);
    void ReadCoil(quint16 adresse, quint16 nb);
    void ConnecterEsclaveModBus(QString adresse, qint16 port);
    void DeconnecterEsclaveModBus();

signals:
    void Reponse(QString expression);

public slots:
    void 	onQTcpSocket_connected();
    void 	onQTcpSocket_disconnected();
    void 	onQTcpSocket_error(QAbstractSocket::SocketError socketError);
    void 	onQTcpSocket_readyRead();

private:
    QTcpSocket *pSocket;
    qint16 transactionID;
    qint16 protocolID;
    quint8 UnitId;
    bool connecte;

};

#endif // MODBUSTCP_H
