#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = 0);
    ~Connexion();
    // les getteurs
     QString ObtenirIpServeur();
     QString ObtenirBase();
     QString ObtenirUtilisateur();
     QString ObtenirPassword();
     QSqlDatabase ObtenirDb();




private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::Connexion *ui;

    QString serveurIp;
    QString base;
    QString utilisateur;
    QString password;
    QSqlDatabase   db;
    void lireBases();
};

#endif // CONNEXION_H
