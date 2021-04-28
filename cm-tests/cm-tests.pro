include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += testlib
QT -= gui

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lcm-lib

TARGET = client-tests
TEMPLATE = app

CONFIG += c++14
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += source \
    ../cm-lib/source

SOURCES += source/models/tst_clienttests.cpp \
    source/controllers/mastercontrollertests.cpp \
    source/data/datetimedecoratortests.cpp \
    source/data/enumeratordecoratortests.cpp \
    source/data/intdecoratortests.cpp \
    source/data/stringdecoratortests.cpp \
    source/main.cpp \
    source/testsuite.cpp

HEADERS += \
    source/controllers/mastercontrollertests.h \
    source/data/datetimedecoratortests.h \
    source/data/enumeratordecoratortests.h \
    source/data/intdecoratortests.h \
    source/data/stringdecoratortests.h \
    source/testsuite.h
