#include "ihmsocket.h"
#include "ui_ihmsocket.h"

ClientDialogueWindows::ClientDialogueWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmSocket)
{
    ui->setupUi(this);
    modbus = new modbusTcp(this);

    if(!connect(modbus, SIGNAL(Reponse(QString)), this, SLOT(OnReponse(QString))))
    qDebug() << "Erreur connexion reponse";
}

ClientDialogueWindows::~ClientDialogueWindows()
{
    if (socketDeDialogueAvecServeur!=NULL)
    {
        socketDeDialogueAvecServeur->close();
        delete socketDeDialogueAvecServeur;
    }
    delete ui;
}

void ClientDialogueWindows::on_lineEditAdresse_textEdited(const QString &arg1)
{

}

void ClientDialogueWindows::on_lineEditNumeroPort_textEdited(const QString &arg1)
{

}

void ClientDialogueWindows::on_pushButtonConnexionAuServeur_clicked()
{
    if (ui->pushButtonConnexionAuServeur->text()!="Déconnexion"){
        // pour chaque nouvelle connexion on réinitialise la zone evenement
        ui->textEditAfficheurEvenement->clear();
        // connexion a l'esclave modbus
        modbus->ConnecterEsclaveModBus(ui->lineEditAdresse->text(),ui->lineEditNumeroPort->text().toInt());
        ui->pushButtonConnexionAuServeur->setText("Déconnexion");
        // rendre accessible zone des demandes
        //ui->groupBoxInfosPoste->setEnabled(true);
         // désactiver les zones de saisie d'adresse ip et de numéro de port
        ui->lineEditAdresse->setEnabled(false);
        ui->lineEditNumeroPort->setEnabled(false);
    }
    else
    {
        modbus->DeconnecterEsclaveModBus();
        ui->pushButtonConnexionAuServeur->setText("Connexion");
        ui->lineEditAdresse->setEnabled(true);
        ui->lineEditNumeroPort->setEnabled(true);
        //ui->groupBoxInfosPoste->setEnabled(false);

    }
}




// requète 5 Force Single Coil
void ClientDialogueWindows::on_pushButtonF5_clicked()
{
    quint16 adresseCoil = ui->AdresseCoilEcriture->value();
    bool etat = ui->checkBoxEtatEcriture->isChecked();
    modbus->ForceSingleCoil(adresseCoil, etat);  // Voir page 164 doc Wago
}

// requète 1 read Coil
void ClientDialogueWindows::on_pushButtonF1_clicked()
{
    quint16 adresseCoil = ui->AdresseCoil->value();
    quint16 nb = 1;
    modbus->ReadCoil(adresseCoil,nb);
}

// Requète 06 Ecriture d'un mot Preset Single Register
void ClientDialogueWindows::on_pushButtonF6_clicked()
{
    quint16 adresseRegistre = ui->AdresseRegistreEcriture->text().toInt();
    quint16 valeur = ui->ValeurRegistreEcrire->text().toInt();
    modbus->PresetSingleRegister(adresseRegistre, valeur);
}

// Requète 03 Lecture de N mots Read Holding Registers
void ClientDialogueWindows::on_pushButtonF3_clicked()
{
    quint16 adresseRegistre = ui->AdresseRegistreLecture->text().toInt();
    modbus->ReadHoldingRegisters(adresseRegistre,0x0001); // 1 seul registre
}

void ClientDialogueWindows::OnReponse(QString reponse)
{
     ui->textEditAfficheurEvenement->append(reponse);
}
