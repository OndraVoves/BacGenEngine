/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
    public:
        QAction *actionSetting;
        QAction *actionSettings;
        QAction *actionExit;
        QAction *actionNewProject;
        QAction *actionOpenProject;
        QAction *actionAbout_Qt;
        QAction *actionCloseProject;
        QAction *actionSaveProject;
        QAction *actionProjectSetting;
        QAction *actionCreateNewViewport;
        QWidget *centralWidget;
        QMenuBar *menuBar;
        QMenu *menu_File;
        QMenu *menu_Settings;
        QMenu *menu_Help;
        QMenu *menuScene;
        QMenu *menuObject;
        QMenu *menuComponent;
        QMenu *menuViewport;
        QMenu *menuAssets;

        void setupUi ( QMainWindow *MainWindow ) {
            if ( MainWindow->objectName().isEmpty() ) {
                MainWindow->setObjectName ( QString::fromUtf8 ( "MainWindow" ) );
            }
            MainWindow->resize ( 573, 177 );
            actionSetting = new QAction ( MainWindow );
            actionSetting->setObjectName ( QString::fromUtf8 ( "actionSetting" ) );
            QIcon icon;
            icon.addFile ( QString::fromUtf8 ( ":/images/preferences-system.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionSetting->setIcon ( icon );
            actionSettings = new QAction ( MainWindow );
            actionSettings->setObjectName ( QString::fromUtf8 ( "actionSettings" ) );
            actionSettings->setIcon ( icon );
            actionExit = new QAction ( MainWindow );
            actionExit->setObjectName ( QString::fromUtf8 ( "actionExit" ) );
            QIcon icon1;
            icon1.addFile ( QString::fromUtf8 ( ":/images/application-exit.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionExit->setIcon ( icon1 );
            actionNewProject = new QAction ( MainWindow );
            actionNewProject->setObjectName ( QString::fromUtf8 ( "actionNewProject" ) );
            QIcon icon2;
            icon2.addFile ( QString::fromUtf8 ( ":/images/game-new.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionNewProject->setIcon ( icon2 );
            actionOpenProject = new QAction ( MainWindow );
            actionOpenProject->setObjectName ( QString::fromUtf8 ( "actionOpenProject" ) );
            QIcon icon3;
            icon3.addFile ( QString::fromUtf8 ( ":/images/game-open.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionOpenProject->setIcon ( icon3 );
            actionAbout_Qt = new QAction ( MainWindow );
            actionAbout_Qt->setObjectName ( QString::fromUtf8 ( "actionAbout_Qt" ) );
            actionCloseProject = new QAction ( MainWindow );
            actionCloseProject->setObjectName ( QString::fromUtf8 ( "actionCloseProject" ) );
            actionSaveProject = new QAction ( MainWindow );
            actionSaveProject->setObjectName ( QString::fromUtf8 ( "actionSaveProject" ) );
            QIcon icon4;
            icon4.addFile ( QString::fromUtf8 ( ":/images/game-save.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionSaveProject->setIcon ( icon4 );
            actionProjectSetting = new QAction ( MainWindow );
            actionProjectSetting->setObjectName ( QString::fromUtf8 ( "actionProjectSetting" ) );
            QIcon icon5;
            icon5.addFile ( QString::fromUtf8 ( ":/images/game-configure.png" ), QSize(), QIcon::Normal, QIcon::Off );
            actionProjectSetting->setIcon ( icon5 );
            actionCreateNewViewport = new QAction ( MainWindow );
            actionCreateNewViewport->setObjectName ( QString::fromUtf8 ( "actionCreateNewViewport" ) );
            centralWidget = new QWidget ( MainWindow );
            centralWidget->setObjectName ( QString::fromUtf8 ( "centralWidget" ) );
            MainWindow->setCentralWidget ( centralWidget );
            menuBar = new QMenuBar ( MainWindow );
            menuBar->setObjectName ( QString::fromUtf8 ( "menuBar" ) );
            menuBar->setGeometry ( QRect ( 0, 0, 573, 23 ) );
            menu_File = new QMenu ( menuBar );
            menu_File->setObjectName ( QString::fromUtf8 ( "menu_File" ) );
            menu_Settings = new QMenu ( menuBar );
            menu_Settings->setObjectName ( QString::fromUtf8 ( "menu_Settings" ) );
            menu_Help = new QMenu ( menuBar );
            menu_Help->setObjectName ( QString::fromUtf8 ( "menu_Help" ) );
            menuScene = new QMenu ( menuBar );
            menuScene->setObjectName ( QString::fromUtf8 ( "menuScene" ) );
            menuScene->setEnabled ( false );
            menuObject = new QMenu ( menuBar );
            menuObject->setObjectName ( QString::fromUtf8 ( "menuObject" ) );
            menuObject->setEnabled ( false );
            menuComponent = new QMenu ( menuBar );
            menuComponent->setObjectName ( QString::fromUtf8 ( "menuComponent" ) );
            menuComponent->setEnabled ( false );
            menuViewport = new QMenu ( menuBar );
            menuViewport->setObjectName ( QString::fromUtf8 ( "menuViewport" ) );
            menuAssets = new QMenu ( menuBar );
            menuAssets->setObjectName ( QString::fromUtf8 ( "menuAssets" ) );
            MainWindow->setMenuBar ( menuBar );

            menuBar->addAction ( menu_File->menuAction() );
            menuBar->addAction ( menuAssets->menuAction() );
            menuBar->addAction ( menuScene->menuAction() );
            menuBar->addAction ( menuViewport->menuAction() );
            menuBar->addAction ( menuObject->menuAction() );
            menuBar->addAction ( menuComponent->menuAction() );
            menuBar->addAction ( menu_Settings->menuAction() );
            menuBar->addAction ( menu_Help->menuAction() );
            menu_File->addAction ( actionNewProject );
            menu_File->addAction ( actionOpenProject );
            menu_File->addAction ( actionSaveProject );
            menu_File->addAction ( actionProjectSetting );
            menu_File->addAction ( actionCloseProject );
            menu_File->addSeparator();
            menu_File->addAction ( actionExit );
            menu_Settings->addAction ( actionSetting );
            menu_Help->addAction ( actionAbout_Qt );
            menuViewport->addAction ( actionCreateNewViewport );

            retranslateUi ( MainWindow );
            QObject::connect ( actionNewProject, SIGNAL ( activated() ), MainWindow, SLOT ( newProject() ) );
            QObject::connect ( actionExit, SIGNAL ( activated() ), MainWindow, SLOT ( quit() ) );
            QObject::connect ( actionAbout_Qt, SIGNAL ( activated() ), MainWindow, SLOT ( aboutQt() ) );
            QObject::connect ( actionSetting, SIGNAL ( activated() ), MainWindow, SLOT ( showModulesSettingsDialog() ) );

            QMetaObject::connectSlotsByName ( MainWindow );
        } // setupUi

        void retranslateUi ( QMainWindow *MainWindow ) {
            MainWindow->setWindowTitle ( QApplication::translate ( "MainWindow", "Playground", 0, QApplication::UnicodeUTF8 ) );
            actionSetting->setText ( QApplication::translate ( "MainWindow", "&Settings", 0, QApplication::UnicodeUTF8 ) );
            actionSettings->setText ( QApplication::translate ( "MainWindow", "&Settings", 0, QApplication::UnicodeUTF8 ) );
            actionExit->setText ( QApplication::translate ( "MainWindow", "&Exit", 0, QApplication::UnicodeUTF8 ) );
            actionExit->setShortcut ( QApplication::translate ( "MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8 ) );
            actionNewProject->setText ( QApplication::translate ( "MainWindow", "&New project", 0, QApplication::UnicodeUTF8 ) );
            actionOpenProject->setText ( QApplication::translate ( "MainWindow", "&Open project", 0, QApplication::UnicodeUTF8 ) );
            actionAbout_Qt->setText ( QApplication::translate ( "MainWindow", "About &Qt", 0, QApplication::UnicodeUTF8 ) );
            actionCloseProject->setText ( QApplication::translate ( "MainWindow", "&Close project", 0, QApplication::UnicodeUTF8 ) );
            actionSaveProject->setText ( QApplication::translate ( "MainWindow", "Save project", 0, QApplication::UnicodeUTF8 ) );
            actionSaveProject->setShortcut ( QApplication::translate ( "MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8 ) );
            actionProjectSetting->setText ( QApplication::translate ( "MainWindow", "Project setting", 0, QApplication::UnicodeUTF8 ) );
            actionCreateNewViewport->setText ( QApplication::translate ( "MainWindow", "Create new", 0, QApplication::UnicodeUTF8 ) );
            menu_File->setTitle ( QApplication::translate ( "MainWindow", "&File", 0, QApplication::UnicodeUTF8 ) );
            menu_Settings->setTitle ( QApplication::translate ( "MainWindow", "&Tools", 0, QApplication::UnicodeUTF8 ) );
            menu_Help->setTitle ( QApplication::translate ( "MainWindow", "&Help", 0, QApplication::UnicodeUTF8 ) );
            menuScene->setTitle ( QApplication::translate ( "MainWindow", "&Scene", 0, QApplication::UnicodeUTF8 ) );
            menuObject->setTitle ( QApplication::translate ( "MainWindow", "&Object", 0, QApplication::UnicodeUTF8 ) );
            menuComponent->setTitle ( QApplication::translate ( "MainWindow", "&Component", 0, QApplication::UnicodeUTF8 ) );
            menuViewport->setTitle ( QApplication::translate ( "MainWindow", "Viewport", 0, QApplication::UnicodeUTF8 ) );
            menuAssets->setTitle ( QApplication::translate ( "MainWindow", "Assets", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
