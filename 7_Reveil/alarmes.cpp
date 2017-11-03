#include "alarmes.h"
#include "ui_alarmes.h"

Alarmes::Alarmes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarmes)
{
    ui->setupUi(this);
}

Alarmes::~Alarmes()
{
    delete ui;
}

void Alarmes::on_pushButton_clicked()
{

   emit reglerAlarme(ui->timeEdit->time());
   this->close();
}
