#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T17:30:13
#
#-------------------------------------------------

QT       -= core gui

TARGET = configmacros
TEMPLATE = lib

HEADERS += libconfigmacros.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
