#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>

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
     QString ServeurIp();
     QString Base();
     QString Utilisateur();
     QString Password();



private slots:
    void on_buttonBox_accepted();

private:
    Ui::Connexion *ui;
    QString serveurIp;
    QString base;
    QString utilisateur;
    QString password;
};

#endif // CONNEXION_H
