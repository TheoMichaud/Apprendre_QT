#include "equilibreuse.h"
#include "ui_equilibreuse.h"

#include <QDebug>

Equilibreuse::Equilibreuse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Equilibreuse),
    chartView(NULL),
    newton(false),
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

    QString leFichier = QFileDialog::getOpenFileName(this, "Charger un fichier de données", QDir::homePath(), "Fichiers (*.mbr)");
    fichierInfo = new QFileInfo(leFichier);
    if(leFichier != NULL)
    {
        if (!leFichier.isEmpty())
        {
            statusBar()->showMessage("Fichier ouvert : " + fichierInfo->baseName() );
            setWindowTitle(fichierInfo->baseName() + " - Viewer");

            data.LireMesuresBrutes(leFichier);

            if(chartView != NULL)
                delete chartView;

            chartView = new QChartView(FabriquerCourbes());
            chartView->setRenderHint(QPainter::Antialiasing, true);
            horizontalLayout->addWidget(chartView);

        }
    }
}


QChart * Equilibreuse::FabriquerCourbes()
{
    QChart *chart = new QChart();
    chart->setTitle("Forces appliquées sur les paliers");
    QLineSeries *courbeA = new QLineSeries(chart);
    QLineSeries *courbeO = new QLineSeries(chart);


    int indiceA = 0 ;
    int indiceO = data.nbEchantillons/2;
    float decalageDegre = data.decalageOrigine * 360/1000;

    double Calibrage = 1;     // 1V correspond à 1V
    if(newton)
        Calibrage = 9.80665;  // 1V correspond à 9.80665 N

    for(int i = 0 ; i < data.nbEchantillons / 2 ; i++)
    {
        if(brutes)
        {

            float degree  = map(i, 0, 1000, 0 - decalageDegre, 360 -decalageDegre);
            courbeA->append(degree, data.mesuresBrutes[indiceA++]);
            courbeO->append(degree, data.mesuresBrutes[indiceO++]);
        }
        else
        {
            float degree  = map(i, 0, 1000, 0 - decalageDegre, 360 -decalageDegre);
            float FA = map(data.mesuresBrutes[indiceA++], 0, 1, 0, Calibrage);
            float FO = map(data.mesuresBrutes[indiceO++], 0, 1, 0, Calibrage);

            courbeA->append(degree , FA);
            courbeO->append(degree , FO);
        }
    }

    courbeA->setName("Force en A");
    courbeA->setColor(Qt::blue);
    courbeO->setName("Force en O");
    courbeO->setColor(Qt::red);

    chart->addSeries(courbeA);
    chart->addSeries(courbeO);

    chart->createDefaultAxes();


    QValueAxis *axisX = (QValueAxis *)chart->axisX();
    axisX->setTickCount(5);
    axisX->setMinorTickCount(2);


    axisX->setLabelFormat("%d");
    axisX->setTitleText("Position angulaire en °");

    QValueAxis *axisY = (QValueAxis *)chart->axisY();
    axisY->applyNiceNumbers();
    axisY->setMinorTickCount(10);

    /* Customize axis colors
        QPen axisPen(QRgb(0xd18952));
        axisPen.setWidth(2);
        axisX->setLinePen(axisPen);
        axisY->setLinePen(axisPen);
    */

    if(newton)
        axisY->setTitleText("Force en Newton");
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
    brutes = arg1;
    if(chartView != NULL)
    {
        delete chartView;
    }
    chartView = new QChartView(FabriquerCourbes());
    chartView->setRenderHint(QPainter::Antialiasing, true);
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
    chartView->setRenderHint(QPainter::Antialiasing, true);
    horizontalLayout->addWidget(chartView);
}

void Equilibreuse::on_actionPrise_en_compte_de_l_origine_toggled(bool arg1)
{

}
