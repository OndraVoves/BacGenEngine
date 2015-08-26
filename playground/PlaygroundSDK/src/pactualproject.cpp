#include "../include/pactualproject.h"

#include <QMessageBox>
#include <QDebug>
#include <QMenu>
#include <QDir>
#include <QLibrary>

#include <bopenglrenderer.h>

#include <QGLWidget>

#include <BackGenEngine/bdynamicmodulesystem.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bassetmanager.h>
#include <BackGenEngine/bscene.h>

PActualProject::PActualProject ( PModulesSystem *pc_module_system, QObject *parent ) :
    QObject ( parent ), Project ( 0 ), ActualScene ( 0 ), pcActiveObject ( 0 ), pcModuleSystem ( pc_module_system ),
    Modifed ( false ), pcEditorLayer ( 0 ), pcComponentsScroll ( 0 ), pcActiveSceneDockWidget ( 0 )  {
}

PActualProject::~PActualProject () {
    if ( Project ) {
        delete Project;
    }
}

BOpenGLRenderer *PActualProject::getRenderer() {
    return pcRenderer;
}

BackGenEngine::BProject *PActualProject::project( ) {
    return Project;
}

bool PActualProject::create ( const QString &name, const QString &dir ) {
    if ( Project ) {
        close();
    }

    // Check "/"
    QString project_dir ( dir );
    if ( !project_dir.endsWith ( "/" ) ) {
        project_dir.append ( "/" );
    }

    // todo project distribution prasarna...
    pcLogger = new BackGenEngine::BLogger();

    BackGenEngine::BDynamicModuleSystem *pc_module_system = new BackGenEngine::BDynamicModuleSystem ( pcLogger );
    pc_module_system->loadModule ( "../../modules/component/simple/BSimpleComponent" );
    pc_module_system->loadModule ( "../../modules/asset/image/BImageAsset" );

    Project = new BackGenEngine::BProject ( 0, pc_module_system, pcLogger );
    Project->setBaseDir ( dir.toStdString().c_str() );
    Project->setName ( name.toStdString().c_str() );


    // Save
    BoxE::Core::BFile project_file ( project_dir.append ( "project.cfg" ).toStdString().c_str() );
    project_file.open ( BoxE::Core::BIODevice::WriteOnly );
    BoxE::Core::BByteArray data ( Project->toByteArray() );
    project_file.write ( data.constData(), data.size() );
    project_file.close();


    emit projectOpened();
    setModified ( true );
}

bool PActualProject::open ( const QString &dir ) {
    if ( Project ) {
        close();
    }

    // Check "/"
    QString project_dir ( dir );
    if ( !project_dir.endsWith ( "/" ) ) {
        project_dir.append ( "/" );
    }


    pcLogger = new BackGenEngine::BLogger();

    BackGenEngine::BDynamicModuleSystem *pc_module_system = new BackGenEngine::BDynamicModuleSystem ( pcLogger );

    QString dir_path ( "./bgevm/modules/" );
    QDir mod_dir ( dir_path );
    QStringList files = mod_dir.entryList ( QStringList ( "*.*" ) );


    QStringList::ConstIterator it = files.constBegin();
    QString actual_file;
    while ( it != files.constEnd() ) {
        actual_file = dir_path + ( *it );

        if ( QLibrary::isLibrary ( actual_file ) ) {
            pc_module_system->loadModule ( actual_file.toStdString().c_str() );
        }

        ++it;
    }

    Project = new BackGenEngine::BProject ( 0, pc_module_system, pcLogger );
    Project->setBaseDir ( dir.toStdString().c_str() );

    // Load
    QByteArray data;

    QFile project_file ( QString ( project_dir ).append ( "project.cfg" ) );
    project_file.open ( QIODevice::ReadOnly );
    data = project_file.readAll();
    Project->fromByteArray ( BoxE::Core::BByteArray ( data.constData(), data.size() ) );
    project_file.close();

    pcRenderer = new BOpenGLRenderer ( pcLogger  );
    //pcCentralGL = new QGLWidget ( QGLFormat::defaultFormat()  );

    //asset
    QFile assets_file ( QString ( project_dir ).append ( "data/assets/assets_manager.cfg" ) );
    assets_file.open ( QIODevice::ReadOnly );
    data = assets_file.readAll();
    Project->getAssetManager().fromByteArray ( BoxE::Core::BByteArray ( data.constData(), data.size() ), pcRenderer );
    assets_file.close();

    //Scene
    QDir scene_dir ( QString ( project_dir ).append ( "data/scenes" ) );
    QStringList scene_files = scene_dir.entryList ( QStringList ( "*.scene" ) );
    QStringList::ConstIterator scene_it = scene_files.constBegin();
    QString actual_scene_file;
    while ( scene_it != scene_files.constEnd() ) {
        actual_scene_file = scene_dir.absoluteFilePath ( ( *scene_it ) );

        QFile scene_file ( actual_scene_file );
        scene_file.open ( QIODevice::ReadOnly );
        data = scene_file.readAll();

        BackGenEngine::BScene *pc_new_scene = new BackGenEngine::BScene ( pcRenderer, pcLogger );
        pc_new_scene->fromByteArray ( BoxE::Core::BByteArray ( data.constData(), data.size() ), Project->getModuleSystem(), &Project->getAssetManager() );
        scene_file.close();

        Project->getSceneManager().insertScene ( pc_new_scene );

        ++scene_it;
    }

    if ( pcEditorLayer ) {
        delete pcEditorLayer;
    }

    pcEditorLayer = new BackGenEngine::BLayer ( "__EDITOR__", BackGenEngine::BLayer::NORMAL, pcLogger );

    emit projectOpened();
}

