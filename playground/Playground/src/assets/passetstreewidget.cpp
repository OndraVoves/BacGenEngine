#include "../../include/assets/passetstreewidget.h"

#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bdynamicmodulesystem.h>
#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bassetmanager.h>
#include <BackGenEngine/babstractrenderer.h>
#include <BackGenEngine/bassetloadermodule.h>

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/passetitemhelpermodule.h>



#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QSettings>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include "./include/mainwindow.h"

#include "../../include/assets/pdefaulteditassetwidget.h"
#include "../../include/assets/asseteditdockwidget.h"


PAssetsTreeWidget::PAssetsTreeWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent ) :
    QTreeWidget ( parent ), pcMainWindow ( main_window ) , pcActualProject ( actual_project ), pcAssetManager ( &actual_project->project()->getAssetManager() ),
    DoubleClickAction ( OPEN_IN_DOCK ) {

    setIconSize ( QSize ( 32, 32 ) );

    pcModuleSystem = ( BackGenEngine::BDynamicModuleSystem * ) actual_project->project()->getModuleSystem();

    headerItem()->setText ( 0, tr ( "Name" ) );

    generateItems();

    createActions();

    loadSettings();

    connect ( pcActualProject, SIGNAL ( assetChanged ( QString, BackGenEngine::BAbstractAsset * ) ),
              this, SLOT ( assetChanged ( QString, BackGenEngine::BAbstractAsset * ) ) );


    connect ( this, SIGNAL ( itemDoubleClicked ( QTreeWidgetItem *, int ) ), this, SLOT ( itemDClicked ( QTreeWidgetItem *, int ) ) );
}

PAssetsTreeWidget::~PAssetsTreeWidget() {
//    delete pcActionNewAsset;
}

void PAssetsTreeWidget:: generateItems() {
    createTopLevelItems();

    BackGenEngine::BAssetManager::asset_hash_t::ConstIterator it = pcAssetManager->constBegin();
    while ( it != pcAssetManager->constEnd() ) {
        createAssetItem ( ( *it ), QString ( ( *it )->getAssetType().constData() ) );
        ++it;
    }

}

void PAssetsTreeWidget::loadSettings() {
    QSettings s;

    s.beginGroup ( "AssetTree" );
    DoubleClickAction = ( EDoubleClickAction ) s.value ( "DoubleClickAction", 0 ).toInt();
    s.endGroup();
}

void PAssetsTreeWidget::contextMenuEvent ( QContextMenuEvent *event ) {
    QMenu contex_menu ( this );

    if ( !selectedItems().isEmpty() ) {
        QTreeWidgetItem *pc_item = selectedItems().first();
        if ( pc_item->parent() ) {
            contex_menu.addAction ( pcActionEditInDock );
            contex_menu.addAction ( pcActionEditInExternal );
            contex_menu.addAction ( pcActionRemoveAsset );
        } else {
            pcActionNewAsset->setText ( QString ( tr ( "Create new %1" ).arg ( pc_item->text ( 0 ) ) ) );
            contex_menu.addAction ( pcActionNewAsset );
        }
    }

    contex_menu.exec (  event->globalPos() );
}

void PAssetsTreeWidget::createActions() {
    QAction *pc_add_asset  = new QAction ( tr ( "&Add asset" ) , this );
    connect ( pc_add_asset, SIGNAL ( activated() ), this, SLOT ( addAsset() ) );

    pcMainWindow->assetMenu()->addAction ( pc_add_asset );

    pcActionNewAsset = new QAction ( "", this );
    connect ( pcActionNewAsset, SIGNAL ( activated() ), this, SLOT ( newAsset() ) );

    pcActionRemoveAsset = new QAction ( tr ( "&Remove asset" ), this );
    connect ( pcActionRemoveAsset, SIGNAL ( activated() ), this, SLOT ( removeAsset() ) );

    pcActionEditInExternal = new QAction ( tr ( "Edit in &external editor" ), this );
    connect ( pcActionEditInExternal, SIGNAL ( activated() ), this, SLOT ( editInExternalEditor() ) );

    pcActionEditInDock = new QAction ( tr ( "Edit in dock" ), this );
    connect ( pcActionEditInDock, SIGNAL ( activated() ), this, SLOT ( editInDock() ) );
}

void PAssetsTreeWidget::createTopLevelItems() {
    clear();
    BackGenEngine::BDynamicModuleSystem::asset_module_hash_t::ConstIterator it = pcModuleSystem->getAssetModuleHash().constBegin();

    QTreeWidgetItem *pc_new_item = 0;
    QString name;
    while ( it != pcModuleSystem->getAssetModuleHash().constEnd() ) {
        name = it.key().constData();
        pc_new_item = new QTreeWidgetItem();
        pc_new_item->setText ( 0, name );
        pc_new_item->setIcon ( 0, QIcon ( QString ( "./images/assets/%1.png" ).arg ( name ) ) );

        addTopLevelItem ( pc_new_item );
        ++it;
    }
}

