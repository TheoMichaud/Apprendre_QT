#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T10:59:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServeurBanque
TEMPLATE = app


SOURCES += main.cpp \
    serveurbanque.cpp \
    serveurbanquewindow.cpp \
    compteclient.cpp

HEADERS  += \
    compteclient.h \
    serveurbanque.h \
    serveurbanquewindow.h

FORMS    += \
    serveurbanquewindow.ui
