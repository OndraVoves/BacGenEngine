#ifndef PMODULESSYSTEM_H
#define PMODULESSYSTEM_H

#include <QHash>
#include <QLibrary>

#include "./modulesheader.h"

class QTreeWidgetItem;
class QTreeWidget;

namespace BackGenEngine {
    class BAbstractComponent;
}

class PComponentProperties;
class PComponentPropertiesModule;
class PAssetEditWidgetModule;
class PSettingModule;
class PAssetItemHelperModule;
class PComponentToolBarModule;

class PModulesSystem : QObject {
        Q_OBJECT

    public:
        typedef QHash<QString, PComponentPropertiesModule *> component_properties_hash_t;
        typedef QHash<QString, PAssetEditWidgetModule * > asset_edit_widget_hash_t;
        typedef QHash<QString, PSettingModule * > setting_tab_hash_t;
        typedef QHash<QString, PAssetItemHelperModule * > asset_item_helper_hash_t;
        typedef QHash<QString, PComponentToolBarModule * > component_toolbar_hash_t;

    public:
        PModulesSystem();
        ~PModulesSystem();

        bool loadModule ( QString path );


        const component_properties_hash_t &componentPropertiesHash() const;
        const asset_edit_widget_hash_t assetEditWidgetHash() const;
        const setting_tab_hash_t settingTabHash() const;
        const asset_item_helper_hash_t assetItemHelperHash() const;
        const component_toolbar_hash_t componentToolBarHash() const;

    private:
        bool parseBaseHeader ( PModuleBaseHeader_t *p_header );

        bool insertComponentPropertiesModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header );
        bool insertAssetEditWidgetsModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header );
        bool insertSettingTabModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header );
        bool insertAssetItemHelperModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header );
        bool insertComponentToolBarModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header );

    private:
        component_properties_hash_t ComponentPropertiesModule;
        asset_edit_widget_hash_t    AssetEditWidgetsModule;
        setting_tab_hash_t          SettingTabModule;
        asset_item_helper_hash_t    AssetItemHelperModule;
        component_toolbar_hash_t    ComponentToolBarModules;
};

#endif // PMODULESSYSTEM_H
