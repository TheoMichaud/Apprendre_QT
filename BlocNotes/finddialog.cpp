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
    QString texte = ui->texteRecherche->text(); // QLineEdit
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if ( ui->checkBoxArriere->isChecked()) // QCheckBox
        emit rechercherPrecedent(texte, cs);
    else
        emit rechercherSuivant(texte, cs);
}
