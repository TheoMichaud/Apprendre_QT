#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QErrorMessage>
#include <QStringList>

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
    QSqlDatabase ObtenirDb();
    QStringList *ObtenirListeBases();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Connexion *ui;
    QSqlDatabase   db;
    QStringList *listeBases;
    void lireBases();
};

#endif // CONNEXION_H
