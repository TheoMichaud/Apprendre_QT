#ifndef ALARMES_H
#define ALARMES_H

#include <QDialog>
#include <QTime>

namespace Ui {
class Alarmes;
}

class Alarmes : public QDialog
{
    Q_OBJECT

public:
    explicit Alarmes(QWidget *parent = 0);
    ~Alarmes();

signals:
    void reglerAlarme(QTime alarme);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Alarmes *ui;
};

#endif // ALARMES_H
