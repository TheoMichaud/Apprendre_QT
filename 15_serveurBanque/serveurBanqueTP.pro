#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T11:52:41
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serveurBanqueTP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serveurbanque.cpp \
    compteclient.cpp \
    interfaceaccesbdbanque.cpp

HEADERS  += mainwindow.h \
    serveurbanque.h \
    compteclient.h \
    interfaceaccesbdbanque.h

FORMS    += mainwindow.ui
