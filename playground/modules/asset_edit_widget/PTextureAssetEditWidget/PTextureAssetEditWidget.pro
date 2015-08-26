#-------------------------------------------------
#
# Project created by QtCreator 2011-08-30T15:14:45
#
#-------------------------------------------------

TARGET = PTextureAssetEditWidget
TEMPLATE = lib

DEFINES += PTEXTUREASSETEDITWIDGET_LIBRARY

SOURCES += ptextureasseteditwidget.cpp \
    ptextureasset.cpp

HEADERS += ptextureasseteditwidget.h\
        PTextureAssetEditWidget_global.h \
    ptextureasset.h

LIBS += -lBTextureAsset

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE8FA8923
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PTextureAssetEditWidget.dll
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
    ptextureasset.ui