void PAssetsTreeWidget::createAssetItem ( BackGenEngine::BAbstractAsset *pc_asset, QString type ) {
    QTreeWidgetItem *pc_new_item = new QTreeWidgetItem ( findItems ( type, Qt::MatchCaseSensitive ).first() );

    updateAssetItem ( pc_asset, pc_new_item );
}

void PAssetsTreeWidget::updateAssetItem ( BackGenEngine::BAbstractAsset *pc_asset, QTreeWidgetItem *pc_item ) {
    pc_item->setText ( 0, pc_asset->getName().constData() );
    pc_item->setData ( 0, Qt::UserRole, qVariantFromValue ( ( void * ) pc_asset )  );

    PModulesSystem::asset_item_helper_hash_t::ConstIterator it = pcActualProject->moduleSystem()->assetItemHelperHash().constBegin();
    while ( it != pcActualProject->moduleSystem()->assetItemHelperHash().constEnd() ) {
        if ( ( *it )->assetType() == pc_asset->getInterfaceType().constData() ) {
            ( *it )->update ( pc_asset, pcActualProject, pc_item );
            break;
        }
        ++it;
    }

    QString tool_tip = pc_item->toolTip ( 0 );
    pc_item->setToolTip ( 0, QString ( "<b>Name: </b>%1<br/>" ).arg ( pc_asset->getName().constData() ).append ( tool_tip ) );
}

void PAssetsTreeWidget::newAsset ( QString asset ) {
    QString type = asset.split ( ". " ).at ( 1 );

    int i = 2;
    QString name = QString ( "%1_1" ).arg ( type );

    while ( pcAssetManager->containAsset ( name.toStdString().c_str() ) ) {
        name = QString ( "%1_%2" ).arg ( type ).arg ( i++ );
    }

    BackGenEngine::BAbstractAsset *pc_new_asset = pcModuleSystem->createAsset ( type.toStdString().c_str(), pcActualProject->project(), ( BackGenEngine::BAbstractRenderer * ) pcActualProject->getRenderer(), &pcActualProject->project()->getAssetManager(),  pcActualProject->logger() );

    if ( !pc_new_asset ) {
        QMessageBox::critical ( this, tr ( "Assets manager" ), tr ( "Could not create asset." ), QMessageBox::Ok );
        return;
    }

    pc_new_asset->setName ( name.toStdString().c_str() );

    pcAssetManager->insertAsset ( pc_new_asset );

    createAssetItem ( pc_new_asset, type );
}

void PAssetsTreeWidget::addAsset() {
    QString SuportedFormats;

    BackGenEngine::BDynamicModuleSystem *pc_modules_system = ( BackGenEngine::BDynamicModuleSystem * ) pcActualProject->project()->getModuleSystem();
    BackGenEngine::BDynamicModuleSystem::asset_loader_module_hash_t::ConstIterator it = pc_modules_system->getAssetLoaderHash().constBegin();

    while ( it != pc_modules_system->getAssetLoaderHash().constEnd() ) {
        QString str ( QString ( "%1 (*.%1) (*.%1);;" ).arg ( it.key().constData() ) );
        SuportedFormats.append ( str );
        ++it;
    }

    QString file_name = QFileDialog::getOpenFileName (  this, tr ( "Open asset.." ), QString(), SuportedFormats  );

    if ( file_name.isEmpty()  ) {
        return;
    }

    QString ext = file_name.split ( '.' ).last();

    QString asset_type;;
    it = pc_modules_system->getAssetLoaderHash().constBegin();
    while ( it != pc_modules_system->getAssetLoaderHash().constEnd() ) {
        if ( ext == it.key().constData() ) {
            asset_type = ( *it )->getAssetType().constData();
        }
        ++it;
    }


    QFileInfo file_info ( file_name );

    QString base_dir_str ( pcActualProject->project()->getBaseDir().constData() );
    if ( !base_dir_str.endsWith ( '/' ) ) {
        base_dir_str.append ( '/' );
    }


    QString short_filename = file_info.fileName();
    QString full_path ( QString ( "%1data/assets/%2/%3" ).arg ( base_dir_str ).arg ( asset_type.toLower() ).arg ( short_filename ) );

    //makeDirSceleton ( base_dir_str, asset()->getAssetType().constData() );

    QFile file ( full_path );
    if ( file.exists() ) {
        int ret = QMessageBox::question ( this, "Asset exist", "Asset is exist, replace it?", QMessageBox::Ok | QMessageBox::Cancel );

        if ( ret == QMessageBox::Ok ) {
            QFile::copy ( file_name, full_path );
        } else {
            return;
        }

    } else {
        QFile::copy ( file_name, full_path );
    }

    // create
    int i = 2;
    QString name = QString ( "%1_1" ).arg ( asset_type );

    while ( pcAssetManager->containAsset ( name.toStdString().c_str() ) ) {
        name = QString ( "%1_%2" ).arg ( asset_type ).arg ( i++ );
    }

    BackGenEngine::BAbstractAsset *pc_new_asset = pcModuleSystem->createAsset ( asset_type.toStdString().c_str(), pcActualProject->project(), ( BackGenEngine::BAbstractRenderer * ) pcActualProject->getRenderer(), &pcActualProject->project()->getAssetManager(),  pcActualProject->logger() );

    if ( !pc_new_asset ) {
        QMessageBox::critical ( this, tr ( "Assets manager" ), tr ( "Could not create asset." ), QMessageBox::Ok );
        return;
    }

    pc_new_asset->setName ( name.toStdString().c_str() );
    pc_new_asset->setPath ( short_filename.toStdString().c_str() );
    pcAssetManager->insertAsset ( pc_new_asset );
    createAssetItem ( pc_new_asset, asset_type );


}

