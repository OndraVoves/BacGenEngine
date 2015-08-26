#-------------------------------------------------
#
# Project created by QtCreator 2011-08-30T17:13:01
#
#-------------------------------------------------

TARGET = PMaterialAssetEditWidget
TEMPLATE = lib

DEFINES += PMATERIALASSETEDITWIDGET_LIBRARY

SOURCES += pmaterialasseteditwidget.cpp \
    pmaterialasset.cpp

HEADERS += pmaterialasseteditwidget.h\
        PMaterialAssetEditWidget_global.h \
    pmaterialasset.h

LIBS += -lBTextureAsset -lBMaterialAsset

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE93DFD4A
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PMaterialAssetEditWidget.dll
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
    pmaterialasset.ui
