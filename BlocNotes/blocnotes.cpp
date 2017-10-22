#include "blocnotes.h"
#include "ui_blocnotes.h"
#include "info.h"

blocNotes::blocNotes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::blocNotes),
    nomDocument(""),
    contenuDocument(""),
    fichierInfo(NULL),
    modifie(false)
{
    ui->setupUi(this);
    ui->actionEnregistrer->setEnabled(false);
    ui->actionEnregistrer_sous->setEnabled(false);

}

blocNotes::~blocNotes()
{
    delete ui;
}

void blocNotes::on_actionOuvrir_triggered()
{
    nomDocument = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QDir::homePath() , "Text files (*.txt)");
    fichierInfo = new QFileInfo(nomDocument);
    QFile fichier(nomDocument);
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Fichier ouvert : " + fichierInfo->baseName() );
        setWindowTitle(fichierInfo->baseName() + " - Bloc-notes");
        contenuDocument = fichier.readAll();
        fichier.close();
        ui->plainTextEdit->setPlainText(contenuDocument);

        // désactive le bouton enregistrer
        ui->actionEnregistrer->setEnabled(false);
        // autorise l'enregistrement sous un autre nom
        ui->actionEnregistrer_sous->setEnabled(true);

    }
    else
        statusBar()->showMessage("Erreur de lecture du fichier - " + nomDocument );
}


void blocNotes::on_actionNouveau_triggered(){
    // le nom et le contenu du document sont vides
    nomDocument = "";
    contenuDocument = "";
    fichierInfo = NULL;

    ui->plainTextEdit->setPlainText(contenuDocument);
    ui->actionEnregistrer->setEnabled(false);
    modifie = false;
    setWindowTitle("Sans titre - Bloc-notes");
    statusBar()->showMessage("Nouveau document - Sans titre");
}

void blocNotes::on_actionEnregistrer_triggered(){
    if (nomDocument != ""){
        QFile fichier(nomDocument);
        // Ouverture d'un fichier en lecture seule
        if (fichier.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // création d'un flux
            QTextStream flux(&fichier);
            contenuDocument = ui->plainTextEdit->toPlainText();
            flux << contenuDocument;
            fichier.close();
            statusBar()->showMessage("Le document : " + nomDocument + " a été enregistré");
            // désactive le bouton enregistrer
            ui->actionEnregistrer->setEnabled(false);
            modifie = false;
        }
        else
            statusBar()->showMessage("erreur lors de l'enregistrement du document");
    }
    else
        on_actionEnregistrer_sous_triggered();
}

void blocNotes::on_actionEnregistrer_sous_triggered(){
    nomDocument = QFileDialog::getSaveFileName(this, "Enregistrer sous...", QDir::homePath(), "Texte (*.txt)");
    fichierInfo = new QFileInfo(nomDocument);
    setWindowTitle(fichierInfo->baseName() + " - Bloc-notes");
    on_actionEnregistrer_triggered();
}

void blocNotes::on_plainTextEdit_textChanged(){
    modifie = true;
    // active les boutons enregistrer et enregistrer sous
    ui->actionEnregistrer->setEnabled(true);
    ui->actionEnregistrer_sous->setEnabled(true);

}

void blocNotes::on_actionQuitter_triggered(){
    if (modifie == true){
        // message box question (demande de confirmation pour enregistrer le document modifié)
        // avant de quitter
        QMessageBox::StandardButton reponse;
        QString message = "Voulez-vous <b>enregistrer</b> les modifications de : <br>" + nomDocument;
        reponse = QMessageBox::question(this, "Quitter", message, QMessageBox::Yes|QMessageBox::No );
        if (reponse == QMessageBox::Yes)
            on_actionEnregistrer_triggered();
    }
    this->close();
}

// SLOT pour sélectionner un nouvelle Font
void blocNotes::on_actionPolice_triggered(){
    statusBar()->showMessage("Action Choisir une Font");
    bool ok = false;

    QFont police = QFontDialog::getFont(&ok, ui->plainTextEdit->font(), this, "Choisissez une police");
    if (ok)
        ui->plainTextEdit->setFont(police);
}



void blocNotes::on_actionCouleur_du_fond_triggered(){
    QColor couleur = QColorDialog::getColor(Qt::yellow, this );
    if( couleur.isValid()){
        statusBar()->showMessage("Couleur sélectionnée : " + couleur.name());

        ui->plainTextEdit->setStyleSheet(QString("background: %1").arg(couleur.name()));
    }
}

void blocNotes::on_actionA_propos_triggered(){
    Info fenetreInfo(this);
    fenetreInfo.exec();
    statusBar()->showMessage("A propos du blocNotes : Version 2017 1.0");

}

// Undoes the last operation
void blocNotes::on_actionAnnuler_triggered(){
    ui->plainTextEdit->undo();
}

// redoes the last operation
void blocNotes::on_actionR_tablir_triggered(){
    ui->plainTextEdit->redo();
}

void blocNotes::on_actionRechercher_triggered(){
    expression = QInputDialog::getText(this, "Rechercher", "Rechercher : ");
    if(!ui->plainTextEdit->find(expression)){
        QMessageBox::information(this, "Info", "L'expression : <b>" + expression + "</b> n'a pas été trouvée !");
    }
}

void blocNotes::on_actionRechercher_le_suivant_triggered(){
    if(!ui->plainTextEdit->find(expression)){
        QMessageBox::information(this, "Info", "L'expression : <b>" + expression + "</b> n'a pas été trouvée !");
    }
}
