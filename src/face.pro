QT += core
QT -= gui
TEMPLATE = app
CONFIG += c++11

LIBS += `pkg-config opencv --libs` -ldlib -lopenblas
SOURCES += \
    clsFaceLandmarkDetection.cpp \
    clsAmooNorouz.cpp \
    main.cpp \
    clsGetLandmarks.cpp

HEADERS += \
    clsFaceLandmarkDetection.h \
    clsAmooNorouz.h \
    clsGetLandmarks.h
