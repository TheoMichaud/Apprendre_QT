#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    // création d'un slot Ouvrir

    void Ouvrir();

    // création de slot en utilisant la nomenclature spécifique
    // le nom du slot commence par on_
    // vient ensuite le nom de l'émetteur
    // puis pour finir le nom de l'action
    // cette notation relie automatiquement un émetteur et un slot

    void on_Autre_chose_triggered();
    void on_Autre_chose_encore_triggered();
    void on_actionQuitter_triggered();
    void on_actionInformation_triggered();
    void on_actionPolice_triggered();
    void on_actionCouleur_triggered();

    void on_actionEnregistrer_triggered();

private:
    Ui::MainWindow *ui;
    QString contenuFichier;
    QString nomFichier;

};

#endif // MAINWINDOW_H
