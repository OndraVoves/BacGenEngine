#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bscene.h>

#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QCloseEvent>
#include <QDockWidget>
#include <QDir>
#include <QVBoxLayout>


#include "../include/project/newprojectdialog.h"
#include "../include/scenes/psceneslistwidget.h"
#include "../include/objects/objectstreewidget.h"
#include "../include/objects/pobjectwidget.h"

#include "../include/modules/pmodulessettingsdialog.h"
#include "../include/assets/passetstreewidget.h"

#include "../pprojectsettingdialog.h"


#include <PlaygroundSDK/pmodulessystem.h>
#include <PlaygroundSDK/pscenedockwidget.h>

MainWindow::MainWindow ( QWidget *parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow ), ActualProject ( &ModuleSystem ) {
    ui->setupUi ( this );

    // Actual project
    connect ( &ActualProject,         SIGNAL ( projectOpened() ), this,           SLOT ( projectOpened() ) );
    connect ( &ActualProject,         SIGNAL ( projectClosed() ), this,           SLOT ( projectClosed() ) );
    connect ( &ActualProject,         SIGNAL ( sceneOpened ( BackGenEngine::BScene * ) ) ,
              this,                   SLOT (   sceneOpened ( BackGenEngine::BScene * ) ) );

    //Actions
    connect ( ui->actionCloseProject, SIGNAL ( activated()     ), &ActualProject, SLOT ( closeProject()  ) );
    connect ( ui->actionOpenProject,  SIGNAL ( activated()     ), this,           SLOT ( openProject()   ) );
    connect ( ui->actionSaveProject, SIGNAL ( activated() ), &ActualProject, SLOT ( maybeSave() ) );
    connect ( ui->actionProjectSetting, SIGNAL ( activated( ) ), this, SLOT ( projectSetting() ) );
    connect ( ui->actionCreateNewViewport, SIGNAL ( activated() ), this, SLOT ( newViewport() ) );

    setCentralWidget ( 0 );
    setDockNestingEnabled ( true );

    readSettings();

    loadPlaygroundModules();

    ActualProject.open ( "/home/backgen/pokusgame/" );
}

MainWindow::~MainWindow() {
    delete ui;
}

QMenu *MainWindow::assetMenu() {
    return ui->menuAssets;
}

QMenu *MainWindow::sceneMenu() {
    return ui->menuScene;
}

QMenu *MainWindow::objectMenu() {
    return ui->menuObject;
}

QMenu *MainWindow::componentMenu() {
    return ui->menuComponent;
}

void MainWindow::closeEvent ( QCloseEvent *e ) {
    writeSettings();

    QHash<QString, PSceneDockWidget *>::Iterator it = ViewportsHash.begin();
    while ( it != ViewportsHash.end() ) {
        disconnect ( ( *it ), SIGNAL ( destroyed ( QObject * ) ), this, SLOT ( viewportDestroyed ( QObject * ) ) );
        delete ( *it );
        it = ViewportsHash.erase ( it );
    }

    ActualProject.closeProject();
    e->accept();
}

void MainWindow::projectOpened() {
    setWindowTitle ( QString ( "%1 - Playground" ).arg ( ActualProject.project()->getName().constData() ) );

    // Scenes
    pcScenesDockWidget = new QDockWidget ( "Scenes" );
    pcScenesDockWidget->setObjectName ( "ScenesDockWidget" );

    PScenesListWidget *scene_list_widget = new PScenesListWidget ( this, &ActualProject );
    scene_list_widget->fillSceneList();
    pcScenesDockWidget->setWidget ( scene_list_widget );

    //Assets.
    pcAssetDockWidget = new QDockWidget ( "Assets" );
    pcAssetDockWidget->setObjectName ( "AssetDockWidget" );

    PAssetsTreeWidget *assets_tree_widget = new PAssetsTreeWidget ( this, &ActualProject );
    pcAssetDockWidget->setWidget ( assets_tree_widget );

    // Objects tree.
    pcObjectsTreeDockWidget = new QDockWidget ( tr ( "Objects tree" ) );
    pcObjectsTreeDockWidget->setObjectName ( "ObjectsTreeDockWidget" );
    ObjectsTreeWidget *pc_objects_tree_widget = new ObjectsTreeWidget ( this, &ActualProject );
    pcObjectsTreeDockWidget->setWidget ( pc_objects_tree_widget );

    // Object.
    pcObjectDocWidget = new QDockWidget ( tr ( "Object" ) );
    pcObjectDocWidget->setObjectName ( "ObjectDockWidget" );
    PObjectWidget *pc_object_widget = new PObjectWidget ( this, &ActualProject );
    pcObjectDocWidget->setWidget ( pc_object_widget );

    // Dock widget.
    addDockWidget ( Qt::LeftDockWidgetArea, pcScenesDockWidget );
    addDockWidget ( Qt::RightDockWidgetArea, pcObjectsTreeDockWidget );
    addDockWidget ( Qt::RightDockWidgetArea, pcObjectDocWidget );
    addDockWidget ( Qt::RightDockWidgetArea, pcAssetDockWidget );

    tabifyDockWidget ( pcScenesDockWidget, pcAssetDockWidget );
    tabifyDockWidget ( pcAssetDockWidget, pcObjectsTreeDockWidget );

    QSettings setting;
    //restoreGeometry ( setting.value ( "MainWindow/Geometry" ).toByteArray() );

    int count = setting.value ( "Viewports/count", 0 ).toInt();
    if ( count ) {
        do {
            newViewport();
            count--;
        } while ( count != 0 );
    }

    restoreState (  setting.value ( "MainWindow/State" ).toByteArray() );
}

