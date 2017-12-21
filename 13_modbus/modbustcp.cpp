#include "modbustcp.h"
#include <QDebug>
#include <QDataStream>

modbusTcp::modbusTcp(QObject *parent) : QObject(parent)
{
    transactionID = (quint16)0x0000;
    protocolID = (quint16)0x0000;
    UnitId = (quint8)0x00;

    // création de la socket
    pSocket=new QTcpSocket (this);

    // association des evenements possible liés à la socket
    connect( pSocket, SIGNAL( connected()),    this, SLOT (onQTcpSocket_connected()));
    connect( pSocket, SIGNAL( disconnected()), this, SLOT (onQTcpSocket_disconnected()));
    connect( pSocket, SIGNAL( error (QAbstractSocket::SocketError)), this, SLOT (onQTcpSocket_error (QAbstractSocket::SocketError)));
    connect( pSocket, SIGNAL( readyRead()),    this, SLOT(onQTcpSocket_readyRead()));
}

// Function 03 (03hex) Read holding Registers
// Read the binary contents of input registers in the slave.

void modbusTcp::ReadHoldingRegisters(quint16 adresse, quint16 nb)
{
    QByteArray buffer;
    QDataStream streamOut(&buffer, QIODevice::WriteOnly);
    streamOut << transactionID;
    streamOut << protocolID;
    streamOut << (quint16)0x0006;   //longueur de la trame PDU
    streamOut << UnitId;
    streamOut << (quint8)0x03;      // code fonction 03
    streamOut << (quint16)adresse;  // adresse du premier mot à lire
    streamOut << (quint16)nb;       // nombre de mot à lire
    qDebug() << " >> " << buffer;
    transactionID++;                // le code de transaction est incrémenté
    pSocket->write(buffer);
}


// Function 06 (06hex) Preset Single Register
// Writes a value into a single holding register.

void modbusTcp::PresetSingleRegister(quint16 adresse, quint16 valeur)
{
    QByteArray buffer;
    QDataStream streamOut(&buffer, QIODevice::WriteOnly);
    streamOut << transactionID;
    streamOut << protocolID;
    streamOut << (quint16)0x0006;   //longueur de la trame PDU
    streamOut << UnitId;
    streamOut << (quint8)0x06;      // code fonction 06
    streamOut << (quint16)adresse;  // adresse du mot
    streamOut << (quint16)valeur;   // la valeur à écrire
    qDebug() << " >> " << buffer;
    transactionID++;                // le code de transaction est incrémenté
    pSocket->write(buffer);
}

// Function 16 (10hex) Write Multiple Registers
// Writes values into a sequence of holding registers

void modbusTcp::WriteMultipleRegisters(quint16 adresse, QList<quint16> data)
{
    QByteArray buffer;
    QDataStream streamOut(&buffer, QIODevice::WriteOnly);
    streamOut << transactionID;
    streamOut << protocolID;
    quint16 length = (quint16)(7 + data.size() * 2);
    streamOut << length;   //longueur de la trame PDU
    streamOut << UnitId;
    streamOut << (quint8)0x10;      // code fonction 16
    streamOut << (quint16)adresse;  // adresse de base
    streamOut << (quint16)data.size();  // nb de mots
    streamOut << (quint8)(data.size() * 2); // nb d'octets
    for (int i=0; i<data.size(); i++)
    {
        streamOut << (quint16) data[i];
    }
    qDebug() << " >> " << buffer;
    transactionID++;                // le code de transaction est incrémenté
    pSocket->write(buffer);
}

// Function 5 (05hex) Write coil
void modbusTcp::ForceSingleCoil(quint16 adresse, bool valeur)
{
    QByteArray buffer;
    QDataStream streamOut(&buffer, QIODevice::WriteOnly);
    streamOut << transactionID;
    streamOut << protocolID;
    streamOut << (quint16)0x0006;   //longueur de la trame PDU  6 octets
    streamOut << UnitId;
    streamOut << (quint8)0x05;      // code fonction 05
    streamOut << (quint16)adresse;  // adresse de base
    if (valeur)
        streamOut << (quint16)0xff00;
    else
        streamOut << (quint16)0x0000;

    qDebug() << " >> " << buffer;
    transactionID++;                // le code de transaction est incrémenté
    pSocket->write(buffer);
}

