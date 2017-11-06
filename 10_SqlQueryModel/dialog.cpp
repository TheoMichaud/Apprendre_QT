#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QString mdp = QInputDialog::getText(this,"Mot de passe"," Mot de passe : ");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("philippes.ddns.net");     // le hostname ou l'adresse IP du serveur mySQL
    db.setUserName("QtUtilisateur");          // le nom de l'utilisateur
    db.setPassword(mdp);               // le mot de passe de l'utilisateur
    db.setDatabaseName("pi");                 // le nom de la base
    if (db.open())
    {
        // l'ouverture de la base réussie
        this->modele = new QSqlTableModel(this);
        modele->setTable("people");          // Sélection de la table
        modele->select();                    // remplissage du modèle avec le contenu de la table
        modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification

        ui->tableView->setModel(modele);     // association du modèle à la vue
        ui->tableView->hideColumn(0);        // masquer la première colonne (les id)
    }
    else
    {
        // l'ouverture de la base a échouée
        // affichage de la boîte de dialoque critical

        QMessageBox::critical(this, "Erreur SQL", db.lastError().driverText());
    }


}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}
