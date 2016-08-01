#-------------------------------------------------
#
# Project created by QtCreator 2016-07-27T15:50:03
#
#-------------------------------------------------

QT       += core gui webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testWebEngine
TEMPLATE = app

target.path=/home/root
INSTALLS += target
SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

