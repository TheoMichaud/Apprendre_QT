#include "assitantreseau.h"
#include "ui_assitantreseau.h"

AssitantReseau::AssitantReseau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssitantReseau)
{
    ui->setupUi(this);
    // intanciation d'un nouveau Qprocess
    process = new QProcess(this);

    // Connexion du Qprocess au Slot onDataRead
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(onDataRead()));

}

AssitantReseau::~AssitantReseau(){
    delete ui;
}


void AssitantReseau::on_actionarp_a_triggered(){
   QStringList arguments;
   arguments << "-a";
   process->start("arp", arguments);
}

void AssitantReseau::onDataRead(){
    QByteArray sortie;
    sortie = process->readAllStandardOutput();
    QString str;
    str = QString::fromLatin1(sortie);
    ui->textEdit->setText(str);
}

void AssitantReseau::on_actionarp_d_triggered(){
    QStringList arguments;
    arguments << "-d";
    process->start("arp", arguments);
}




void AssitantReseau::on_actionroute_print_triggered()
{
    QStringList arguments;
    arguments << "print";
    process->start("route",arguments);
}

void AssitantReseau::on_actionver_triggered()
{
    QStringList arguments;
    process->start("ver", arguments);
}
