#ifndef SERVEURBANQUEWINDOW_H
#define SERVEURBANQUEWINDOW_H

#include <QMainWindow>
#include "serveurbanque.h"


namespace Ui {
    class ServeurBanqueWindow;
}

class ServeurBanqueWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServeurBanqueWindow(QWidget *parent = 0);
    ~ServeurBanqueWindow();

private:
    Ui::ServeurBanqueWindow *ui;
    ServeurBanque *leServeur ;


};

#endif // SERVEURBANQUEWINDOW_H
