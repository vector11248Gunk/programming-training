#-------------------------------------------------
#
# Project created by QtCreator 2017-08-28T10:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        sudoku.cpp \
		dancing_link.cpp

HEADERS  += mainwindow.h \
        utils.h \
        sudoku.h \
		dancing_link.h

FORMS    += mainwindow.ui
