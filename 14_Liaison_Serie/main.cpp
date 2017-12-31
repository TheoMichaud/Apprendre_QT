#include <QCoreApplication>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>

QT_USE_NAMESPACE
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Example use QSerialPortInfo
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();

            // Example use QSerialPort
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
                serial.close();
        }

    return a.exec();
}
