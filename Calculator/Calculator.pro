#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T20:07:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Expression.cpp \
    MathEx.cpp \
    pushbutton.cpp

HEADERS  += mainwindow.h \
    Expression.h \
    MathEx.h \
    metacharacter.h \
    pushbutton.h

CONFIG += c++11
