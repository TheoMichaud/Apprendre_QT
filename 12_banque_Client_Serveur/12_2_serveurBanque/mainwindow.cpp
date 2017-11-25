#include "mainwindow.h"
#include "ui_mainwindow.h"

BanqueMainWindow::BanqueMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    leServeur= new ServeurBanque();
    leServeur->Start();
}

BanqueMainWindow::~BanqueMainWindow()
{
    delete ui;
}
