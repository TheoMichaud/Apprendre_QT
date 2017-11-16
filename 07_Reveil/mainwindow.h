#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsItem>
#include <QTime>
#include <QTimer>
//#include <QSound>
#include <QDebug>
#include "alarmes.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void tournerAiguilles();
    void setAlarme(const QTime &valeurAlarme);

    void on_actionQuitter_triggered();
    void on_actionAlarme_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *grandeAiguille;
    QGraphicsLineItem *petiteAiguille;
    QGraphicsLineItem *troteuse;

    //QSound *sonnerieAlarme;
    Alarmes *WAlarme;
    QTime timeAlarme;
    void dessinerCadran();
    QTimer *tictac;


};

#endif // MAINWINDOW_H
