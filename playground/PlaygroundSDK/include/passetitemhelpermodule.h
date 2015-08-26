#ifndef PASSETITEMHELPERMODULE_H
#define PASSETITEMHELPERMODULE_H

#include <QString>

class QLibrary;
class QTreeWidgetItem;

namespace BackGenEngine {
    class BAbstractAsset;
}

class PActualProject;

class PAssetItemHelperModule {
    public:
        PAssetItemHelperModule ( QLibrary *pc_lib, QString asset_type );
        ~PAssetItemHelperModule();

        QLibrary *lib();

        QString assetType( ) const;

        bool load();
        void update ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QTreeWidgetItem *pc_item  );

    private:
        typedef void ( update_fce_t ) ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QTreeWidgetItem *pc_item );
        update_fce_t *UpdateFce;

    private:
        QLibrary *pcLib;
        QString AssetType;
};

#endif // PASSETITEMHELPERMODULE_H
