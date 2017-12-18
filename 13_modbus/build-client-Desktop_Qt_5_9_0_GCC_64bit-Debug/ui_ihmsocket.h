/********************************************************************************
** Form generated from reading UI file 'ihmsocket.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMSOCKET_H
#define UI_IHMSOCKET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IhmSocket
{
public:
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditAdresse;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditNumeroPort;
    QPushButton *pushButtonConnexionAuServeur;
    QTextEdit *textEditAfficheurEvenement;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *AdresseCoil;
    QCheckBox *checkBoxEtat;
    QPushButton *pushButtonF1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *AdresseCoilEcriture;
    QCheckBox *checkBoxEtatEcriture;
    QPushButton *pushButtonF5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpinBox *AdresseRegistreLecture;
    QLineEdit *ValeurRegistreLire;
    QPushButton *pushButtonF3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *AdresseRegistreEcriture;
    QLineEdit *ValeurRegistreEcrire;
    QPushButton *pushButtonF6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_8;

    void setupUi(QWidget *IhmSocket)
    {
        if (IhmSocket->objectName().isEmpty())
            IhmSocket->setObjectName(QStringLiteral("IhmSocket"));
        IhmSocket->resize(693, 657);
        horizontalLayout_9 = new QHBoxLayout(IhmSocket);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(IhmSocket);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        lineEditAdresse = new QLineEdit(IhmSocket);
        lineEditAdresse->setObjectName(QStringLiteral("lineEditAdresse"));
        lineEditAdresse->setMinimumSize(QSize(300, 0));
        lineEditAdresse->setFont(font);

        horizontalLayout_2->addWidget(lineEditAdresse);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(IhmSocket);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lineEditNumeroPort = new QLineEdit(IhmSocket);
        lineEditNumeroPort->setObjectName(QStringLiteral("lineEditNumeroPort"));
        lineEditNumeroPort->setMaximumSize(QSize(100, 16777215));
        lineEditNumeroPort->setFont(font);

        horizontalLayout->addWidget(lineEditNumeroPort);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout);

        pushButtonConnexionAuServeur = new QPushButton(IhmSocket);
        pushButtonConnexionAuServeur->setObjectName(QStringLiteral("pushButtonConnexionAuServeur"));
        pushButtonConnexionAuServeur->setEnabled(true);
        pushButtonConnexionAuServeur->setFont(font);

        horizontalLayout_4->addWidget(pushButtonConnexionAuServeur);


        verticalLayout_2->addLayout(horizontalLayout_4);

        textEditAfficheurEvenement = new QTextEdit(IhmSocket);
        textEditAfficheurEvenement->setObjectName(QStringLiteral("textEditAfficheurEvenement"));
        QFont font1;
        font1.setPointSize(11);
        textEditAfficheurEvenement->setFont(font1);

        verticalLayout_2->addWidget(textEditAfficheurEvenement);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(IhmSocket);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_5->addWidget(label_3);

        AdresseCoil = new QSpinBox(IhmSocket);
        AdresseCoil->setObjectName(QStringLiteral("AdresseCoil"));
        AdresseCoil->setMinimum(512);
        AdresseCoil->setMaximum(767);

        horizontalLayout_5->addWidget(AdresseCoil);

        checkBoxEtat = new QCheckBox(IhmSocket);
        checkBoxEtat->setObjectName(QStringLiteral("checkBoxEtat"));
        checkBoxEtat->setFont(font);

        horizontalLayout_5->addWidget(checkBoxEtat);

        pushButtonF1 = new QPushButton(IhmSocket);
        pushButtonF1->setObjectName(QStringLiteral("pushButtonF1"));
        pushButtonF1->setFont(font);

        horizontalLayout_5->addWidget(pushButtonF1);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(IhmSocket);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_6->addWidget(label_4);

        AdresseCoilEcriture = new QSpinBox(IhmSocket);
        AdresseCoilEcriture->setObjectName(QStringLiteral("AdresseCoilEcriture"));
        AdresseCoilEcriture->setMinimum(512);
        AdresseCoilEcriture->setMaximum(767);

        horizontalLayout_6->addWidget(AdresseCoilEcriture);

        checkBoxEtatEcriture = new QCheckBox(IhmSocket);
        checkBoxEtatEcriture->setObjectName(QStringLiteral("checkBoxEtatEcriture"));
        checkBoxEtatEcriture->setFont(font);

        horizontalLayout_6->addWidget(checkBoxEtatEcriture);

        pushButtonF5 = new QPushButton(IhmSocket);
        pushButtonF5->setObjectName(QStringLiteral("pushButtonF5"));
        pushButtonF5->setFont(font);

        horizontalLayout_6->addWidget(pushButtonF5);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(IhmSocket);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        horizontalLayout_8->addWidget(label_6);

        AdresseRegistreLecture = new QSpinBox(IhmSocket);
        AdresseRegistreLecture->setObjectName(QStringLiteral("AdresseRegistreLecture"));
        AdresseRegistreLecture->setMinimumSize(QSize(100, 0));
        AdresseRegistreLecture->setMinimum(0);
        AdresseRegistreLecture->setMaximum(767);
        AdresseRegistreLecture->setValue(0);

        horizontalLayout_8->addWidget(AdresseRegistreLecture);

        ValeurRegistreLire = new QLineEdit(IhmSocket);
        ValeurRegistreLire->setObjectName(QStringLiteral("ValeurRegistreLire"));
        ValeurRegistreLire->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_8->addWidget(ValeurRegistreLire);

        pushButtonF3 = new QPushButton(IhmSocket);
        pushButtonF3->setObjectName(QStringLiteral("pushButtonF3"));
        pushButtonF3->setMinimumSize(QSize(162, 0));
        pushButtonF3->setFont(font);

        horizontalLayout_8->addWidget(pushButtonF3);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(IhmSocket);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_7->addWidget(label_5);

        AdresseRegistreEcriture = new QSpinBox(IhmSocket);
        AdresseRegistreEcriture->setObjectName(QStringLiteral("AdresseRegistreEcriture"));
        AdresseRegistreEcriture->setMinimumSize(QSize(100, 0));
        AdresseRegistreEcriture->setMinimum(0);
        AdresseRegistreEcriture->setMaximum(767);
        AdresseRegistreEcriture->setValue(0);

        horizontalLayout_7->addWidget(AdresseRegistreEcriture);

        ValeurRegistreEcrire = new QLineEdit(IhmSocket);
        ValeurRegistreEcrire->setObjectName(QStringLiteral("ValeurRegistreEcrire"));
        ValeurRegistreEcrire->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_7->addWidget(ValeurRegistreEcrire);

        pushButtonF6 = new QPushButton(IhmSocket);
        pushButtonF6->setObjectName(QStringLiteral("pushButtonF6"));
        pushButtonF6->setMinimumSize(QSize(162, 0));
        pushButtonF6->setFont(font);

        horizontalLayout_7->addWidget(pushButtonF6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_8 = new QPushButton(IhmSocket);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setFont(font);

        horizontalLayout_3->addWidget(pushButton_8);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_9->addLayout(verticalLayout_2);


        retranslateUi(IhmSocket);
        QObject::connect(pushButton_8, SIGNAL(clicked()), IhmSocket, SLOT(close()));

        QMetaObject::connectSlotsByName(IhmSocket);
    } // setupUi

    void retranslateUi(QWidget *IhmSocket)
    {
        IhmSocket->setWindowTitle(QApplication::translate("IhmSocket", "Client ModBUS TCP", Q_NULLPTR));
        label->setText(QApplication::translate("IhmSocket", "Host Name Serveur", Q_NULLPTR));
        lineEditAdresse->setText(QApplication::translate("IhmSocket", "172.18.58.161", Q_NULLPTR));
        label_2->setText(QApplication::translate("IhmSocket", "Num\303\251ro de port", Q_NULLPTR));
        lineEditNumeroPort->setText(QApplication::translate("IhmSocket", "502", Q_NULLPTR));
        pushButtonConnexionAuServeur->setText(QApplication::translate("IhmSocket", "Connexion", Q_NULLPTR));
        label_3->setText(QApplication::translate("IhmSocket", "Adresse Coil : ", Q_NULLPTR));
        checkBoxEtat->setText(QApplication::translate("IhmSocket", "\303\251tat", Q_NULLPTR));
        pushButtonF1->setText(QApplication::translate("IhmSocket", "Lire Coil (01)", Q_NULLPTR));
        label_4->setText(QApplication::translate("IhmSocket", "Adresse Coil : ", Q_NULLPTR));
        checkBoxEtatEcriture->setText(QApplication::translate("IhmSocket", "\303\251tat", Q_NULLPTR));
        pushButtonF5->setText(QApplication::translate("IhmSocket", "Ecriture Coil (05)", Q_NULLPTR));
        label_6->setText(QApplication::translate("IhmSocket", "Adresse Registre : ", Q_NULLPTR));
        pushButtonF3->setText(QApplication::translate("IhmSocket", "Lire registre (03)", Q_NULLPTR));
        label_5->setText(QApplication::translate("IhmSocket", "Adresse Registre : ", Q_NULLPTR));
        pushButtonF6->setText(QApplication::translate("IhmSocket", "Ecrire registre (06)", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("IhmSocket", "Quitter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IhmSocket: public Ui_IhmSocket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMSOCKET_H
