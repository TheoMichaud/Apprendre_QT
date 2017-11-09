#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtSql>
#include <QtCore>
#include <QDebug>
#include <QMessageBox>

#include <QInputDialog>

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
    void on_pushButtonAjouter_clicked();





    void on_comboBoxTable_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    connexion *Wconnexion;
    QSqlTableModel *modele;


    QSqlDatabase db;
    QString table;

    void ouvrirBase();
    void lireTables();
};

#endif // DIALOG_H
