#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "info.h"
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connection du signal trigerred du menu actionOuvrir au slot Ouvrir
    connect(ui->actionOuvrir, SIGNAL(triggered(bool)),
            this, SLOT(Ouvrir()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Ouvrir()
{
    // La boîte de dialogue « Ouverture d'un fichier » est gérée par
    // getOpenFileName().
    // Sans paramètre particulier, la boîte de dialogue permet d'ouvrir
    // n'importe quel fichier.

    nomFichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", NULL, "Text files (*.txt)");



    QFile fichier(nomFichier);
    statusBar()->showMessage(nomFichier);

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        contenuFichier = fichier.readAll();
        fichier.close();
        ui->textLogActions->setText(contenuFichier);
        // désactive le bouton enregistrer
        ui->actionEnregistrer->setEnabled(false);

    }
    else qDebug() << "Impossible d'ouvrir le fichier !";
}

void MainWindow::on_Autre_chose_triggered()
{
    // message box warning
    QMessageBox::warning(this, "Warning", "Vous venez de cliquer sur Autre chose");
    ui->textLogActions->append("Clique sur <b>\"Autre chose\"</b> dans un sous menu de Test");
}

void MainWindow::on_Autre_chose_encore_triggered()
{
    ui->textLogActions->append("Clique sur <b>\"Autre chose encore\"</b> dans un sous menu de Test");
}

void MainWindow::on_actionQuitter_triggered()
{
    // message box question (demande de confirmation)
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this, "Quitter", "Confirmez-vous l'action de <b>Quitter</b> ?",QMessageBox::Yes|QMessageBox::No );
    if (reponse == QMessageBox::Yes) {
        qDebug() << "Yes a été cliqué";
        this->close();
    } else {
        ui->textLogActions->append("L'action sur <b>\"Quitter\"</b> n'a pas été confirmée");
        qDebug() << "Yes n'a pas été cliqué";
    }

}

//

void MainWindow::on_actionInformation_triggered()
{
    qDebug() << "Saisir info a été cliqué";

    QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?");
    ui->textLogActions->append("Bienvenue <b>" + pseudo + "</b>");

}

void MainWindow::on_actionPolice_triggered()
{
    qDebug() << "Choisir une police a été cliqué";
    bool ok = false;

    QFont police = QFontDialog::getFont(&ok, ui->textLogActions->font(), this, "Choisissez une police");

    if (ok){
        ui->textLogActions->setFont(police);
    }
}

void MainWindow::on_actionCouleur_triggered()
{
    qDebug() << "Choisir une couleur a été cliqué";
    QColor couleur = QColorDialog::getColor(Qt::yellow, this );
    if( couleur.isValid() )
    {
        qDebug() << "Couleur sélectionnée : " << couleur.name();

        ui->textLogActions->setStyleSheet(QString("background: %1").arg(couleur.name()));
    }
}



void MainWindow::on_actionEnregistrer_triggered()
{
    qDebug() << "L'action Enregistrer a été cliqué";
    QFile fichier(nomFichier);
    // Ouverture d'un fichier en lecture seule
    if (fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        // création d'un flux
        QTextStream flux(&fichier);
        contenuFichier = ui->textLogActions->toPlainText();
        flux << contenuFichier;
        fichier.close();
        QMessageBox::information(this, "Info", "Le fichier : <b>" + nomFichier + "</b> a été Enregistré");
        // désactive le bouton enregistrer
        ui->actionEnregistrer->setEnabled(false);
    }
    else{

        // Message box information
        // La méthode statique information()permet d'ouvrir une boîte de dialogue
        // constituée d'une icône « information ».

        QMessageBox::information(this, "Info", "erreur lors de l'ouverture du fichier");
    }
}

void MainWindow::on_textLogActions_textChanged()
{
    // active le bouton enregistrer
    ui->actionEnregistrer->setEnabled(true);
}

void MainWindow::on_actionA_propos_triggered()
{
    Info fenetre;

    fenetre.exec();
    qDebug() << " info a été cliqué";
}
