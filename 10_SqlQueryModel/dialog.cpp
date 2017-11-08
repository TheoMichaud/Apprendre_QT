#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");

    Wconnexion = new connexion();

    this->modele = new QSqlTableModel(this);
    modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification
    ui->tableView->setModel(modele);     // association du modèle à la vue

    ouvrirBase();
}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << "Connexion";
    ouvrirBase();
}

void Dialog::ouvrirBase()
{
    //  efface le modèle
    modele->clear();
    // efface la liste des tables
    ui->comboBoxTable->clear();

    // lance la fenêtre connexion
    Wconnexion->exec();


    db.setHostName(Wconnexion->ServeurIp());           // l'adresse IP du serveur mySQL
    db.setUserName(Wconnexion->Utilisateur());           // le nom de l'utilisateur
    db.setPassword(Wconnexion->Password());           // le mot de passe de l'utilisateur
    db.setDatabaseName(Wconnexion->Base());           // le nom de la base
    if(!db.open())
    {
        QMessageBox::information(this, "Erreur !!!", db.lastError().driverText());
    }
    else
    {

        lireTables();
        table = ui->comboBoxTable->currentText();
        modele->setTable(table);          // Sélection de la table
        modele->select();                 // Chargement des données dans le modèle
    }

}

void Dialog::lireTables()
{

       QStringList tables = db.tables(QSql::AllTables);  // les tables plus les vues

       for (int i=0; i<tables.size(); i++)
       {
           ui->comboBoxTable->addItem(tables[i]);
       }
}

// Slot pour ajouter un enregistrement à la table
void Dialog::on_pushButtonAjouter_clicked()
{
   int ligne = modele->rowCount();
    modele->insertRows(ligne,1);
}



void Dialog::on_comboBoxTable_currentIndexChanged(const QString &arg1)
{
    qDebug()<< arg1;
    modele->setTable(arg1);          // Sélection de la table
    modele->select();
}
