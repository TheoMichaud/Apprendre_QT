#include "serveurbanquewindow.h"
#include "ui_serveurbanquewindow.h"
#include "serveurbanque.h"

#include <QMessageBox>

ServeurBanqueWindow::ServeurBanqueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServeurBanqueWindow)
{
    ui->setupUi(this);

    leServeur = new ServeurBanque(this);
    leServeur->start();
}

ServeurBanqueWindow::~ServeurBanqueWindow()
{
    leServeur->stop();
    leServeur->deleteLater ();
    delete ui;
}



