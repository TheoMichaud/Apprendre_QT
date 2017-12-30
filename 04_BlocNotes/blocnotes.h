#ifndef BLOCNOTES_H
#define BLOCNOTES_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QDebug>
#include "finddialog.h"
#include "crypto.h"


namespace Ui {
class blocNotes;
}

class blocNotes : public QMainWindow
{
    Q_OBJECT

public:
    explicit blocNotes(QWidget *parent = 0);
    ~blocNotes();

public slots:
    void rechercher(QString expression, QTextDocument::FindFlag options);
    void rechercherReg(QRegExp expression, QTextDocument::FindFlags options);
    void crypter(QString clef);

private slots:
    void on_actionOuvrir_triggered();
    void on_actionNouveau_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionEnregistrer_sous_triggered();
    void on_actionPolice_triggered();
    void on_actionA_propos_triggered();
    void on_plainTextEdit_textChanged();
    void on_actionQuitter_triggered();
    void on_actionCouleur_du_fond_triggered();
    void on_actionAnnuler_triggered();
    void on_actionR_tablir_triggered();
    void on_actionRechercher_triggered();
    void on_actionRechercher_le_suivant_triggered();
    void on_actionCouper_triggered();
    void on_actionCopier_triggered();
    void on_actionColler_triggered();
    void on_actionSelectionner_tout_triggered();
    void on_actionCrypter_triggered();
    void on_actionD_crypter_triggered();


private:
    Ui::blocNotes *ui;
    FindDialog *WRechercher;
    Crypto *WCrypto;
    QString nomDocument;
    QString contenuDocument;
    QFileInfo *fichierInfo;
    bool modifie;
    // attributs utilisés pour la recherche
    QString expression;
    QTextDocument::FindFlag options;
    Crypto::FONCTION opt;
};

#endif // BLOCNOTES_H
