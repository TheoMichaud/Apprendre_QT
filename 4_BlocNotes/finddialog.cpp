#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    ui->pushButtonRechercher->setEnabled(false);
}

FindDialog::~FindDialog()
{
    delete ui;
}

// Ce slot est est appelé dès que le texte change dans le QLineEdit et qui permettra
// d’activer le bouton « Rechercher » si un texte a été saisi

void FindDialog::on_texteRecherche_textChanged(const QString &arg1)
{
    if(arg1 != "")
        ui->pushButtonRechercher->setEnabled(true);
    else
        ui->pushButtonRechercher->setEnabled(false);
}

// invoqué lorsque l’utilisateur clique sur le bouton « Rechercher » et qui
// permettra l’émission d’un signal en fonction des choix des cases à cocher

void FindDialog::on_pushButtonRechercher_clicked()
{


    QTextDocument::FindFlag options;
    int value = 0;
    if (ui->checkBoxArriere->isChecked())
        value = 1;   // Search backwards instead of forwards.
    if (ui->checkBoxCasse->isChecked())
        value +=2;   // Specifying this option changes the behaviour to a case sensitive find operation.
    if (ui->checkBoxMotEntier->isChecked())
        value +=4;   // Makes find match only complete words.
    options = (QTextDocument::FindFlag) value;

    if ( !ui->checkBoxExpReg->isChecked()){
        QString expression = ui->texteRecherche->text(); // le texte du QLineEdit
        emit rechercher(expression, options);   // recherche normale
    }
    else{
        QRegExp expression(ui->texteRecherche->text());
        emit rechercherReg(expression, options);  // recherche avec les expressions régulières
    }
}
