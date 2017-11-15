#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "connexion.h"
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnexion_triggered();

    void on_comboBoxTable_currentIndexChanged(const QString &arg1);

    void on_pushButtonInserer_clicked();

    void on_pushButtonSupprimer_clicked();

private:
    Ui::MainWindow *ui;
    Connexion      *Wconnexion;
    QSqlDatabase   db;
    QSqlTableModel *modele;

    void lireBases();
    void ouvrirBase();
    void lireTables();
};

#endif // MAINWINDOW_H
