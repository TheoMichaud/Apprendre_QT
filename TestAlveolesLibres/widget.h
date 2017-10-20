#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "alveoleslibres.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonReserver_clicked();

    void on_pushButtonLiberer_clicked();

    void on_listWidgetOccupees_currentRowChanged();

private:
    Ui::Widget *ui;
    Alveoleslibres *lesAlveolesLibres;

    void AfficherAlveolesLibres();

};

#endif // WIDGET_H