void PActualProject::close() {
    if ( !project() ) {
        return;
    }

    setActualScene ( 0 );

    emit projectClosed();


    setModified ( false );

    delete Project;
    Project = 0;

    delete pcLogger;
}

void PActualProject::setModified ( bool modified ) {
    if ( Modifed != modified ) {
        Modifed = modified;
        emit projectModified ( Modifed );
    }
}

bool PActualProject::isModifed() const {
    return Modifed;
}

void PActualProject::setActualScene ( BackGenEngine::BScene *pc_scene ) {
    ActualScene = pc_scene;
    emit sceneOpened ( pc_scene );
}

BackGenEngine::BScene *PActualProject::actualScene() {
    return ActualScene;
}

void PActualProject::activateObject ( BackGenEngine::BObject *pc_object ) {
    if ( pcActiveObject == pc_object ) {
        return;
    }

    pcActiveObject = pc_object;

    emit objectActivated();
}

BackGenEngine::BObject *PActualProject::activeObject( ) {
    return pcActiveObject;
}

void PActualProject::changeObject ( QString old_name, BackGenEngine::BObject *pc_object ) {
    emit objectChanged ( old_name, pc_object );
    setModified ( true );
}

void PActualProject::changeLayerManager() {
    emit layerManagerChanged();
    setModified ( true );
}

void PActualProject::changeTagManager() {
    emit tagManagerChanged();
    setModified ( true );
}

PModulesSystem *PActualProject::moduleSystem() {
    return pcModuleSystem;
}

void PActualProject::changeAsset ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset ) {
    emit assetChanged ( old_name, pc_asset );
    setModified ( true );
}

BackGenEngine::BLogger *PActualProject::logger() {
    return pcLogger;
}

void PActualProject::setActiveSceneDockWidget ( PSceneDockWidget *pc_scene_dock_widget ) {
    pcActiveSceneDockWidget = pc_scene_dock_widget;
    emit sceneDockWidgetActivated();
}

PSceneDockWidget *PActualProject::activeSceneDockWidget() {
    return pcActiveSceneDockWidget;
}


void PActualProject::closeProject() {
    close();
}

PScrollComponentsWidget *PActualProject::getComponentsScroll() {
    return pcComponentsScroll;
}

void PActualProject::setComponentsScroll ( PScrollComponentsWidget *pc_scroll ) {
    pcComponentsScroll = pc_scroll;
}

void PActualProject::saveScene ( BackGenEngine::BScene *pc_scene ) {
    QString project_dir ( Project->getBaseDir().constData() );

    BoxE::Core::BByteArray data;

    BoxE::Core::BFile scene_file ( QString ( project_dir ).append ( QString ( "data/scenes/%1.scene" ).arg ( pc_scene->getName().constData() ) ).toStdString().c_str() );
    scene_file.open ( BoxE::Core::BIODevice::WriteOnly );
    data = pc_scene->toByteArray();

    scene_file.write ( data.constData(), data.size() );
    scene_file.close();
}

void PActualProject::saveAllScene( ) {
    BackGenEngine::BSceneManager::scene_hash_t::ConstIterator it = Project->getSceneManager().getSceneHash().constBegin();
    while ( it != Project->getSceneManager().getSceneHash().constEnd() ) {
        saveScene ( ( *it ) );
        ++it;
    }
}

QGLWidget *PActualProject::getCentralGL() {
    return pcCentralGL;
}

BackGenEngine::BLayer *PActualProject::getEditorLayer() {
    return pcEditorLayer;
}

void PActualProject::saveAssets( ) {
    QString project_dir ( Project->getBaseDir().constData() );

    // Save
    BoxE::Core::BByteArray data;

    BoxE::Core::BFile asset_manager_file ( QString ( project_dir ).append ( "data/assets/assets_manager.cfg" ).toStdString().c_str() );
    asset_manager_file.open ( BoxE::Core::BIODevice::WriteOnly );
    data = Project->getAssetManager().toByteArray();

    asset_manager_file.write ( data.constData(), data.size() );
    asset_manager_file.close();
}


void PActualProject::saveProject() {
    QString project_dir ( Project->getBaseDir().constData() );

    // Save
    BoxE::Core::BByteArray data;

    BoxE::Core::BFile project_file ( QString ( project_dir ).append ( "project.cfg" ).toStdString().c_str() );
    project_file.open ( BoxE::Core::BIODevice::WriteOnly );
    data = Project->toByteArray();
    project_file.write ( data.constData(), data.size() );
    project_file.close();

}

void PActualProject::maybeSave() {
    saveProject();
    saveAssets();
    saveAllScene();
}
