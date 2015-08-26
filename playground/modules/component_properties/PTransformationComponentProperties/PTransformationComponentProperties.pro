#-------------------------------------------------
#
# Project created by QtCreator 2011-08-17T22:57:48
#
#-------------------------------------------------

TARGET = PTransformationComponentProperties
TEMPLATE = lib

DEFINES += PTRANSFORMATIONCOMPONENTPROPERTIES_LIBRARY

SOURCES += \
    ptransformation.cpp

HEADERS +=\
        PTransformationComponentProperties_global.h \
    ptransformation.h


INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE77C0FC2
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PTransformationComponentProperties.dll
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

FORMS += \
    ptransformation.ui
