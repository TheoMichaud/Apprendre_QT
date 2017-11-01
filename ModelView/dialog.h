#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

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
    void on_pushButtonAjouter_clicked();
    void on_pushButtonInserer_clicked();
    void on_pushButtonEffacer_clicked();
    
    void on_pushButtonAfficher_clicked();

private:
    Ui::Dialog *ui;
    
    QStringListModel *modele;
 
};

#endif // DIALOG_H
