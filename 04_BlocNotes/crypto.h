#ifndef CRYPTO_H
#define CRYPTO_H

#include <QDialog>
#include <QDebug>
#include <QCryptographicHash>

namespace Ui {
class Crypto;
}

class Crypto : public QDialog
{
    Q_OBJECT


public:
    explicit Crypto(QWidget *parent = 0);
    ~Crypto();

    enum FONCTION{
        CHIFFRER = 1,
        DECHIFFRER = 2,
    };

    void Coder(QString &contenu, QString clef, FONCTION opt);
    QString Sha512(QString clef);



private slots:
    void on_buttonBox_accepted();

signals:
    void clef(QString clef);

private:
    Ui::Crypto *ui;
};

#endif // CRYPTO_H
