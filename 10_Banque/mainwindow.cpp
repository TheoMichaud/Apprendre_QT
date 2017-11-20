#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Wconnexion = new Connexion(this);
    this->modele = new QSqlTableModel(this);
    // definie la stratégie de modification
    this->modele->setEditStrategy(QSqlTableModel::OnRowChange);
    // association du modèle à la vue
    ui->tableView->setModel(modele);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slot pour l'ouverture d'une connexion à
// un serveur de base de données

void MainWindow::on_actionConnexion_triggered()
{
    modele->clear();
    // efface la liste des tables
    ui->comboBoxTable->clear();

    // lance la fenêtre connexion
    Wconnexion->exec();
    QStringList *listeBases = new QStringList();
    listeBases = Wconnexion->ObtenirListeBases();
    ui->comboBoxBases->clear();
    for (int i=0; i<listeBases->size(); i++)
    {
        ui->comboBoxBases->addItem(listeBases->at(i));  // chaque nom de table est affecté a un QcomboBox
    }
    lireTables();
}

// Fonction pour lire les tables présentes dans une base de données
// et compléter le comboxTable
void MainWindow::lireTables()
{

    statusBar()->showMessage("Base ouverte : " + Wconnexion->ObtenirDb().databaseName() + " sur le serveur : " + Wconnexion->ObtenirDb().hostName());
    QStringList tables = Wconnexion->ObtenirDb().tables(QSql::AllTables);  // AllTables les tables plus les vues
    ui->comboBoxTable->clear();
    for (int i=0; i<tables.size(); i++)
    {
        ui->comboBoxTable->addItem(tables[i]);  // chaque nom de table est affecté a un QcomboBox
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



// Action quitter



void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

//Changement de base
void MainWindow::on_comboBoxBases_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase db = Wconnexion->ObtenirDb();
    db.setDatabaseName(ui->comboBoxBases->currentText());
    if(!db.open())
    {
        QErrorMessage *erreur = new QErrorMessage(this);
        erreur->showMessage(db.lastError().driverText());
    }
    lireTables();
}
