#include "connexion.h"
#include "ui_connexion.h"

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");

}

Connexion::~Connexion()
{
    delete ui;
}

QString Connexion::ServeurIp()
{
    return serveurIp;
}

QString Connexion::Base()
{
    return base;
}

QString Connexion::Utilisateur()
{
    return utilisateur;
}

QString Connexion::Password()
{
    return password;
}

// Au click sur le bouton OK
// Ouverture de la base sélectionnée

void Connexion::on_buttonBox_accepted()
{
    serveurIp = ui->lineEditAdresse  ->text();
    utilisateur = ui->lineEditUtilisateur->text();
    password = ui->lineEditPassword->text();
    base = ui->comboBoxBases->currentText();

    db.setDatabaseName(ui->comboBoxBases->currentText());
    if(!db.open())
    {
        QMessageBox::information(this, "Erreur !!!", db.lastError().driverText());
    }

}


// Au click sur le bouton connexion
// Etablissement d'une  connexion au serveur pour
// appeler la fonction lire les bases disponibles

void Connexion::on_pushButton_clicked()
{
    db.setHostName(ui->lineEditAdresse->text());          // l'adresse IP du serveur mySQL
    db.setUserName(ui->lineEditUtilisateur->text());      // le nom de l'utilisateur
    db.setPassword(ui->lineEditPassword->text());         // le mot de passe de l'utilisateur
    if(!db.open())
    {
        QMessageBox::information(this, "Erreur !!!", db.lastError().driverText());
    }
    else
    {
        lireBases();
        ui->comboBoxBases->setEnabled(true);
        ui->label_Base->setEnabled(true);
        ui->buttonBox->setEnabled(true);
    }
}

// Fonction pour lire les base de données disponibles
// sur un serveur connectée.

void Connexion::lireBases()
{
    ui->comboBoxBases->clear();
    QSqlQuery maRequete(db);
    maRequete.exec("SHOW DATABASES;");
    while (maRequete.next()) {
        QVariant base = maRequete.value(0);
        ui->comboBoxBases->addItem(base.toString());
    }
}
