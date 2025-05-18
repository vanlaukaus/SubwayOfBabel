RC_ICONS = "C:/SubwayOfBabel/appicon.ico"
QT       += core gui widgets network
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubwayOfBabel
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui

win32 {
    LIBS += -lws2_32
}
