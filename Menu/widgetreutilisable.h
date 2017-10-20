#ifndef WIDGETREUTILISABLE_H
#define WIDGETREUTILISABLE_H

#include <QWidget>

namespace Ui {
class WidgetReutilisable;
}

class WidgetReutilisable : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetReutilisable(QWidget *parent = 0);
    ~WidgetReutilisable();

private:
    Ui::WidgetReutilisable *ui;
};

#endif // WIDGETREUTILISABLE_H
