#-------------------------------------------------
#
# Project created by QtCreator 2011-07-24T13:00:14
#
#-------------------------------------------------

QT       += core gui

LIBS += -lPlaygroundSDK -lbackgenengine -lboxe-core -lGLEW -lSDL -lBTransformationComponent

TARGET = Playground
TEMPLATE = app

INCLUDEPATH += ../../modules/includes/ \
               ../../engine/ \
               ../../../BoxE/core/

LIBS += -L../../engine/lib \
        -L../../../BoxE/core/lib \
        -L../../modules/libs/ \
        -L../PlaygroundSDK/

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/project/newprojectdialog.cpp \
    src/scenes/psceneslistwidget.cpp \
    src/scenes/sceneeditdialog.cpp \
    src/objects/objectstreewidget.cpp \
    src/objects/pobjectwidget.cpp \
    src/scenes/layersmanagerdialog.cpp \
    src/scenes/ptagsmanagerdialog.cpp \
    src/modules/pmodulessettingsdialog.cpp \
    src/modules/pmodulessettings.cpp \
    src/assets/passetstreewidget.cpp \
    src/assets/pdefaulteditassetwidget.cpp \
    src/assets/passetsettings.cpp \
    src/assets/asseteditdockwidget.cpp \
    pgeneralsettings.cpp \
    src/components/pcomponentswidget.cpp \
    pprojectsettingdialog.cpp \
    ../../modules/renderer/opengl/bopenglrenderer.cpp \
    ../../modules/renderer/opengl/bopengltexture.cpp \
    ../../modules/renderer/opengl/bopenglframebuffer.cpp \


HEADERS  += include/mainwindow.h \
    include/project/newprojectdialog.h \
    include/scenes/psceneslistwidget.h \
    include/scenes/sceneeditdialog.h \
    include/objects/objectstreewidget.h \
    include/objects/pobjectwidget.h \
    include/scenes/layersmanagerdialog.h \
    include/scenes/ptagsmanagerdialog.h \
    include/modules/pmodulessettingsdialog.h \
    include/modules/pmodulessettings.h \
    include/assets/passetstreewidget.h \
    include/assets/pdefaulteditassetwidget.h \
    include/assets/passetsettings.h \
    include/assets/asseteditdockwidget.h \
    pgeneralsettings.h \
    include/components/pcomponentswidget.h \
    pprojectsettingdialog.h\
    ../../modules/renderer/opengl/bopenglrenderer.h \
    ../../modules/renderer/opengl/bopengltexture.h \
    ../../modules/renderer/opengl/bopenglframebuffer.h \

FORMS    += ui/mainwindow.ui \
    ui/project/newprojectdialog.ui \
    ui/scenes/sceneeditdialog.ui \
    ui/scenes/layersmanagerdialog.ui \
    ui/scenes/ptagsmanagerdialog.ui \
    ui/modules/pmodulessettingsdialog.ui \
    ui/modules/pmodulessettings.ui \
    ui/assets/pdefaulteditassetwidget.ui \
    ui/assets/passetsettings.ui \
    ui/assets/asseteditdockwidget.ui \
    pgeneralsettings.ui \
    ui/components/pcomponentswidget.ui \
    pprojectsettingdialog.ui

RESOURCES += \
    playground.qrc
