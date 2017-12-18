#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T16:18:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        ihmsocket.cpp \
    modbustcp.cpp

HEADERS  += ihmsocket.h \
    modbustcp.h

FORMS    += ihmsocket.ui
