#ifndef EQUILIBREUSE_H
#define EQUILIBREUSE_H

#include <QMainWindow>
#include <QtCharts>

#include "experience.h"

namespace Ui {
class Equilibreuse;
}

class Equilibreuse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Equilibreuse(QWidget *parent = 0);
    ~Equilibreuse();

private slots:
    void on_actionOuvrir_triggered();
    void on_actionAffichage_en_Newton_toggled(bool arg1);
    void on_actionAffichage_en_brutes_toggled(bool arg1);

    void on_actionPrise_en_compte_de_l_origine_toggled(bool arg1);

private:
    Ui::Equilibreuse *ui;
    QChart *FabriquerCourbes();
    QChartView  *chartView;
    QHBoxLayout *horizontalLayout;
    QFileInfo   *fichierInfo;

    Experience data;

    int origine;
    bool newton;
    bool decalage;
    bool filtre;
    bool brutes;

    float map(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif // EQUILIBREUSE_H
