#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QStandardItemModel>
#define NBLIGNE 8
#define NBCOLONNE 4
#include "delegate.h"

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
    void on_pushButtonSelection_clicked();
    void on_AjouterColonne_clicked();

private:
    Ui::Dialog *ui;
    QStandardItemModel *modele;
    Delegate *monDelegue;

};

#endif // DIALOG_H
