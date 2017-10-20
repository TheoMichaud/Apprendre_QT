#include "widgetreutilisable.h"
#include "ui_widgetreutilisable.h"

WidgetReutilisable::WidgetReutilisable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetReutilisable)
{
    ui->setupUi(this);
}

WidgetReutilisable::~WidgetReutilisable()
{
    delete ui;
}
