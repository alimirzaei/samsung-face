QT += core network
QT -= gui
TEMPLATE = app
CONFIG += c++11

LIBS += `pkg-config opencv --libs` -ldlib -lopenblas
SOURCES += \
    clsFaceLandmarkDetection.cpp \
    clsAmooNorouz.cpp \
    clsEnrichedFullObject.cpp \
    main.cpp \
    MyTcpServer.cpp

HEADERS += \
    clsFaceLandmarkDetection.h \
    clsAmooNorouz.h \
    clsEnrichedFullObject.h \
    MyTcpServer.h
