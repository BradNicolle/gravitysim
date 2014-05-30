#-------------------------------------------------
#
# Project created by QtCreator 2013-08-11T21:08:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GravitySim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    planet.cpp \
    spacecraft.cpp \
    canvas.cpp \
    trajectory.cpp \
    xmlparser.cpp

HEADERS  += mainwindow.h \
    planet.h \
    spacecraft.h \
    canvas.h \
    trajectory.h \
    manoeuvre.h \
    xmlparser.h

FORMS    += mainwindow.ui

RESOURCES += \
    application.qrc
