#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T10:38:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = memorywidget
TEMPLATE = app


SOURCES += main.cpp\
        memorywidget.cpp \
    memoryview.cpp \
    memoryitem.cpp \
    memoryscene.cpp \
    appeventfilter.cpp \
    labelitem.cpp \
    memoryitemgroup.cpp

HEADERS  += memorywidget.h \
    memoryview.h \
    memoryitem.h \
    memoryscene.h \
    appeventfilter.h \
    globalvalues.hpp \
    labelitem.hpp \
    memoryitemgroup.h

FORMS    += \
    form.ui
