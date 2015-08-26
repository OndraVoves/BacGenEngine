#-------------------------------------------------
#
# Project created by QtCreator 2011-08-01T18:10:28
#
#-------------------------------------------------

TARGET = PImageAssetEditWidget
TEMPLATE = lib

DEFINES += PIMAGEASSETEDITWIDGET_LIBRARY

SOURCES += \
    pimage.cpp

HEADERS +=\
        PImageAssetEditWidget_global.h \
    pimage.h

INCLUDEPATH += ../../../../modules/includes/ \
               ../../../../engine/ \
               ../../../../../BoxE/core/

LIBS += -L../../../../engine/lib \
        -L../../../../../BoxE/core/lib \
        -L../../../../modules/libs/ \
        -L../../PlaygroundSDK/

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xED3AAF81
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PImageAssetEditWidget.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

FORMS += \
    pimage.ui
