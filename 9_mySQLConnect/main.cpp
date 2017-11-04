#include <QCoreApplication>
#include <QtSql>

#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // création d'une connexion
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.10");     // l'adresse IP du serveur mySQL
    db.setUserName("QtUtilisateur");    // le nom de l'utilisateur
    db.setPassword("password");         // le mot de passe de l'utilisateur
    db.setDatabaseName("pi");           // le nom de la base

    if(db.open())
    {
        qDebug() << "Connected ... ";

        // Création d'une requète pour lire la table people
        QSqlQuery maRequete;
        if (maRequete.exec("SELECT * FROM `people`"))
        {
            // affichage tant qu'il y a des lignes
            while(maRequete.next())
            {
                QVariant id = maRequete.value(0);  // 0 première colonne
                QVariant firstName = maRequete.value("FirstName");
                QVariant lastName = maRequete.value("LastName");

                qDebug() << id.toInt() << firstName.toString() <<  lastName.toString() ;
            }
        }
        else
        {
            qDebug() << "Erreur : " << db.lastError();
        }

        // Création d'une requète pour insérer un enregistrement

        QString insRequete = "INSERT INTO `pi`.`people` (`id`, `FirstName`, `LastName`) VALUES (NULL, :prenom , :nom )";
        maRequete.prepare(insRequete);
        maRequete.bindValue(":prenom", "Albert");
        maRequete.bindValue(":nom", "Einstein");
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
