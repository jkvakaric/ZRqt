QT += core sql
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = ZRqt
 target.files = ZRqt
 target.path = /home/root
INSTALLS += target

TEMPLATE = app

SOURCES += main.cpp \
    reading.cpp \
    dbconnection.cpp \
    activereading.cpp \
    apploop.cpp

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    reading.h \
    dbconnection.h \
    activereading.h \
    apploop.h
