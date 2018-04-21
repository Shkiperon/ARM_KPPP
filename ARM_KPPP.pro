#-------------------------------------------------
#
# Project created by Shkiperon 2016-02-16T16:40:13
#
#-------------------------------------------------

QT       += core gui network widgets testlib

TARGET = ARM_KPPP
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    qtconntodb.cpp \
    qtrfid.cpp \
    qtoknoapp.cpp \
    qtrelay.cpp \
    qtbutton.cpp \
    qmousemover.cpp

HEADERS  += \
    qtconntodb.h \
    qtrfid.h \
    qtoknoapp.h \
    qtrelay.h \
    qtbutton.h \
    qmousemover.h

LIBS += -lwiringPi
