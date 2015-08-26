#-------------------------------------------------
#
# Project created by QtCreator 2011-08-18T14:01:22
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = PTransformationToolBar
TEMPLATE = lib

DEFINES += PTRANSFORMATIONTOOLBAR_LIBRARY

SOURCES += ptransformationtoolbar.cpp

HEADERS += ptransformationtoolbar.h\
        PTransformationToolBar_global.h

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE941BDFB
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PTransformationToolBar.dll
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
