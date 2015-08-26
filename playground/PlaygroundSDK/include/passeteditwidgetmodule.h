#ifndef PASSETEDITWIDGETMODULE_H
#define PASSETEDITWIDGETMODULE_H

#include <QString>

class QLibrary;

class PAssetEditWidget;

namespace BackGenEngine {
    class BAbstractAsset;
}

class PActualProject;

class PAssetEditWidgetModule {
    public:
        PAssetEditWidgetModule ( QLibrary *pc_lib, QString asset_type );
        ~PAssetEditWidgetModule();

        QLibrary *lib();
        QString assetType( ) const;

        bool load();
        PAssetEditWidget *create ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project );

    private:
        typedef PAssetEditWidget * ( create_fce_t ) ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project );
        create_fce_t *CreateFce;

    private:
        QLibrary *pcLib;
        QString AssetType;
};

#endif // PASSETEDITWIDGETMODULE_H
