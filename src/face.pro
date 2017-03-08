QT += core
QT -= gui
TEMPLATE = lib
CONFIG += c++11

LIBS += `pkg-config opencv --libs` -ldlib -lopenblas
SOURCES += \
    clsFaceLandmarkDetection.cpp \
    clsAmooNorouz.cpp \
    clsEnrichedFullObject.cpp \
    main.cpp

HEADERS += \
    clsFaceLandmarkDetection.h \
    clsAmooNorouz.h \
    clsEnrichedFullObject.h
