#-------------------------------------------------
#
# Project created by QtCreator 2011-07-26T11:03:59
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = PlaygroundSDK
TEMPLATE = lib

LIBS += -lbackgenengine -lboxe-core -lGLEW -lSDL -lBTransformationComponent

DEFINES += PLAYGROUNDSDK_LIBRARY

INCLUDEPATH += ../../modules/includes/ \
               ../../engine/ \
               ../../../BoxE/core/

LIBS += -L../../engine/lib \
        -L../../../BoxE/core/lib \
        -L../../modules/libs/

SOURCES += \
           src/pactualproject.cpp \
           src/pmyaction.cpp \
    src/pcomponentproperties.cpp \
    src/pmodulessystem.cpp \
    src/pcomponentpropertiesmodule.cpp \
    src/passeteditwidget.cpp \
    src/psettingtabwidget.cpp \
    src/passeteditwidgetmodule.cpp \
    src/psettingmodule.cpp \
    src/pdockwidget.cpp \
    src/passetitemhelpermodule.cpp \
    src/pcomponenttoolbar.cpp \
    src/pcomponenttoolbarmodule.cpp\
    src/pscenedockwidget.cpp \
    src/pbgeglwidget.cpp \
    ../../modules/renderer/opengl/bopenglrenderer.cpp \
    ../../modules/renderer/opengl/bopengltexture.cpp \
    ../../modules/renderer/opengl/bopenglframebuffer.cpp \
    src/beditorcameracomponent.cpp\
    src/pscrollcomponentswidget.cpp


HEADERS += PlaygroundSDK_global.h \
        include/pactualproject.h \
        include/pmyaction.h \
    include/modulesheader.h \
    include/pcomponentproperties.h \
    include/pmodulessystem.h \
    include/pcomponentpropertiesmodule.h \
    include/passeteditwidget.h \
    include/psettingtabwidget.h \
    include/passeteditwidgetmodule.h \
    include/psettingmodule.h \
    include/pdockwidget.h \
    include/passetitemhelpermodule.h \
    include/pcomponenttoolbar.h \
    include/pcomponenttoolbarmodule.h\
    include/pscenedockwidget.h \
    include/pbgeglwidget.h\
    ../../modules/renderer/opengl/bopenglrenderer.h \
    ../../modules/renderer/opengl/bopengltexture.h \
    ../../modules/renderer/opengl/bopenglframebuffer.h \
    include/beditorcameracomponent.h\
    include/pscrollcomponentswidget.h

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEFB2B04E
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PlaygroundSDK.dll
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
