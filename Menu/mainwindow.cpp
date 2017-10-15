#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QInputDialog>
#include <QFontDialog>

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
    // Message box information
    // La méthode statique information()permet d'ouvrir une boîte de dialogue
    // constituée d'une icône « information ».

    QMessageBox::information(this, "Info", "Vous venez de cliquer sur <b>Ouvrir</b> dans le menu Fichier");
    ui->textLogActions->append("Clique sur <b>\"Ouvrir\"</b> dans le menu Fichier");
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
