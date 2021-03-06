#include "equilibreuse.h"
#include "ui_equilibreuse.h"

#include <QDebug>

Equilibreuse::Equilibreuse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Equilibreuse),
    chartView(NULL),
    newton(true),
    degre(true),
    graphiques(NULL)
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
            afficherVueGraphique();

        }
    }
}


QChart * Equilibreuse::FabriquerCourbes()
{
    QChart *chart = new QChart();
    chart->setTitle("Forces appliquées sur les paliers");
    QLineSeries *courbeA = new QLineSeries(chart);
    QLineSeries *courbeO = new QLineSeries(chart);

    QLineSeries *axeX0 = new QLineSeries(chart);
    QLineSeries *axeY0 = new QLineSeries(chart);

    axeX0->setColor(QRgb(Qt::black));
    axeY0->setColor(QRgb(Qt::black));




    int indiceA = 0 ;
    int indiceO = data.nbEchantillons/2;
    float decalageDegre = data.decalageOrigine * 360/1000;

    double Calibrage = 1;     // 1V correspond à 1V
    if(newton)
        Calibrage = 9.80665;  // 1V correspond à 9.80665 N

    int i;
    float x;
    for(i = 0 ; i < data.nbEchantillons / 2 ; i++)
    {
        if(degre)
            x  = map(i, 0, 1000, 0 - decalageDegre, 360 -decalageDegre);
        else
            x = i;

        if (i==0) axeX0->append(QPoint(x,0));
        if(!newton)
        {
            courbeA->append(x, data.mesuresBrutes[indiceA++]);
            courbeO->append(x, data.mesuresBrutes[indiceO++]);
        }
        else
        {

            float FA = map(data.mesuresBrutes[indiceA++], 0, 1, 0, Calibrage);
            float FO = map(data.mesuresBrutes[indiceO++], 0, 1, 0, Calibrage);

            courbeA->append(x , FA);
            courbeO->append(x , FO);
        }
    }

    axeX0->append(QPoint(x,0));


    courbeA->setName("Force en A");
    courbeA->setColor(Qt::blue);
    courbeO->setName("Force en O");
    courbeO->setColor(Qt::red);

    chart->addSeries(axeX0);
    chart->addSeries(courbeO);
    chart->addSeries(courbeA);



    chart->createDefaultAxes();
    chart->setAcceptHoverEvents(true);
    chart->legend()->hide();  // Cache les légendes

    QValueAxis *axisX = (QValueAxis *)chart->axisX();
    axisX->setTickCount(5);
    axisX->setMinorTickCount(2);


    axisX->setLabelFormat("%d");
    axisX->setTitleText("Position angulaire en °");

    QValueAxis *axisY = (QValueAxis *)chart->axisY();
    axisY->setMinorTickCount(10);

    axeY0->append(QPoint(0.0,axisY->max()));
    axeY0->append(QPoint(0.0,axisY->min()));
    chart->addSeries(axeY0);
    chart->createDefaultAxes();

    if(newton)
        axisY->setTitleText("Force en Newton");
    else
        axisY->setTitleText("Tension en Volts");

    if(!connect(courbeA, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool))))
        qDebug() << "Erreur connexion hovered courbeA";
    if(!connect(courbeO, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool))))
        qDebug() << "Erreur connexion hovered courbeO";
    return chart;
}

// Fonction map
// Fonction  pour effectuer des changements d'échelle.
// Avec ou sans décalage.
// exemple y= map(500, 0, 1000, 0, 360)
// donne 180
float Equilibreuse::map(float x, float Xa, float Xb, float Ya, float Yb)
{
    return (x - Xa) * (Yb - Ya) / (Xb - Xa) + Ya;

}

void Equilibreuse::afficherVueGraphique()
{
    if(graphiques != NULL) delete graphiques;
    graphiques = FabriquerCourbes();

    if(chartView != NULL) delete chartView;
    chartView = new QChartView(graphiques);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    horizontalLayout->addWidget(chartView);
}


void Equilibreuse::tooltip(QPointF point, bool state)
{
    QLineSeries *courbe = (QLineSeries *)sender();

    if (state)
        statusBar()->showMessage(" Téta : " + QString::number( point.x()) + "° " + courbe->name() +" : " + QString::number( point.y()) + "N");
    else
        statusBar()->showMessage("");
}



void Equilibreuse::on_actionAffichage_en_Newton_toggled(bool arg1)
{
    newton = arg1;
    afficherVueGraphique();
}



void Equilibreuse::on_actionAffichage_en_degr_toggled(bool arg1)
{
    degre = arg1;
    afficherVueGraphique();
}
