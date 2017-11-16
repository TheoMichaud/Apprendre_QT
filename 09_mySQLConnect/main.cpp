#include <QCoreApplication>
#include <QtSql>

#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // création d'une connexion
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("172.18.58.5");     // l'adresse IP du serveur mySQL
    db.setUserName("snir");    // le nom de l'utilisateur
    db.setPassword("snir");         // le mot de passe de l'utilisateur
    db.setDatabaseName("snirBanque1");           // le nom de la base

    if(db.open())
    {
        qDebug() << "Connected ... ";

        // Création d'une requète pour lire la table people
        QSqlQuery maRequete;
        if (maRequete.exec("SELECT * FROM `client`"))
        {
            // affichage tant qu'il y a des lignes
            while(maRequete.next())
            {
                QVariant id = maRequete.value(0);  // 0 première colonne
                QVariant nom = maRequete.value("nom");
                QVariant prenom = maRequete.value("prenom");
                QVariant ville = maRequete.value("ville");

                qDebug() << id.toInt()
                         << nom.toString()
                         << prenom.toString()
                         << ville.toString();
            }
        }
        else
        {
            qDebug() << "Erreur : " << db.lastError();
        }

        // Création d'une requète pour insérer un enregistrement

        QString insRequete = "INSERT INTO `snirBanque`.`client` ( `nom`, `prenom`, `ville` ) VALUES ( :prenom , :nom, :ville )";
        maRequete.prepare(insRequete);
        maRequete.bindValue(":prenom", "Philippe");
        maRequete.bindValue(":nom", "SIMIER");
        maRequete.bindValue(":ville", "Le Mans");

        if (maRequete.exec())
        {
            qDebug() << "Enregistrement insere ...";
        }

    }
    else
    {
        qDebug() << "Erreur : " << db.lastError();
    }


    qDebug() << "Fermeture ...";
    db.close();
    return a.exec();
}
