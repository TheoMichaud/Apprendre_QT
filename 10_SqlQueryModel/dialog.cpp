#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.10");     // l'adresse IP du serveur mySQL
    db.setUserName("QtUtilisateur");    // le nom de l'utilisateur
    db.setPassword("password");         // le mot de passe de l'utilisateur
    db.setDatabaseName("pi");           // le nom de la base

    db.open();
    this->modele = new QSqlTableModel(this);
    modele->setTable("people");          // Sélection de la table
    modele->select();                    // remplissage du modèle avec le contenu de la table
    modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification

    ui->tableView->setModel(modele);     // association du modèle à la vue
    ui->tableView->hideColumn(0);        // masquer la première colonne (les id)
}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}
