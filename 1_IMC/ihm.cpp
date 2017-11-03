#include "ihm.h"
#include "ui_ihm.h"
#include <QDebug>

IHM::IHM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHM)
{
    ui->setupUi(this);
    if(!connect(ui->pushButtonDevine, SIGNAL(clicked(bool)),this,SLOT(Devine())))
        qDebug() << "Erreur connexion Bouton Devine";
    ui->QTabOnglet->setCurrentIndex(0);

}

IHM::~IHM()
{
    delete ui;
}



void IHM::on_pushButtonSuite_clicked()
{
    ui->QTabOnglet->setCurrentIndex(1);
    ui->QTabOnglet->widget(1)->setVisible(true);
    AfficherInfos();
}

void IHM::AfficherInfos()
{

    // Initialisation de poids, taille, âge, nom et prénom
    nom = ui->lineEditNom->text();
    prenom = ui->lineEditPrenom->text();
    age = ui->spinBoxAge->value();
    poids = ui->doubleSpinBoxPoids->value();
    taille = ui->doubleSpinBoxTaille->value();

    double imc = poids/(taille * taille);

    // affichage du message de bienvenue
    ui->textEditAfficheur->setText("Bienvenue : <b>"+prenom+ " "+nom+"</b>");
    ui->textEditAfficheur->append("Votre indice de masse corporelle est : <b>" + QString::number(imc, 'f', 1) + "</b>");
    ui->textEditAfficheur->append("\nVotre Corpulence est qualifié de : <b>" + DeterminerClassification(imc) + "</b>");

}



QString IHM::DeterminerClassification(double imc)
{
    double imcs[NB_IMC] = {16.5, 18.5, 25, 30, 35, 40};
    QString corpulences[NB_CORPULENCE] = {"Famine",
                                          "Maigreur",
                                          "Normale",
                                          "Surpoids",
                                          "Obésité modérée",
                                          "Obésité sévère",
                                          "Obésité morbide"};
    int indiceCorpulence = 0;

    for (int i = 0; i < NB_IMC - 1; i++) {
        if (imc > imcs[i] && imc <= imcs[i + 1]) {
            indiceCorpulence = i + 1;
        }
    }
    // les cas extremes
    if (imc < imcs[0]) {
        indiceCorpulence = 0;
    }
    if (imc > imcs[NB_IMC-1]) {
       indiceCorpulence = NB_CORPULENCE - 1;
    }
    return corpulences[indiceCorpulence];

}

void IHM::Devine()
{
    double poidsIdeal = 0;

    if (ui->radioButtonFemme->isChecked()) {
        poidsIdeal = 45.5 + 2.3 * (taille / 0.0254 - 60.0);
    }
    if (ui->radioButtonHomme->isChecked()) {
        poidsIdeal = 50.0 + 2.3 * (taille / 0.0254 - 60.0);
    }
    if (poidsIdeal > 0) {
        ui->textEditAfficheur->append("\nVotre poids idéal avec la formule de Devine est : <b>" + QString::number(poidsIdeal, 'f', 1) + " kg </b>");
        double ecart = poids-poidsIdeal;
        if (ecart >= 0) {
          ui->textEditAfficheur->append("Vous devez perdre : <b>"+QString::number(ecart, 'f', 1)+" kg</b>\n");
        }
        else {
          ui->textEditAfficheur->append("Vous devez prendre : <b>"+QString::number(-ecart, 'f', 1)+" kg</b>\n");
        }
    }

}

void IHM::Lorentz()
{
    double poidsIdeal = 0;

    if (ui->radioButtonFemme->isChecked()) {
        poidsIdeal = taille * 100.0 - 100.0 -(taille*100-150)/2.5;
    }
    if (ui->radioButtonHomme->isChecked()) {
        poidsIdeal = taille * 100.0 - 100.0 -(taille*100-150)/4;
    }
    if (poidsIdeal > 0) {
        ui->textEditAfficheur->append("\nVotre poids idéal avec la formule de Lorentz est : <b>" + QString::number(poidsIdeal, 'f', 1) + " kg</b>");
        double ecart = poids-poidsIdeal;
        if (ecart >= 0) {
          ui->textEditAfficheur->append("Vous devez perdre : <b>"+QString::number(ecart, 'f', 1)+" kg</b>\n");
        }
        else {
          ui->textEditAfficheur->append("Vous devez prendre : <b>"+QString::number(-ecart, 'f', 1)+" kg</b>\n");
        }
    }
}

void IHM::LorentzAge()
{
    double poidsIdeal = 0;

    poidsIdeal = 50.0 + (taille*100 - 150)/4 + (age - 20)/4;
    if (poidsIdeal > 0) {
        ui->textEditAfficheur->append("\nVotre poids idéal avec la formule de Lorentz tenant compte de l'âge : <b>" + QString::number(poidsIdeal, 'f', 1) + " kg</b>");
        double ecart = poids-poidsIdeal;
        if (ecart >= 0) {
          ui->textEditAfficheur->append("Vous devez perdre : <b>"+QString::number(ecart, 'f', 1)+" kg</b>\n");
        }
        else {
          ui->textEditAfficheur->append("Vous devez prendre : <b>"+QString::number(-ecart, 'f', 1)+" kg</b>\n");
        }
    }
}






void IHM::on_pushButtonLorentz_clicked()
{
    Lorentz();
}

void IHM::on_pushButtonLorentzAge_clicked()
{
    LorentzAge();
}


void IHM::on_QTabOnglet_currentChanged(int index)
{
    if(index == 1){
        AfficherInfos();

    }
}
