#include "crypto.h"
#include "ui_crypto.h"

Crypto::Crypto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Crypto)
{
    ui->setupUi(this);
}

Crypto::~Crypto()
{
    delete ui;
}

// Slot quand la clé a été saisie
void Crypto::on_buttonBox_accepted()
{
    QString cle = ui->lineEditClef->text();
    emit clef(cle);
}

// méthode pour chiffrer ou déchiffrer un contenu
void Crypto::Coder(QString &contenu, QString clef, FONCTION opt)
{

    int lg,lc;  // longueur de la clé
    ushort decalage;
    lg = clef.size();
    lc = contenu.size();

    for (int i = 0; i< lc; i++){

        if (clef.at(i % lg).unicode() > 96)
            decalage = clef.at(i % lg).unicode()-96;  // 'a' -> 1 'b' -> 2 etc
        else if (clef.at(i % lg).unicode() > 64)
            decalage = clef.at(i % lg).unicode()-64;  // 'A' -> 1 'B' -> 2 etc
        else if (clef.at(i % lg).unicode() > 47)   // '0'-> 1 '1' -> 2
            decalage = clef.at(i % lg).unicode()-47;
        else
            decalage = clef.at(i % lg).unicode();  // les espaces -> 32

        if (contenu.at(i).unicode() > 19){   // les codes spéciaux ne sont pas chiffrés
            if (opt == CHIFFRER){

                contenu[i] = contenu.at(i).unicode() + decalage;
            }
            else{

                contenu[i] = contenu.at(i).unicode() - decalage;
            }
        }
    }
}

// Méthode pour obtenir l'empreinte Sha512 de la clef
QString Crypto::Sha512(QString clef)
{
    QCryptographicHash hash(QCryptographicHash::Sha512);
    hash.addData(clef.toUtf8());
    return hash.result().toHex();
}


