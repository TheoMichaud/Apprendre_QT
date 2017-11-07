#include "connexion.h"
#include "ui_connexion.h"

connexion::connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexion)
{
    ui->setupUi(this);
}

connexion::~connexion()
{
    delete ui;
}

QString connexion::ServeurIp()
{
    return serveurIp;
}

QString connexion::Base()
{
    return base;
}

QString connexion::Utilisateur()
{
    return utilisateur;
}

QString connexion::Password()
{
    return password;
}



void connexion::on_buttonBox_accepted()
{
    serveurIp = ui->lineEditServeurIP->text();
    base = ui->lineEditBase->text();
    utilisateur = ui->lineEditUtilisateur->text();
    password = ui->lineEditPassword->text();
}
