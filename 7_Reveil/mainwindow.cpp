#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dessinerCadran();
    tournerAiguilles();
    //sonnerieAlarme = new QSound(":/sons/sonnerie.wav");
    WAlarme = new Alarmes(this);
    if(!connect(WAlarme, SIGNAL(reglerAlarme(QTime)), this, SLOT(setAlarme(QTime))) )
        qDebug() << "Erreur connexion Alarme";

    tictac = new QTimer;
    connect(tictac,SIGNAL(timeout()),this,SLOT(tournerAiguilles()));
    tictac->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dessinerCadran()
{
    // Création d'une Scene
    // La scène sert de conteneur pour les éléments graphiques
    scene =  new QGraphicsScene;
    scene->setSceneRect(-300, -300, 600, 600);

    // Création des éléments graphiques
    // La classe QGraphicsItem est la classe de base pour les éléments graphiques
    // dans une scène.

    QPen pen5(Qt::lightGray, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen1(Qt::lightGray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QGraphicsItem *cadran[2];
    cadran[0] = scene->addEllipse(QRect(-250,-250,500,500),pen5);
    cadran[1] = scene->addEllipse(QRect(-240,-240,480,480),pen5);
    cadran[0]->setZValue(5);
    cadran[1]->setZValue(5);

    // les repères des minutes tous les 6 degrees

    QGraphicsItem  *reperes[60];
    for (int i=0; i<60; i++){
        if(i%5 == 0)    // les repères des cinq minutes sont plus gros
            reperes[i] = scene->addLine(200, 0, 225, 0, pen5);
        else
            reperes[i] = scene->addLine(200, 0, 220, 0, pen1);
        reperes[i]->setRotation(i*6);
    }


    // Les nombres 12 3 6 9

    QFont maFont("Times", 24, QFont::Bold);
    QGraphicsItem *item[5];
    item[0] = scene->addText("12", maFont);
    item[0]->setPos(-28,-200);
    item[1] = scene->addText("3", maFont);
    item[1]->setPos(160, -28);
    item[2] = scene->addText("6", maFont);
    item[2]->setPos(-15, 145);
    item[3] = scene->addText("9", maFont);
    item[3]->setPos(-185, -28);

    QPixmap monPixmap;
    monPixmap.load(":/images/logo_touchard2.png");
    item[4] = scene->addPixmap(monPixmap);
    item[4]->setPos(-40, 60);
    item[4]->setFlag(QGraphicsItem::ItemIsMovable);

    QPen penAxeCentral(Qt::red, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brushAxeCentral(Qt::red);
    QGraphicsItem *axe = scene->addEllipse(QRect(-10,-10,20,20), penAxeCentral, brushAxeCentral);
    axe->setZValue(4);

    QPen penTroteuse(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penGrandeAiguille(Qt::darkMagenta, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen penPetiteAiguille(Qt::darkMagenta, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    grandeAiguille = scene->addLine(QLine(0, 0, 0, -200), penGrandeAiguille);
    petiteAiguille = scene->addLine(QLine(0, 0, 0, -100), penPetiteAiguille);
    troteuse = scene->addLine(QLine(0, 25, 0, -210), penTroteuse);

    troteuse->setZValue(3);
    grandeAiguille->setZValue(2);
    petiteAiguille->setZValue(1);

    // QGraphicsView fournit la vue "widget" qui permet de visualiser
    // le contenu de la scène.

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
}

void MainWindow::tournerAiguilles()
{
    QTime maintenant = QTime::currentTime();
    int h = maintenant.hour();
    int min = maintenant.minute();
    int sec = maintenant.second();
    statusBar()->showMessage(maintenant.toString("HH:mm:ss") +
                             " Alarme : " +
                             timeAlarme.toString("HH:mm:ss"));

    // Rotation de la troteuse :
    troteuse->resetTransform();
    troteuse->setRotation(6 * sec);

    // Rotation de la grande aiguille :
    grandeAiguille->resetTransform();
    grandeAiguille->setRotation((min * 6) + (0.1 * sec));

    // Rotation de la petite aiguille :
    petiteAiguille->resetTransform();
    petiteAiguille->setRotation((0.0083333333 * sec) + (0.5 * min) + (30 * h));

    if (maintenant.toString("HH:mm:ss") == timeAlarme.toString("HH:mm:ss")){
        //sonnerieAlarme->play();

    }
}

void MainWindow::setAlarme(const QTime &valeurAlarme)
{
    timeAlarme = valeurAlarme;
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionAlarme_triggered()
{
    WAlarme->show();
}
