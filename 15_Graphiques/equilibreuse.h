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
    void tooltip(QPointF point, bool state);
    void on_actionAffichage_en_Newton_toggled(bool arg1);
    void on_actionAffichage_en_degr_toggled(bool arg1);

private:
    Ui::Equilibreuse *ui;
    QChart *FabriquerCourbes();
    QChartView  *chartView;
    QHBoxLayout *horizontalLayout;
    QFileInfo   *fichierInfo;

    Experience data;

    int origine;
    bool newton;
    bool degre;
    QChart *graphiques;

    float map(float x, float in_min, float in_max, float out_min, float out_max);
    void afficherVueGraphique();
};

#endif // EQUILIBREUSE_H
