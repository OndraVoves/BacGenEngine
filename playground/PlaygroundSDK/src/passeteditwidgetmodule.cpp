#include "../include/passeteditwidgetmodule.h"

#include <QLibrary>

PAssetEditWidgetModule::PAssetEditWidgetModule ( QLibrary *pc_lib,  QString asset_type ) : pcLib ( pc_lib ), CreateFce ( 0 ), AssetType ( asset_type ) {

}

PAssetEditWidgetModule::~PAssetEditWidgetModule() {
    delete pcLib;
}

QLibrary *PAssetEditWidgetModule::lib() {
    return pcLib;
}

QString PAssetEditWidgetModule::assetType( ) const {
    return AssetType;
}


bool PAssetEditWidgetModule::load() {
    CreateFce = ( create_fce_t * ) pcLib->resolve ( "createAssetEditWidget" );
    if ( !CreateFce ) {
        return false;
    }

    return true;
}

PAssetEditWidget *PAssetEditWidgetModule::create ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) {
    if ( CreateFce ) {
        return CreateFce ( pc_asset, pc_project );
    }
    return 0;
}
