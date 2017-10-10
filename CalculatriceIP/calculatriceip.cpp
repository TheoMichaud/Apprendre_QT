#include "calculatriceip.h"
#include "ui_calculatriceip.h"
#include <QtMath>
#include "adresseipv4.h"

CalculatriceIP::CalculatriceIP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatriceIP)
{

    quint32 leMasque = 0xff000000;
    quint32 fenetre;
    quint8  octet;
    QString masque;



    ui->setupUi(this);

    for(int valeur=8; valeur<=30; valeur++){
        ui->comboBoxSuffixe->addItem(QString::number(valeur));

        masque = "";
        fenetre  = 0xFF000000;
        for(int indice = 0 ; indice < 4 ; indice++)
        {
            octet = (leMasque & fenetre) >> (8 * (3-indice));
            masque += QString::number(octet) ;
            if (indice<3){
                masque += "." ;
                fenetre >>= 8 ;
            }

        }
        // Ecriture du masque sur l'IHM
         ui->comboBoxMasque->addItem(masque);
         // Calcul et Ecriture du nombre maximum de sous réseaux
         int nbReseaux = 0;
         if (valeur != 30)
            nbReseaux = qPow(2,(32 - valeur-2));
         ui->comboBoxSousReseaux->addItem(QString::number(nbReseaux));
         // Calcul et Ecriture du nombre maximum d'adresses IP
         int nbHotes = (qPow(2,(32 - valeur))) -2;
         ui->compoBoxAdressesIP->addItem(QString::number(nbHotes));

         leMasque >>= 1 ;
         leMasque |= 0x80000000;
    }
    ui->comboBoxSuffixe->setCurrentIndex(16);
    ui->lineEditAdresse1->setValidator(new QIntValidator(1,223));
    ui->lineEditAdresse2->setValidator(new QIntValidator(0,255));
    ui->lineEditAdresse3->setValidator(new QIntValidator(0,255));
    ui->lineEditAdresse4->setValidator(new QIntValidator(0,254));

    connect(ui->lineEditAdresse1, SIGNAL(textChanged(QString)), this, SLOT(onAdresseIPChange()));
    connect(ui->lineEditAdresse2, SIGNAL(textChanged(QString)), this, SLOT(onAdresseIPChange()));
    connect(ui->lineEditAdresse3, SIGNAL(textChanged(QString)), this, SLOT(onAdresseIPChange()));
    connect(ui->lineEditAdresse4, SIGNAL(textChanged(QString)), this, SLOT(onAdresseIPChange()));
}

CalculatriceIP::~CalculatriceIP()
{
    delete ui;
}

void CalculatriceIP::on_comboBoxSuffixe_currentIndexChanged(int index)
{
    ui->comboBoxMasque->setCurrentIndex(index);
    ui->comboBoxSousReseaux->setCurrentIndex(index);
    ui->compoBoxAdressesIP->setCurrentIndex(index);

    bool OK;
    quint8 tabAdresse[4];
    tabAdresse[0] = ui->lineEditAdresse1->text().toInt(&OK);
    tabAdresse[1] = ui->lineEditAdresse2->text().toInt(&OK);
    tabAdresse[2] = ui->lineEditAdresse3->text().toInt(&OK);
    tabAdresse[3] = ui->lineEditAdresse4->text().toInt(&OK);

    quint8 suffixe = ui->comboBoxSuffixe->currentText().toInt(&OK);

    AdresseIPv4 adresse(tabAdresse,suffixe);   // création d'un objet adresse IPv4
    adresse.ObtenirAdresseReseau(tabAdresse);  // appelle de la méthode obtenir adresse réseau
    QString adresseReseau;
    adresseReseau = ConvertirTableauIpEnQString(tabAdresse);
    adresseReseau += " / ";
    adresseReseau += ui->comboBoxSuffixe->currentText();
    ui->lineEditAdresseReseau->setText(adresseReseau);   // affichage de l'adresse réseau

    adresse.ObtenirAdresseDiffusion(tabAdresse);  // appelle de la méthode obtenir adresse de diffusion

    ui->lineEditAdresseDiffusion->setText(ConvertirTableauIpEnQString(tabAdresse));  // affichage de l'adresse de diffusion

    adresse.ObtenirPremiereAdresse(tabAdresse);  // appelle de la methode première adresse réseau
    QString plageAdresse = ConvertirTableauIpEnQString(tabAdresse);
    plageAdresse += "    -    ";
    adresse.ObtenirDerniereAdresse(tabAdresse);  // appelle de la méthode dernière adresse réseau
    plageAdresse += ConvertirTableauIpEnQString(tabAdresse);
    ui->lineEditAdresseUtilisables->setText(plageAdresse);
}


// Corrigé de la Question 10
void CalculatriceIP::onAdresseIPChange()
{
    on_comboBoxSuffixe_currentIndexChanged(ui->comboBoxSuffixe->currentIndex());
}


// Fonction pour transformer un tableau IP en chaîne de caractères
QString CalculatriceIP::ConvertirTableauIpEnQString(const quint8 _tabIp[])
{
    QString chaine;
    for(int indice = 0 ; indice < 4 ; indice++)
    {
        chaine += QString::number(_tabIp[indice]) ;
        if (indice<3)
            chaine += "." ;
    }
    return chaine;
}