// Function 1 (01hex) Read coil
void modbusTcp::ReadCoil(quint16 adresse, quint16 nb)
{
    QByteArray buffer;
    QDataStream streamOut(&buffer, QIODevice::WriteOnly);
    streamOut << transactionID;
    streamOut << protocolID;
    streamOut << (quint16)0x0006;   //longueur de la trame PDU  6 octets
    streamOut << UnitId;
    streamOut << (quint8)0x01;      // code fonction 01
    streamOut << (quint16)adresse;  // adresse de base
    streamOut << (quint16)nb;       // nb nombre de bits

    qDebug() << " >> " << buffer;
    transactionID++;                // le code de transaction est incrémenté
    pSocket->write(buffer);

}

// connexion au serveur
void modbusTcp::ConnecterEsclaveModBus(QString adresse, qint16 port)
{
     pSocket->connectToHost ( adresse, port );
}

// déconnexion du serveur
void modbusTcp::DeconnecterEsclaveModBus()
{
     pSocket->disconnectFromHost();
     pSocket->close();
}

void modbusTcp::onQTcpSocket_connected()
{
    connecte = true;
    qDebug() << "Connecté au serveur";
}

void modbusTcp::onQTcpSocket_disconnected()
{
    connecte = false;
    qDebug() << "Déconnecté";
}

void modbusTcp::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    QString message = "Oups une erreur !!! <br />" + pSocket->errorString();
    emit SocketErreur(socketError);
    qDebug() << message;
}

void modbusTcp::onQTcpSocket_readyRead()
{
    QDataStream fluxIn(pSocket);
    quint16 transactionId;
    quint16 ProtocolId;
    quint16 length;
    quint8 UnitId;
    quint8 fonctionCode;
    quint16 donnee;
    quint8 val;
    quint8 nb;
    QByteArray data;
    QString hexValue;

    if ( pSocket->bytesAvailable() > 6 )
    {
        fluxIn >> transactionId;
        fluxIn >> ProtocolId;
        fluxIn >> length;
        fluxIn >> UnitId;
        fluxIn >> fonctionCode;
    }
    switch (fonctionCode)
    {
    case 1:  // Read Coil
        fluxIn >> nb;
        fluxIn >> val;
        emit Reponse(01,val,"(F1) Read Coil : " + QString::number(val));
        break;

    case 3:   //Read holding registers
        fluxIn >> nb;
        fluxIn >> donnee;
        hexValue = QString("0x%1").arg(donnee, 4, 16, QLatin1Char( '0' ));
        emit Reponse(03,donnee,"(F3) Read holding registers : " + hexValue);
        break;

    case 5: // Force Single Coil
        emit Reponse(05,00,"(F5) Ecriture Coil effectuée");
        break;

    case 6: // Preset Single Register
        emit Reponse(06,00,"(F6) Ecriture Registre effectuée");
        break;

    case 16: // Write Multiple Registers
        emit Reponse(16,00,"(F16) Ecriture Registres multiples effectuée");
        break;

    default:

        fluxIn >> val;
        switch (val)
        {
        case 1:
            emit Erreur(fonctionCode, val, "Erreur : La fonction demandée n'est pas supportée");
            break;
        case 2:
            emit Erreur(fonctionCode, val, "Erreur : Adresse invalide");
            break;
        case 3:
            emit Erreur(fonctionCode, val, "Erreur : Valeur hors de la plage admissible");
            break;
        case 8:
            emit Erreur(fonctionCode, val, "Erreur : Valeur en lecture seule");
            break;
        default:
            emit Erreur(fonctionCode, val, "Erreur : type inconnue");

        }




    }
    fluxIn >> data;

}
