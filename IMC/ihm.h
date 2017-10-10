#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class IHM;
}

class IHM : public QMainWindow
{
    Q_OBJECT

public:
    explicit IHM(QWidget *parent = 0);
    ~IHM();



private slots:
    void on_pushButtonSuite_clicked();

    void Devine();

    void on_pushButtonLorentz_clicked();

    void on_pushButtonLorentzAge_clicked();



    void on_QTabOnglet_currentChanged(int index);

private:
    Ui::IHM *ui;

    double poids;
    double taille;
    QString nom;
    QString prenom;
    int age;
    static const int NB_IMC = 6;
    static const int NB_CORPULENCE = 7;

    void AfficherInfos();
    QString DeterminerClassification(double imc);
    /*void Devine();*/
    void Lorentz();
    void LorentzAge();

};

#endif // IHM_H
