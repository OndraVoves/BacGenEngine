#-------------------------------------------------
#
# Project created by QtCreator 2011-08-30T17:53:55
#
#-------------------------------------------------

TARGET = PMeshRendererProperties
TEMPLATE = lib

DEFINES += PMESHRENDERERPROPERTIES_LIBRARY

SOURCES += pmeshrendererproperties.cpp \
    pmeshrenderer.cpp

HEADERS += pmeshrendererproperties.h\
        PMeshRendererProperties_global.h \
    pmeshrenderer.h

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -lBMaterialAsset -lBMeshRendererComponent

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE00A27E6
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PMeshRendererProperties.dll
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
    pmeshrenderer.ui
