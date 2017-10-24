#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

private slots:
    void on_texteRecherche_textChanged(const QString &arg1);

    void on_pushButtonRechercher_clicked();

signals:
    void rechercherPrecedent(QString texte, Qt::CaseSensitivity cs);
    void rechercherSuivant(QString texte, Qt::CaseSensitivity cs);

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
