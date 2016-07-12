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
    memoryitemgroup.cpp \
    memoryitempresentation.cpp \
    memoryunit.cpp

HEADERS  += \
    globalvalues.hpp \
    labelitem.hpp \
    memoryitempresentation.hpp \
    memoryscene.hpp \
    memoryview.hpp \
    memorywidget.hpp \
    memoryitemgroup.hpp \
    memoryitem.hpp \
    appeventfilter.hpp \
    memoryunit.hpp

FORMS    += \
    form.ui
