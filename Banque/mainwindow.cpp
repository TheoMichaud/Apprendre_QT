#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    this->Wconnexion = new Connexion(this);
    this->modele = new QSqlTableModel(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnexion_triggered()
{
    ouvrirBase();
}

// Fonction pour lire les tables présentes dans la table et compléter le comboxTable
void MainWindow::lireTables()
{
    QStringList tables = db.tables(QSql::AllTables);  // AllTables les tables plus les vues

    for (int i=0; i<tables.size(); i++)
    {
        ui->comboBoxTable->addItem(tables[i]);  // chaque nom de table est affecté a un QcomboBox
    }
}

// Fonction pour ouvrir une base de données
void MainWindow::ouvrirBase()
{
    //  efface le modèle

    modele->clear();
    // efface la liste des tables
    ui->comboBoxTable->clear();

    // lance la fenêtre connexion
    Wconnexion->exec();


    db.setHostName(Wconnexion->ServeurIp() );         // l'adresse IP du serveur mySQL
    db.setUserName(Wconnexion->Utilisateur()  );      // le nom de l'utilisateur
    db.setPassword(Wconnexion->Password());           // le mot de passe de l'utilisateur
    //db.setDatabaseName(Wconnexion->Base());           // le nom de la base
    if(!db.open())
    {
        QMessageBox::information(this, "Erreur !!!", db.lastError().driverText());
    }
    else
    {
        QSqlQuery maRequete(db);
           maRequete.exec("SHOW DATABASES;");
        while (maRequete.next()) {
            QVariant base = maRequete.value(0);
            qDebug() << base;
        }
        lireTables();
        statusBar()->showMessage("Base ouverte : " + Wconnexion->Base() );
        modele->setTable(ui->comboBoxTable->currentText());    // Sélection de la table
        modele->select();                 // Chargement des données dans le modèle
        ui->tableView->resizeColumnsToContents();  // ajustement de la largeur des colonnes
        // association du modèle à la vue
        ui->tableView->setModel(modele);
        // definie la stratégie de modification
        modele->setEditStrategy(QSqlTableModel::OnRowChange);


    }

}


void MainWindow::on_comboBoxTable_currentIndexChanged(const QString &arg1)
{
    modele->setTable(arg1);          // Sélection de la nouvelle table
    modele->select();                // recharge le modèle avec les données
    ui->tableView->resizeColumnsToContents(); // ajustement de la largeur des colonnes
}

// Slot pour ajouter un enregistrement à la table
// nous appelons insertRows pour créer une nouvelle ligne (enregistrement) vide

void MainWindow::on_pushButtonInserer_clicked()
{
    modele->insertRows(0,1); // insert une ligne au début
}

// Slot pour supprimer un enregistrement
// nous appelons removeRow pour retirer une ligne du modèle
// removeRow reçoit le numéro de la ligne à supprimer

void MainWindow::on_pushButtonSupprimer_clicked()
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
