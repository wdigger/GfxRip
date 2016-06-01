#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T13:40:00
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GfxRip
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/gfxrip.cpp \
    src/rippermodel.cpp \
    src/imagedelegate.cpp \
    src/inspector.cpp

HEADERS  += src/mainwindow.h \
    src/gfxrip.h \
    src/rippermodel.h \
    src/imagedelegate.h \
    src/inspector.h

RESOURCES += \
    res/resources.qrc

INCLUDEPATH += ./
