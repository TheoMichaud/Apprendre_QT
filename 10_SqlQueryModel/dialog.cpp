#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Wconnexion = new connexion();

    connect(Wconnexion, SIGNAL(connecter(QString,QString,QString,QString)),this, SLOT(connecter(QString,QString,QString,QString)));

    Wconnexion->exec();
    qDebug() << hostName << " " << userName;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);     // l'adresse IP du serveur mySQL
    db.setUserName(userName);    // le nom de l'utilisateur
    db.setPassword(password);         // le mot de passe de l'utilisateur
    db.setDatabaseName(base);           // le nom de la base

    if(db.open())
    {
    this->modele = new QSqlTableModel(this);
    modele->setTable("comptes");          // Sélection de la table
    modele->select();                    // remplissage du modèle avec le contenu de la table
    modele->setEditStrategy(QSqlTableModel::OnRowChange); // definie la stratégie de modification

    ui->tableView->setModel(modele);     // association du modèle à la vue
    //ui->tableView->hideColumn(0);        // masquer la première colonne (les id)
    }
    else
    {

        QMessageBox::information(this, "erreur", db.lastError().driverText());

    }

}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << "Connexion";
    Wconnexion->exec();


}

void Dialog::connecter(QString serveurIp, QString base, QString utilisateur, QString password)
{
    Dialog::hostName =  serveurIp;
    Dialog::userName = utilisateur;
    Dialog::password = password;
    Dialog::base = base;
}
