#ifndef ASSITANTRESEAU_H
#define ASSITANTRESEAU_H

#include <QMainWindow>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QDebug>

namespace Ui {
class AssitantReseau;
}

class AssitantReseau : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssitantReseau(QWidget *parent = 0);
    ~AssitantReseau();

private slots:
    void on_actionarp_a_triggered();
    void onDataRead();

    void on_actionarp_d_triggered();

    void on_actionroute_print_triggered();

private:
    Ui::AssitantReseau *ui;
    QProcess *process;
};

#endif // ASSITANTRESEAU_H
