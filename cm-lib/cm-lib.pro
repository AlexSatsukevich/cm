include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT -= gui
QT += sql network xml

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

TARGET = cm-lib
TEMPLATE = lib

CONFIG += c++14

DEFINES += CMLIB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += source

SOURCES += source/models/client.cpp \
    source/controllers/commandcontroller.cpp \
    source/controllers/databasecontroller.cpp \
    source/controllers/mastercontroller.cpp \
    source/data/datadecorator.cpp \
    source/data/datetimedecorator.cpp \
    source/data/dropdown.cpp \
    source/data/dropdownvalue.cpp \
    source/data/entity.cpp \
    source/data/entitycollection.cpp \
    source/data/enumeratordecorator.cpp \
    source/data/intdecorator.cpp \
    source/data/stringdecorator.cpp \
    source/framework/command.cpp \
    source/framework/objectfactory.cpp \
    source/models/address.cpp \
    source/models/appointment.cpp \
    source/models/clientsearch.cpp \
    source/models/contact.cpp \
    source/networking/networkaccessmanager.cpp \
    source/networking/webrequest.cpp \
    source/rss/rsschannel.cpp \
    source/rss/rssimage.cpp \
    source/rss/rssitem.cpp \
    source/utilities/xmlhelper.cpp

HEADERS += \
    source/cm-lib_global.h \
    source/controllers/commandcontroller.h \
    source/controllers/databasecontroller.h \
    source/controllers/icommandcontroller.h \
    source/controllers/idatabasecontroller.h \
    source/controllers/inavigationcontroller.h \
    source/controllers/mastercontroller.h \
    source/controllers/navigationcontroller.h \
    source/data/datadecorator.h \
    source/data/datetimedecorator.h \
    source/data/dropdown.h \
    source/data/dropdownvalue.h \
    source/data/entity.h \
    source/data/entitycollection.h \
    source/data/enumeratordecorator.h \
    source/data/intdecorator.h \
    source/data/stringdecorator.h \
    source/framework/command.h \
    source/framework/iobjectfactory.h \
    source/framework/objectfactory.h \
    source/models/address.h \
    source/models/appointment.h \
    source/models/client.h \
    source/models/clientsearch.h \
    source/models/contact.h \
    source/networking/inetworkaccessmanager.h \
    source/networking/iwebrequest.h \
    source/networking/networkaccessmanager.h \
    source/networking/webrequest.h \
    source/rss/rsschannel.h \
    source/rss/rssimage.h \
    source/rss/rssitem.h \
    source/utilities/xmlhelper.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
