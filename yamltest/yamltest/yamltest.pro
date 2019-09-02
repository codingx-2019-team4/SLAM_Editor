TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

message($$OUT_PWD)

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../yamltest/yaml-cpp/include

LIBS += ../yamltest/yaml-cpp/build/libyaml-cpp.a

SOURCES += \
        main.cpp
