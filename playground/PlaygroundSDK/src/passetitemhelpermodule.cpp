#include "../include/passetitemhelpermodule.h"

#include <QLibrary>

PAssetItemHelperModule::PAssetItemHelperModule (  QLibrary *pc_lib, QString asset_type   ) : pcLib ( pc_lib ), UpdateFce ( 0 ), AssetType ( asset_type ) {
}


PAssetItemHelperModule::~PAssetItemHelperModule() {
    delete pcLib;
}

QLibrary *PAssetItemHelperModule::lib() {
    return pcLib;
}

QString PAssetItemHelperModule::assetType( ) const {
    return AssetType;
}

bool PAssetItemHelperModule::load() {
    UpdateFce = ( update_fce_t * ) pcLib->resolve ( "updateAssetItem" );
    if ( !UpdateFce ) {
        return false;
    }

    return true;
}

void PAssetItemHelperModule::update ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QTreeWidgetItem *pc_item  ) {
    if ( UpdateFce ) {
        return UpdateFce ( pc_asset, pc_project, pc_item );
    }
}
