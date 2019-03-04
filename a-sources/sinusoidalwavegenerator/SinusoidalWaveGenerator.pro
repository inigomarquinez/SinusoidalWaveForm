#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T15:11:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SinusoidalWaveGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp \
    qcustomplot.cpp \
    sinusoidalEquation.cpp \
    plotWindow.cpp

HEADERS  += mainWindow.h \
    qcustomplot.h \
    sinusoidalEquation.h \
    plotWindow.h

FORMS    += mainWindow.ui \
    plotWindow.ui

RESOURCES += \
    resources.qrc
