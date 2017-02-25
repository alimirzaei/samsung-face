TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += `pkg-config opencv --libs`
SOURCES += main.cpp
