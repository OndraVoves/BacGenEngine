#-------------------------------------------------
#
# Project created by QtCreator 2011-07-30T21:29:27
#
#-------------------------------------------------

TARGET = Simple
TEMPLATE = lib

DEFINES += SIMPLE_LIBRARY

SOURCES += simple.cpp

HEADERS += simple.h\
        Simple_global.h

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xED722294
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Simple.dll
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
