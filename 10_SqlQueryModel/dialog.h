#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtSql>
#include <QtCore>
#include <QDebug>
#include <QMessageBox>
#include "connexion.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void connecter(QString serveurIp, QString base, QString utilisateur, QString password);


private:
    Ui::Dialog *ui;
    connexion *Wconnexion;
    QSqlTableModel *modele;


    QSqlDatabase db;
    QString hostName;
    QString userName;
    QString password;
    QString base;
};

#endif // DIALOG_H
