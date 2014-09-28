include(../../defaults.pri)
TEMPLATE = lib
TARGET = journey

SOURCES += route.cpp \
    map.cpp \
    journeyinfo.cpp \
    cityinfo.cpp

HEADERS += \
    route.h \
    map.h \
    journeyinfo.h \
    cityinfo.h

CONFIG += c++11
