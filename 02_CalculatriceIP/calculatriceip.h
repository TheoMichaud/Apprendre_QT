#ifndef CALCULATRICEIP_H
#define CALCULATRICEIP_H

#include <QWidget>

namespace Ui {
class CalculatriceIP;
}

class CalculatriceIP : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatriceIP(QWidget *parent = 0);
    ~CalculatriceIP();

private slots:
    void on_comboBoxSuffixe_currentIndexChanged(int index);
    void onAdresseIPChange();

private:
    Ui::CalculatriceIP *ui;
    QString ConvertirTableauIpEnQString(const quint8 _tabIp[]);
};

#endif // CALCULATRICEIP_H
