#include "connexion.h"
#include "ui_connexion.h"

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);

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



void Connexion::on_buttonBox_accepted()
{
    serveurIp = ui->lineEditAdresse  ->text();
    base = ui->lineEditBase->text();
    utilisateur = ui->lineEditUtilisateur->text();
    password = ui->lineEditPassword->text();

}
