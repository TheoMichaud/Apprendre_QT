#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(QStringList() << "Description" );

    addRoot("Bdd1");
    addRoot("Bdd2");
    addRoot("Bdd3");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, "description");
    //itm->setText(1, "type");
    ui->treeWidget->currentItem()->addChild(itm);

}

void Dialog::addRoot(QString name)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name);
    //itm->setText(1, description);
//    ui->treeWidget->addTopLevelItem(itm);
    addChild(itm, "Compte");
    addChild(itm, "Client");
}

void Dialog::addChild(QTreeWidgetItem *parent, QString name)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    //itm->setText(1, description);
    parent->addChild(itm);
}