void PAssetsTreeWidget::newAsset() {
    QTreeWidgetItem *pc_item = selectedItems().first();

    QString name = QString ( " . %1" ).arg ( pc_item->text ( 0 ) );
    newAsset ( name );
}

void PAssetsTreeWidget::removeAsset() {
    QTreeWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BAbstractAsset *pc_asset = ( BackGenEngine::BAbstractAsset * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    int ret = QMessageBox::question ( this, tr ( "Do you really want..." ),
                                      tr ( "Do you really want to delete \"%1\" asset?" ).arg ( pc_asset->getName().constData() ),
                                      QMessageBox::Ok | QMessageBox::Cancel );

    if ( ret == QMessageBox::Cancel ) {
        return;
    }


    pcAssetManager->removeAsset ( pc_asset );

    delete pc_asset;
    delete pc_item;
}

inline Qt::DockWidgetArea int2WidgetArea ( int i ) {
    switch ( i ) {
        default:
        case 0:
            return Qt::TopDockWidgetArea;

        case 1:
            return Qt::BottomDockWidgetArea;

        case 2:
            return Qt::LeftDockWidgetArea;

        case 3:
            return Qt::RightDockWidgetArea;

        case 4:
            return Qt::NoDockWidgetArea;
    }
}

void PAssetsTreeWidget::editInDock() {
    QTreeWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BAbstractAsset *pc_asset = ( BackGenEngine::BAbstractAsset * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    AssetEditDockWidget *pc_dock = new AssetEditDockWidget ( pc_asset, pcActualProject, this );

    QSettings s;
    int i = s.value ( "AssetTree/EditDockWidgetPosition", 0 ).toInt();

    if ( i < 4 ) {
        pcMainWindow->addDockWidget ( int2WidgetArea ( i ), pc_dock );
    } else {
        pcMainWindow->addDockWidget ( Qt::TopDockWidgetArea, pc_dock );
        pc_dock->setFloating ( true );
    }

}

void PAssetsTreeWidget::editInExternalEditor() {
    QTreeWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BAbstractAsset *pc_asset = ( BackGenEngine::BAbstractAsset * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    QSettings s;

    QString editor_path = s.value ( QString ( "AssetsEditor/%1" ).arg ( pc_asset->getAssetType().constData() ) ).toString();
    if ( !editor_path.isEmpty( ) ) {
        QStringList arg;
        QString path = QString ( "%1data/assets/%2/%3" ).arg ( pcActualProject->project()->getBaseDir().constData() )
                       .arg ( pc_asset->getAssetType().toLower().constData() )
                       .arg ( pc_asset->getPath().constData() );
        arg << path;
        QProcess::startDetached ( editor_path, arg );
    }
}

void PAssetsTreeWidget::assetChanged ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset ) {
    QList<QTreeWidgetItem *> list = findItems ( old_name, Qt::MatchCaseSensitive | Qt::MatchRecursive );

    if ( list.count( ) ) {
        updateAssetItem ( pc_asset, list.first() );
    }
}

void PAssetsTreeWidget::itemDClicked ( QTreeWidgetItem *pc_item, int col ) {
    ( void ) col;
    if ( pc_item->parent() == 0 ) {
        return;
    }

    switch ( DoubleClickAction ) {
        case OPEN_IN_DOCK:
            editInDock();
            break;

        case OPEN_IN_EXTERNAL_EDITOR:
            editInExternalEditor();
            break;
    }
}
