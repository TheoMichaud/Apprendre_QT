/**
 * @brief Définition des méthodes de la classe crypto
 * @author Philippe SIMIER
 * @date 31/12/2017
 * @details
 *  Classe modélisant un systéme de cryptographie simple
 *  Parfois, vous devez stocker certaines informations que vous pourriez vouloir protéger
 *  contre une observation occasionnelle comme les  mots de passe pour les services distants, par exemple.
 *  La cryptographie forte est évidemment la meilleure solution, mais il peut être difficile de l'utiliser
 *  de la bonne manière. Elles ont tendance à utiliser des bibliothèques volumineuses, et franchement,
 *  cela peut être exagéré pour certaine situation.
 *  Ici je propose un système basé sur le système de substitution polyalphabétique.
 *  les décalages sont opérés à partir d'une clé de longueur quelconque.
 *  si la clé à pour longueur un seul caractère,  c'est la méthode de César
 *  si la clé est très longue alors le système est plus robuste.
 *  pour ne pas avoir à saisir comme clé une phrase très longue et donc difficile à mémoriser.
 *  J'utilise plutôt comme clé une empreinte SHA512 obtenu à partir d'une suite de caractères plus simple à mémoriser.
 */


// Only symmetric encryption is supported (= same key for encryption and decryption required)
// https://wiki.qt.io/Simple_encryption_with_SimpleCrypt

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


