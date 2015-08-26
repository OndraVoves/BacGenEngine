#include "../include/passeteditwidget.h"

PAssetEditWidget::PAssetEditWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QWidget *parent ) :
    QWidget ( parent ), pcAsset ( pc_asset ), pcActualProject ( pc_project ) {

}

BackGenEngine::BAbstractAsset *PAssetEditWidget::asset() {
    return pcAsset;
}

PActualProject *PAssetEditWidget::project( ) {
    return pcActualProject;
}