void MainWindow::projectClosed() {
    setWindowTitle ( "Playground" );

    delete pcScenesDockWidget;
    pcScenesDockWidget = 0;

    delete pcAssetDockWidget;
    pcAssetDockWidget = 0;

    delete pcObjectsTreeDockWidget;
    pcObjectsTreeDockWidget = 0;

    delete pcObjectDocWidget;
    pcObjectDocWidget = 0;
}

void MainWindow::openProject() {
    if ( ActualProject.isModifed() ) {
        // save
    }

    if ( ActualProject.project() ) {
        ActualProject.close();
    }

    ActualProject.open ( QFileDialog::getExistingDirectory ( this, tr ( "Select project directory." ) ) );
}

void MainWindow::sceneOpened ( BackGenEngine::BScene *pc_scene ) {
    if ( pc_scene ) {
        assetMenu()->setEnabled ( true );
        sceneMenu()->setEnabled ( true );
        objectMenu()->setEnabled ( true );
        componentMenu()->setEnabled ( true );

        setWindowTitle ( QString (  " %1 - %2 - Playground" ).arg ( pc_scene->getName().constData() ).arg ( ActualProject.project()->getName().constData() ) );
    }  else {
        assetMenu()->setDisabled ( true );
        sceneMenu()->setDisabled ( true );
        objectMenu()->setDisabled ( true );
        componentMenu()->setDisabled ( true );

        setWindowTitle ( QString ( "%1 - Playground" ).arg ( ActualProject.project()->getName().constData() ) );
    }
}

void MainWindow::showModulesSettingsDialog() {
    PModulesSettingsDialog dialog ( this, &ActualProject, this );
    dialog.exec();
}


void MainWindow::newProject() {
    if ( ActualProject.isModifed() ) {
        int ret = QMessageBox::question ( this, tr ( "Actual project is modifed" ), tr ( "Actual project is modifed, Save it? " ),
                                          QMessageBox::Save | QMessageBox::Cancel |  QMessageBox::Discard );
        switch ( ret ) {
            case QMessageBox::Save:
                break;
            case QMessageBox::Cancel:
                return;
                break;
            case QMessageBox::Discard:
                break;
        }

    }

    NewProjectDialog dialog ( &ActualProject, this );
    dialog.exec();
}

void MainWindow::projectSetting() {
    PProjectSettingDialog dialog ( &ActualProject, this );
    dialog.exec();
}

void MainWindow::quit() {
    if ( ActualProject.isModifed() ) {
        int ret = QMessageBox::question ( this, tr ( "Actual project is modifed" ), tr ( "Actual project is modifed, Save it? " ),
                                          QMessageBox::Save | QMessageBox::Cancel |  QMessageBox::Discard );
        switch ( ret ) {
            case QMessageBox::Save:
                ActualProject.saveProject();
                break;
            case QMessageBox::Cancel:
                return;
                break;
            case QMessageBox::Discard:
                break;
        }

    }

    close();
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt ( this );
}

void MainWindow::writeSettings() {
    QSettings setting;

    setting.beginGroup ( "MainWindow" );
    setting.setValue ( "Geometry", saveGeometry() );
    setting.setValue ( "State", saveState() );
    setting.endGroup();

    setting.beginGroup ( "Viewports" );
    setting.setValue ( "count", ViewportsHash.count() );
    setting.endGroup();
}

inline QTabWidget::TabPosition int2TabPositiom ( int i ) {
    switch ( i ) {
        default:
        case 0:
            return QTabWidget::North;

        case 1:
            return QTabWidget::South;

        case 2:
            return QTabWidget::West;

        case 3:
            return QTabWidget::East;
    }
}

void MainWindow::readSettings() {
    QSettings setting;
    restoreGeometry ( setting.value ( "MainWindow/Geometry" ).toByteArray() );
    restoreState (  setting.value ( "MainWindow/State" ).toByteArray() );

    setTabPosition ( Qt::AllDockWidgetAreas, int2TabPositiom ( setting.value ( "Dock/DockTabPosition", 0 ).toInt() ) );
}

void MainWindow::loadPlaygroundModules() {
    QString dir_path ( "./modules/" );
    QDir dir ( dir_path );
    QStringList files = dir.entryList ( QStringList ( "*.*" ) );


    QStringList::ConstIterator it = files.constBegin();
    QString actual_file;
    while ( it != files.constEnd() ) {
        actual_file = dir_path + ( *it );

        if ( QLibrary::isLibrary ( actual_file ) ) {
            ModuleSystem.loadModule ( actual_file );
        }

        ++it;
    }

}

void MainWindow::newViewport() {
    PSceneDockWidget *pc_new_viewport = new PSceneDockWidget ( &ActualProject );

    connect ( pc_new_viewport, SIGNAL ( destroyed ( QObject * ) ), this, SLOT ( viewportDestroyed ( QObject * ) ) );

    int i = 0;
    while ( ViewportsHash.contains ( QString ( "Viewport%1" ).arg ( i ) ) ) {
        i++;
    }
    QString str = QString ( "Viewport%1" ).arg ( i );

    pc_new_viewport->setObjectName ( str );

    ViewportsHash.insert ( str, pc_new_viewport );

    addDockWidget ( Qt::TopDockWidgetArea, pc_new_viewport );
}

void MainWindow::viewportDestroyed ( QObject *pc_object ) {
    ViewportsHash.remove ( pc_object->objectName() );

    int i = 0;
    QHash<QString, PSceneDockWidget *>::Iterator it = ViewportsHash.begin();
    while ( it != ViewportsHash.end() ) {
        PSceneDockWidget *pc_new_viewport = ( *it );

        pc_new_viewport->setObjectName ( QString ( "Viewport%1" ).arg ( i ) );

        ViewportsHash.insert ( pc_new_viewport->objectName(), pc_new_viewport );
        it = ViewportsHash.erase ( it );
        i++;
    }
}
