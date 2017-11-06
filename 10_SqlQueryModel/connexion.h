#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QString>

namespace Ui {
class connexion;
}

class connexion : public QDialog
{
    Q_OBJECT

public:
    explicit connexion(QWidget *parent = 0);
    ~connexion();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::connexion *ui;
    QString serveurIp;
    QString base;
    QString utilisateur;
    QString password;

signals:
void connecter(QString serveurIp, QString base, QString utilisateur, QString password);
};

#endif // CONNEXION_H
