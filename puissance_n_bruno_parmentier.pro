TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Color.cpp \
    src/ConnectN.cpp \
    src/main.cpp \
    src/Player.cpp

QMAKE_CXXFLAGS += -std=c++11 \
    -pedantic-errors

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    src/libs/keyboard.hpp \
    src/libs/stringConvert.hpp \
    src/libs/randomgenerator.hpp \
    src/Color.h \
    src/ConnectN.h \
    src/Player.h \
    src/libs/keyboard.hpp \
    src/libs/randomgenerator.hpp \
    src/libs/stringConvert.hpp

