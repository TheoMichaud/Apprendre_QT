#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextDocument>

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
    void rechercher(QString expression, QTextDocument::FindFlag options);
    void rechercherReg(QRegExp expression, QTextDocument::FindFlags options);


private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
