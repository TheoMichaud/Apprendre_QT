#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    lesAlveolesLibres(new Alveoleslibres(4,4))
{
    ui->setupUi(this);
    AfficherAlveolesLibres();
    ui->pushButtonLiberer->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
    delete lesAlveolesLibres;
}

void Widget::on_pushButtonReserver_clicked()
{
    int rangee;
    int colonne;
    QString texte;

    if(lesAlveolesLibres->Reserver(rangee,colonne))
    {
        texte = "Alveole (" + QString::number(rangee) ;
        texte += "," + QString::number(colonne) + ")";
        ui->listWidgetOccupees->addItem(texte);
    }
    AfficherAlveolesLibres();
    if(lesAlveolesLibres->empty())
        ui->pushButtonReserver->setEnabled(false);
}

void Widget::on_pushButtonLiberer_clicked()
{
    QListWidgetItem *item = ui->listWidgetOccupees->currentItem();
    QString texte = item->text();
    delete item;
    texte = texte.mid(9);
    texte.chop(1);
    QStringList coord = texte.split(',');
    lesAlveolesLibres->Liberer(coord[0].toInt(),coord[1].toInt());

    ui->listWidgetOccupees->setCurrentRow(-1); // pour ne plus avoir de sélection
    ui->pushButtonLiberer->setEnabled(false);

    AfficherAlveolesLibres();
    if(lesAlveolesLibres->size()!=0)
        ui->pushButtonReserver->setEnabled(true);
}



void Widget::on_listWidgetOccupees_currentRowChanged()
{
    ui->pushButtonLiberer->setEnabled(true);
}

void Widget::AfficherAlveolesLibres()
{
    ui->listWidgetAlveolesLibres->clear();

    for(int indice=(lesAlveolesLibres->size()-1)  ; indice >-1 ; indice--)
    {
        ui->listWidgetAlveolesLibres->addItem(QString::number(lesAlveolesLibres->at(indice)));
    }
}
