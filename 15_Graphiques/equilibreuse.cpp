#include "equilibreuse.h"
#include "ui_equilibreuse.h"

#include <QDebug>

Equilibreuse::Equilibreuse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Equilibreuse),
    chartView(NULL),
    newton(false),
    decalage(false),
    filtre(false),
    brutes(true)
{
    //initialisation de l'IHM
    ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(ui->centralWidget);
}

Equilibreuse::~Equilibreuse()
{
    delete ui;
}

void Equilibreuse::on_actionOuvrir_triggered()
{
    QString leFichier;
    QString chemin = "/home/USERS/PROFS/" + QDir::home().dirName() +"/";
    chemin += QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";
    leFichier = QFileDialog::getOpenFileName(this, tr("Charger un fichier équilibrage"), chemin, tr("Fichiers (*.mbr)"));
    if(leFichier != NULL)
    {
        if (!leFichier.isEmpty())
        {
            data.LireMesuresBrutes(leFichier);

            if(chartView != NULL)
                delete chartView;

            chartView = new QChartView(FabriquerCourbes());
            horizontalLayout->addWidget(chartView);

        }
    }
}

QChart * Equilibreuse::FabriquerCourbes()
{
    QChart *chart = new QChart();
    chart->setTitle("Restitution des Courbes");
    QLineSeries *courbeA = new QLineSeries(chart);
    QLineSeries *courbeO = new QLineSeries(chart);

    int indiceA = 0 ;
    int indiceO = data.nbEchantillons/2;
    if(decalage)
    {
        indiceA += data.decalageOrigine;
        indiceO += data.decalageOrigine;
    }

    int fin = data.nbEchantillons / 4;
    if(brutes)
        fin = data.nbEchantillons / 2;

    double tensionCalibrage = 1;
    if(newton)
        tensionCalibrage = 9.80665; // 5kg = 5V et 1Kg = 9,80665 N

    for(int i = 0 ; i < fin ; i++)
    {
        if(brutes)
        {
            courbeA->append(i,data.mesuresBrutes[indiceA++]);
            courbeO->append(i,data.mesuresBrutes[indiceO++]);
        }
        else
        {
            float x  = map(i, 0, 1000, 0, 360);
            float FA = map(data.mesuresBrutes[indiceA++], 0, 1, 0, tensionCalibrage);
            float FO = map(data.mesuresBrutes[indiceO++], 0, 1, 0, tensionCalibrage);
            courbeA->append(x , FA);
            courbeO->append(x , FO);
        }
    }

    courbeA->setName("Courbe A");
    courbeA->setColor(Qt::blue);
    courbeO->setName("Courbe O");
    courbeO->setColor(Qt::red);

    chart->addSeries(courbeA);
    chart->addSeries(courbeO);

    chart->createDefaultAxes();

    QValueAxis *axisX = (QValueAxis *)chart->axisX();
    axisX->setTickCount(5);
    axisX->setMinorTickCount(2);

    if(!brutes)
        axisX->setMax(360);

    axisX->setLabelFormat("%d");
    axisX->setTitleText("Position angulaire en °");

    QValueAxis *axisY = (QValueAxis *)chart->axisY();
    axisY->applyNiceNumbers();
    axisY->setMinorTickCount(10);

    if(newton)
        axisY->setTitleText("Effort en Newtons");
    else
        axisY->setTitleText("Tension en Volts");

    return chart;
}

float Equilibreuse::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}


void Equilibreuse::on_actionAffichage_en_brutes_toggled(bool arg1)
{
    QList<QAction *> lesActions = ui->menuOptions->actions();
    foreach (QAction *action, lesActions)
    {
        if(action->text() != "Affichage mesures brutes")
        {
            action->setEnabled(!arg1);
            if(arg1)
                action->setChecked(false);
        }
    }
    brutes = arg1;
    if(chartView != NULL)
    {
        delete chartView;
    }
    chartView = new QChartView(FabriquerCourbes());
    horizontalLayout->addWidget(chartView);
}

void Equilibreuse::on_actionAffichage_en_Newton_toggled(bool arg1)
{
    newton = arg1;

    if(chartView != NULL)
    {
        delete chartView;
    }
    chartView = new QChartView(FabriquerCourbes());
    horizontalLayout->addWidget(chartView);
}

void Equilibreuse::on_actionPrise_en_compte_de_l_origine_toggled(bool arg1)
{
    decalage = arg1;
    if(chartView != NULL)
    {
        delete chartView;
    }
    chartView = new QChartView(FabriquerCourbes());
    horizontalLayout->addWidget(chartView);
}
