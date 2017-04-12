QT       += core gui widgets network

CONFIG += c++11

TARGET = udptest

TEMPLATE = app

HEADERS  += widget.h \
            udpsender.h \
            udpreceiver.h


SOURCES += main.cpp\
            widget.cpp \
            udpsender.cpp \
            udpreceiver.cpp

FORMS    += widget.ui
