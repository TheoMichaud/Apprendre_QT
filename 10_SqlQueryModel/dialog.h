#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtSql>
#include <QtCore>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSqlTableModel *modele;
    QSqlDatabase db;
};

#endif // DIALOG_H
