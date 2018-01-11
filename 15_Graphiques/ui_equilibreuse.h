/********************************************************************************
** Form generated from reading UI file 'equilibreuse.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUILIBREUSE_H
#define UI_EQUILIBREUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Equilibreuse
{
public:
    QAction *actionOuvrir;
    QAction *actionQuitter;
    QAction *actionAffichage_en_Newton;
    QAction *actionAffichage_en_brutes;
    QAction *actionPrise_en_compte_du_filtre;
    QAction *actionPrise_en_compte_de_l_origine;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Equilibreuse)
    {
        if (Equilibreuse->objectName().isEmpty())
            Equilibreuse->setObjectName(QStringLiteral("Equilibreuse"));
        Equilibreuse->resize(565, 399);
        actionOuvrir = new QAction(Equilibreuse);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionQuitter = new QAction(Equilibreuse);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionAffichage_en_Newton = new QAction(Equilibreuse);
        actionAffichage_en_Newton->setObjectName(QStringLiteral("actionAffichage_en_Newton"));
        actionAffichage_en_Newton->setCheckable(true);
        actionAffichage_en_Newton->setEnabled(false);
        actionAffichage_en_brutes = new QAction(Equilibreuse);
        actionAffichage_en_brutes->setObjectName(QStringLiteral("actionAffichage_en_brutes"));
        actionAffichage_en_brutes->setCheckable(true);
        actionAffichage_en_brutes->setChecked(true);
        actionPrise_en_compte_du_filtre = new QAction(Equilibreuse);
        actionPrise_en_compte_du_filtre->setObjectName(QStringLiteral("actionPrise_en_compte_du_filtre"));
        actionPrise_en_compte_du_filtre->setCheckable(true);
        actionPrise_en_compte_du_filtre->setEnabled(false);
        actionPrise_en_compte_de_l_origine = new QAction(Equilibreuse);
        actionPrise_en_compte_de_l_origine->setObjectName(QStringLiteral("actionPrise_en_compte_de_l_origine"));
        actionPrise_en_compte_de_l_origine->setCheckable(true);
        actionPrise_en_compte_de_l_origine->setEnabled(false);
        centralWidget = new QWidget(Equilibreuse);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Equilibreuse->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Equilibreuse);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 565, 24));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        Equilibreuse->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Equilibreuse);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Equilibreuse->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Equilibreuse);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Equilibreuse->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFichier->addAction(actionOuvrir);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuOptions->addAction(actionAffichage_en_brutes);
        menuOptions->addSeparator();
        menuOptions->addAction(actionAffichage_en_Newton);
        menuOptions->addAction(actionPrise_en_compte_du_filtre);
        menuOptions->addAction(actionPrise_en_compte_de_l_origine);

        retranslateUi(Equilibreuse);
        QObject::connect(actionQuitter, SIGNAL(triggered()), Equilibreuse, SLOT(close()));

        QMetaObject::connectSlotsByName(Equilibreuse);
    } // setupUi

    void retranslateUi(QMainWindow *Equilibreuse)
    {
        Equilibreuse->setWindowTitle(QApplication::translate("Equilibreuse", "Equilibreuse", Q_NULLPTR));
        actionOuvrir->setText(QApplication::translate("Equilibreuse", "Ouvrir", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOuvrir->setShortcut(QApplication::translate("Equilibreuse", "Alt+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionQuitter->setText(QApplication::translate("Equilibreuse", "Quitter", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuitter->setShortcut(QApplication::translate("Equilibreuse", "Alt+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionAffichage_en_Newton->setText(QApplication::translate("Equilibreuse", "Affichage en Newton", Q_NULLPTR));
        actionAffichage_en_brutes->setText(QApplication::translate("Equilibreuse", "Affichage mesures brutes", Q_NULLPTR));
        actionPrise_en_compte_du_filtre->setText(QApplication::translate("Equilibreuse", "Compensation du filtre", Q_NULLPTR));
        actionPrise_en_compte_de_l_origine->setText(QApplication::translate("Equilibreuse", "Prise en compte de l'origine", Q_NULLPTR));
        menuFichier->setTitle(QApplication::translate("Equilibreuse", "Fichier", Q_NULLPTR));
        menuOptions->setTitle(QApplication::translate("Equilibreuse", "Options", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Equilibreuse: public Ui_Equilibreuse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUILIBREUSE_H
