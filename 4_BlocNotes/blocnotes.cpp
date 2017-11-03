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
    WRechercher = new FindDialog(this);

    if(!connect(WRechercher, SIGNAL(rechercher(QString,QTextDocument::FindFlag)), this, SLOT(rechercher(QString,QTextDocument::FindFlag))))
        qDebug() << "Erreur connexion rechercher";
    if(!connect(WRechercher, SIGNAL(rechercherReg(QRegExp,QTextDocument::FindFlags)), this, SLOT(rechercherReg(QRegExp,QTextDocument::FindFlags))))
        qDebug() << "Erreur connexion rechercherReg";
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

// SLOT pour sélectionner une nouvelle Font
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

    WRechercher->show();
}

void blocNotes::rechercher(QString expression, QTextDocument::FindFlag options ){


    blocNotes::expression = expression;  // sauvegarde de l'expression dans l'argument expression du blocNotes
    blocNotes::options = options;        // sauvegarde des options de recherche

    if(!ui->plainTextEdit->find(expression, options)){
        QMessageBox::information(this, "Info", "Recherche terminée !");
    }
    else{
        QTextCursor curseur;
        curseur = ui->plainTextEdit->textCursor();

        statusBar()->showMessage("Expression trouvée : " + expression +
                                 "\t-> (ligne " +
                                 QString::number(curseur.blockNumber()+1) +
                                 " colonne " +
                                 QString::number(curseur.columnNumber() - expression.size()+1) +
                                 ")"
                                 );
    }
}

// slot pour rechercher à partir d'une expression régulière
// exemple [0-9]{3}  recherche d'un nombre composé de 3 chiffres
void blocNotes::rechercherReg(QRegExp expression, QTextDocument::FindFlags options)
{
    if(!ui->plainTextEdit->find(expression, options)){
        QMessageBox::information(this, "Info", "Recherche terminée !");
    }
    else{
        QTextCursor curseur;
        curseur = ui->plainTextEdit->textCursor();

        statusBar()->showMessage("Expression matchée -> (ligne " +
                                 QString::number(curseur.blockNumber()+1) +
                                 " colonne " +
                                 QString::number(curseur.columnNumber()) +
                                 ")"
                                 );
    }
}


// Slot appelé quand la touche F3 est actionnée
void blocNotes::on_actionRechercher_le_suivant_triggered(){
    rechercher(expression,options);   // appelle le slot rechercher
}

void blocNotes::on_actionCouper_triggered(){
    ui->plainTextEdit->cut();
}

void blocNotes::on_actionCopier_triggered(){
    ui->plainTextEdit->copy();
}

void blocNotes::on_actionColler_triggered(){
    ui->plainTextEdit->paste();
}

void blocNotes::on_actionSelectionner_tout_triggered(){
    ui->plainTextEdit->selectAll();
}
