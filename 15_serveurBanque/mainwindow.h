#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serveurbanque.h"

namespace Ui {
class MainWindow;
}

class BanqueMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BanqueMainWindow(QWidget *parent = 0);
    ~BanqueMainWindow();

private:
    Ui::MainWindow *ui;
    ServeurBanque *leServeur;
};

#endif // MAINWINDOW_H
