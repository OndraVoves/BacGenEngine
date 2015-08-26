#-------------------------------------------------
#
# Project created by QtCreator 2011-08-17T15:48:21
#
#-------------------------------------------------

TARGET = PImageAssetHelper
TEMPLATE = lib

DEFINES += PIMAGEASSETHELPER_LIBRARY

SOURCES += pimageassethelper.cpp

HEADERS += pimageassethelper.h\
        PImageAssetHelper_global.h

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xED3B9BE1
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PImageAssetHelper.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
