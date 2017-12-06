#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T12:33:14
#
#-------------------------------------------------

QT       += core gui network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServeurBanque
TEMPLATE = app


SOURCES += main.cpp\
        serveurmainwindow.cpp \
    compte.cpp

HEADERS  += serveurmainwindow.h \
    compte.h

FORMS    += serveurmainwindow.ui

RESOURCES += \
    icones.qrc
