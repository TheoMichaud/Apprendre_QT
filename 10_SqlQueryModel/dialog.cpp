#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");

    Wconnexion = new connexion(this);

    this->modele = new QSqlTableModel(this);
    modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification

    ui->tableView->setModel(modele);  // association du modèle à la vue


    ouvrirBase();
}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
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
        ui->tableView->resizeColumnsToContents();  // ajustement de la largeur des colonnes
        //ui->tableView->setColumnHidden(0,true);    // la première colonne est cachée
    }

}

// la methode tables de QSqlDatabase retourne la liste des tables
void Dialog::lireTables()
{

    QStringList tables = db.tables(QSql::AllTables);  // AllTables les tables plus les vues

    for (int i=0; i<tables.size(); i++)
    {
        ui->comboBoxTable->addItem(tables[i]);  // chaque nom de table est affecté a un QcomboBox
    }
}

// Slot pour ajouter un enregistrement à la table
// nous appelons insertRows pour créer une nouvelle ligne (enregistrement) vide
void Dialog::on_pushButtonAjouter_clicked()
{
    int ligne = modele->rowCount();
    modele->insertRows(0,1);   // insert une ligne au début

}


// Rechargement des données quand une nouvelle table est sélectionnée
void Dialog::on_comboBoxTable_currentIndexChanged(const QString &arg1)
{

    modele->setTable(arg1);          // Sélection de la nouvelle table
    modele->select();                // recharge le modèle avec les données
    ui->tableView->resizeColumnsToContents();  // ajustement de la largeur des colonnes
    //ui->tableView->setColumnHidden(0,true);    // la première colonne est cachée
}

// Effacer un enregistrement
// nous appelons removeRow pour retirer une ligne du modèle
// removeRow reçoit le numéro de la ligne à supprimer
void Dialog::on_pushButton_2_clicked()
{
    int ligne = ui->tableView->selectionModel()->currentIndex().row(); // on récupère le n° de la ligne

    // message box question (demande de confirmation avant de supprimer la ligne)
    QMessageBox::StandardButton reponse;

    QString message = "Confirmer vous la <b>suppression</b><br> de l'enregistrement ligne : " + QString::number(ligne + 1);
    reponse = QMessageBox::question(this, "Supprimer", message, QMessageBox::Yes|QMessageBox::No );
    if (reponse == QMessageBox::Yes){
        modele->removeRow(ligne);   // retire la ligne du modèle
        modele->select();           // recharge le modèle
    }
}
