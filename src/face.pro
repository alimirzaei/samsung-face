QT += core
QT -= gui
TEMPLATE = app
CONFIG += c++11

LIBS += `pkg-config opencv --libs` -ldlib -lopenblas
SOURCES += face_landmark_detection_ex.cpp

HEADERS += \
    face_landmark_detection_ex.h
