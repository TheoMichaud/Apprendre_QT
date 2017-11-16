#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // déclaration d'un délégué redéfini
    monDelegue = new Delegate(this);

    // déclaration du modèle
    // Pour construire un modèle avec plusieurs lignes et colonnes on doit utiliser
    // un QStandardItemModel
    // Des lignes et des colonnes supplémentaires peuvent toujours être ajoutées
    // par la suite au besoin. Il faudra appeler appendRow() et appendColumn()

    modele = new QStandardItemModel(NBLIGNE, NBCOLONNE, this);  //nb de lignes, nb de colonne, parent

    // Remplissage du modèle : chaque item est rempli avec un entier
    // et chaque item est aligné au centre de la cellule.

    for (int raw=0; raw < NBLIGNE; raw++)
    {
        for (int col=0; col < NBCOLONNE; col++)
        {
            QModelIndex index = modele->index(raw,col,QModelIndex());
            modele->setData(index,  raw * NBCOLONNE + (col+1), Qt::DisplayRole);
            // la fonction setData permet de coder à la fois le fond de l'objet
            // (sa valeur) et sa forme (couleur, police alignemnt...)
            // elle posède un argument de type entier qui code le rôle
            modele->setData(index, Qt::AlignHCenter, Qt::TextAlignmentRole);

        }
    }
    // Un item particulier peut être modifié

    QModelIndex index = modele->index(2,2,QModelIndex());
    modele->setData(index, "une valeur");

    // association du model à la vue (tableview)
    ui->tableView->setModel(modele);

    // association du délégué à la vue
    ui->tableView->setItemDelegate(monDelegue);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    // ajouter une ligne au modele
    QList<QStandardItem *> ligne;
    modele->appendRow(ligne);
}

void Dialog::on_AjouterColonne_clicked()
{
    // ajouter une colonne au modele
    QList<QStandardItem *> colonne;
    modele->appendColumn(colonne);
}



void Dialog::on_pushButtonSelection_clicked()
{
    // affiche les items sélectionnés dans une boite de dialogue

    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList valeurSelections = selection->selectedIndexes();

    QString message;

    for (int i = 0 ; i < valeurSelections.size() ; i++)
    {
        QVariant valeurSelectionne = modele->data(valeurSelections[i], Qt::DisplayRole);

        message += "( " + QString::number(valeurSelections[i].row()+1);
        message += " , " + QString::number(valeurSelections[i].column()+1);
        message += " ) : ";
        message += valeurSelectionne.toString() + "<br />";
    }

    QMessageBox::information(this, "Eléments sélectionnés", message);
}

