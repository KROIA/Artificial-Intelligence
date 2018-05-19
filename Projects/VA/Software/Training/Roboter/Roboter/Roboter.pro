#-------------------------------------------------
#
# Project created by QtCreator 2017-10-29T09:21:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Roboter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += C:\Users\Alex\Documents\QT\Roboter\Roboter\src
INCLUDEPATH += E:\Users\Alex\Documents\QT\Roboter\Roboter\inc


SOURCES += \
        src/geneticNet.cpp \
        src/Net.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/enviroment.cpp \
        src/draw.cpp \
        src/objects/circle.cpp \
        src/objects/line.cpp \
        src/objects/roboter.cpp \
        src/matrix.cpp \
        src/qtgeneticnet.cpp \
        src/config.cpp \
        src/graph.cpp \
        src/worker.cpp


HEADERS += \
		inc/geneticNet.h \
        inc/Net.h \
        inc/mainwindow.h \
        inc/enviroment.h \
        inc/draw.h \
        inc/objects/circle.h \
        inc/objects/line.h \
        inc/objects/roboter.h \
        inc/matrix.h \
        inc/qtgeneticnet.h \
        inc/config.h \
        inc/graph.h \
        inc/worker.h

FORMS += \
        mainwindow.ui
