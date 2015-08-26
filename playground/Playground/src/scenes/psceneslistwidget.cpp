#include "../../include/scenes/psceneslistwidget.h"

#include "./include/mainwindow.h"
#include "./include/scenes/sceneeditdialog.h"
#include "./include/scenes/layersmanagerdialog.h"
#include "./include/scenes/ptagsmanagerdialog.h"


#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QDir>

#include <BackGenEngine/bscene.h>
#include <BackGenEngine/bproject.h>

#include <PlaygroundSDK/pscenedockwidget.h>

PScenesListWidget::PScenesListWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent ) :
    QListWidget ( parent ), pcMainWindow ( main_window ), ActualProject ( actual_project ), pcSceneManager ( & actual_project->project()->getSceneManager() ) {

    createActions();

    setIconSize ( QSize ( 32, 32 ) );

    connect ( this, SIGNAL ( itemDoubleClicked ( QListWidgetItem * ) ), this, SLOT ( sceneDoubleClicked ( QListWidgetItem * ) ) );
}

PScenesListWidget::~PScenesListWidget() {
    deleteActions();
}

void PScenesListWidget::fillSceneList() {
    clear();

    BackGenEngine::BSceneManager::scene_hash_t::ConstIterator it = pcSceneManager->getSceneHash().constBegin();
    //QListWidgetItem *new_item = 0;
    while ( it != pcSceneManager->getSceneHash().constEnd() ) {
        updateSceneItem ( ( *it ), new QListWidgetItem ( this ) );
        ++it;
    }
}


void PScenesListWidget::contextMenuEvent ( QContextMenuEvent *e ) {
    QMenu context_menu ( this );

    context_menu.addAction ( pcActionNewScene );

    if ( !selectedItems().isEmpty() ) {
        context_menu.addAction (  pcActionDeleteScene );
        context_menu.addAction (  pcActionEditScene );
    }

    context_menu.exec ( e->globalPos() );
}

void PScenesListWidget::createActions() {
    pcActionNewScene = new QAction ( QIcon ( ":/images/scene-add.png" ), tr ( "Create &new" ), this );
    connect ( pcActionNewScene, SIGNAL ( activated() ), this, SLOT ( addNewScene() ) );

    pcActionDeleteScene = new QAction ( QIcon ( ":/images/scene-remove.png" ), tr ( "&Delete selected" ), this );
    connect ( pcActionDeleteScene, SIGNAL ( activated() ), this, SLOT ( deleteSelectedScene( ) ) );

    pcActionEditScene = new QAction ( QIcon ( ":/images/scene-configure.png" ), tr ( "&Edit selected" ), this );
    connect ( pcActionEditScene, SIGNAL ( activated() ), this, SLOT ( editSelectedScene() ) );
}

void PScenesListWidget::deleteActions() {
    delete pcActionNewScene;
    pcActionNewScene = 0;

    delete pcActionDeleteScene;
    pcActionDeleteScene = 0;

    delete pcActionEditScene;
    pcActionEditScene = 0;
}

void PScenesListWidget::updateSceneItem ( BackGenEngine::BScene *pc_scene, QListWidgetItem *pc_item ) {
    pc_item->setText ( pc_scene->getName().constData() );
    pc_item->setIcon ( QIcon ( ":/images/scene.png" ) );
    pc_item->setData ( Qt::UserRole, qVariantFromValue ( ( void * ) pc_scene ) );
}

void PScenesListWidget::addNewScene() {
    QString scene_name ( "NewScene_1" );

    int i = 2;
    while ( pcSceneManager->containScene ( scene_name.toStdString().c_str() ) ) {
        scene_name = QString ( "NewScene_%1" ).arg ( i++ );
    }

    // TODO: logger
    BackGenEngine::BScene *pc_new_scene = new BackGenEngine::BScene ( ( BackGenEngine::BAbstractRenderer * ) ActualProject->getRenderer(),  ActualProject->logger() );
    pc_new_scene->setName ( scene_name.toStdString().c_str() );
    pcSceneManager->insertScene ( pc_new_scene );

    QListWidgetItem *pc_new_item = new QListWidgetItem ( this );
    updateSceneItem ( pc_new_scene, pc_new_item );

}


void PScenesListWidget::deleteSelectedScene() {
    QListWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BScene *pc_scene = ( BackGenEngine::BScene * ) pc_item->data ( Qt::UserRole ).value<void *>();

    int ret = QMessageBox::question ( this, tr ( "Do you really want..." ),
                                      tr ( "Do you really want to delete \"%1\" scene?" ).arg ( pc_scene->getName().constData() ),
                                      QMessageBox::Ok | QMessageBox::Cancel );

    if ( ret == QMessageBox::Cancel ) {
        return;
    }

    if ( pc_scene == ActualProject->actualScene() ) {
        ActualProject->setActualScene ( 0 );
        pcMainWindow->sceneMenu()->setDisabled ( true );
    }

    pcSceneManager->removeScene ( pc_scene );

    // Remove file.
    QString scene_filename = QString ( "%1data/scenes/%2.scene" ).arg ( ActualProject->project()->getBaseDir().constData() )
                             .arg ( pc_scene->getName().constData() );
    if ( QFile::exists ( scene_filename ) ) {
        QFile::remove ( scene_filename );
    }

    delete pc_item;
    delete pc_scene;
}

void PScenesListWidget::editSelectedScene() {
    QListWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BScene *pc_scene = ( BackGenEngine::BScene * ) pc_item->data ( Qt::UserRole ).value<void *>();

    SceneEditDialog dialog ( ActualProject, pc_scene, this );

    if ( dialog.exec() ) {
        updateSceneItem ( pc_scene, pc_item );
    }
}

void PScenesListWidget::sceneDoubleClicked ( QListWidgetItem *pc_item ) {
    BackGenEngine::BScene *pc_scene = ( BackGenEngine::BScene * ) pc_item->data ( Qt::UserRole ).value<void *>();

    ActualProject->setActualScene ( pc_scene );

    //PSceneDockWidget *pc_dock = new PSceneDockWidget ( pc_scene, ActualProject, this );
    //pcMainWindow->addDockWidget ( Qt::TopDockWidgetArea, pc_dock );
}
