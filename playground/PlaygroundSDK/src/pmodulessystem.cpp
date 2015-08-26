#include "../include/pmodulessystem.h"

#include <QMessageBox>

#include "../include/pcomponentpropertiesmodule.h"
#include "../include/passeteditwidgetmodule.h"
#include "../include/psettingmodule.h"
#include "../include/passetitemhelpermodule.h"
#include "../include/pcomponenttoolbarmodule.h"

typedef void ( get_base_header_t ) ( PModuleBaseHeader_t * );
typedef void ( get_asset_item_helper_header ) ( PAssetItemHelperHeader_t * );
typedef void ( get_asset_edit_widget_header ) ( PAssetEditWidgetHeader_t * );
typedef void ( get_component_properties_header ) ( PComponentPropertiesHeader_t * );
typedef void ( get_component_toolbar_header ) ( PComponentToolbarHeader_t * );

PModulesSystem::PModulesSystem() {
}

PModulesSystem::~PModulesSystem() {
}

bool PModulesSystem::loadModule ( QString path ) {
    if ( path.isEmpty() ) {
        return false;
    }

    QLibrary *pc_lib = new QLibrary ( path );

    if ( !pc_lib->load() ) {
        delete pc_lib;
        return false;
    }

    get_base_header_t *getBaseHeader = ( get_base_header_t * ) pc_lib->resolve ( "getBaseHeader" );

    if ( getBaseHeader ) {
        PModuleBaseHeader_t base_header;
        getBaseHeader ( &base_header );

        if ( !parseBaseHeader ( &base_header ) ) {
            delete pc_lib;
            return false;
        }

        switch ( base_header.Type ) {
            case COMPONENT_PROPERTIES:
                if ( !insertComponentPropertiesModule ( pc_lib, &base_header ) ) {
                    return false;
                }
                break;

            case COMPONENT_TOOLBAR:
                if ( !insertComponentToolBarModule ( pc_lib, &base_header ) ) {
                    return false;
                }
                break;

            case ASSET_EDIT_WIDGET:
                if ( !insertAssetEditWidgetsModule ( pc_lib, &base_header ) ) {
                    return false;
                }
                break;

            case ASSET_ITEM_HELPER:
                if ( !insertAssetItemHelperModule ( pc_lib, &base_header ) ) {
                    return false;
                }
                break;

            case SETTING_TAB:
                if ( !insertSettingTabModule ( pc_lib, &base_header ) ) {
                    return false;
                }
                break;
        }


    } else {
        delete pc_lib;
        return false;
    }

    return false;
}

const PModulesSystem::component_properties_hash_t &PModulesSystem::componentPropertiesHash() const {
    return ComponentPropertiesModule;
}

const PModulesSystem::asset_edit_widget_hash_t PModulesSystem::assetEditWidgetHash() const {
    return AssetEditWidgetsModule;
}

const PModulesSystem::setting_tab_hash_t PModulesSystem::settingTabHash() const {
    return SettingTabModule;
}

const PModulesSystem::asset_item_helper_hash_t PModulesSystem::assetItemHelperHash() const {
    return AssetItemHelperModule;
}

const PModulesSystem::component_toolbar_hash_t PModulesSystem::componentToolBarHash() const {
    return ComponentToolBarModules;
}

bool PModulesSystem::insertComponentPropertiesModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header ) {
    get_component_properties_header *helper_header = ( get_component_properties_header * ) pc_lib->resolve ( "getComponentPropertiesModuleHeader" );

    if ( !helper_header ) {
        return false;
    }

    PComponentPropertiesHeader_t header;
    helper_header ( &header );

    PComponentPropertiesModule *pc_module = new PComponentPropertiesModule ( pc_lib, header.ComponentType );

    if ( !pc_module->load() ) {
        delete pc_module;
        return false;
    }

    ComponentPropertiesModule.insert ( p_header->Name, pc_module );

    return true;
}

bool PModulesSystem::insertAssetEditWidgetsModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header ) {
    get_asset_edit_widget_header *helper_header = ( get_asset_edit_widget_header * ) pc_lib->resolve ( "getAssetEditWidgetModuleHeader" );

    if ( !helper_header ) {
        return false;
    }

    PAssetEditWidgetHeader_t header;
    helper_header ( &header );

    PAssetEditWidgetModule *pc_module = new PAssetEditWidgetModule ( pc_lib, header.AssetType );

    if ( !pc_module->load() ) {
        delete pc_module;
        return false;
    }

    AssetEditWidgetsModule.insert ( p_header->Name, pc_module );

    return true;
}

bool PModulesSystem::insertSettingTabModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header ) {
    PSettingModule *pc_module = new PSettingModule ( pc_lib );

    if ( !pc_module->load() ) {
        delete pc_module;
        return false;
    }

    SettingTabModule.insert ( p_header->Name, pc_module );

    return true;
}

bool PModulesSystem::insertAssetItemHelperModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header ) {
    get_asset_item_helper_header *helper_header = ( get_asset_item_helper_header * ) pc_lib->resolve ( "getAssetItemHelperModuleHeader" );

    if ( !helper_header ) {
        return false;
    }

    PAssetItemHelperHeader_t header;
    helper_header ( &header );

    // resolv type conflict.

    PAssetItemHelperModule *pc_module = new PAssetItemHelperModule ( pc_lib, header.AssetType );

    if ( !pc_module->load() ) {
        delete pc_module;
        return false;
    }

    AssetItemHelperModule.insert ( p_header->Name, pc_module );

    return true;
}

bool PModulesSystem::insertComponentToolBarModule ( QLibrary *pc_lib, PModuleBaseHeader_t *p_header ) {
    get_component_toolbar_header *helper_header = ( get_component_toolbar_header * ) pc_lib->resolve ( "getComponentToolBarModuleHeader" );

    if ( !helper_header ) {
        return false;
    }

    PComponentToolbarHeader_t header;
    helper_header ( &header );

    // resolv type conflict.

    PComponentToolBarModule *pc_module = new PComponentToolBarModule ( pc_lib, header.ComponentType );

    if ( !pc_module->load() ) {
        delete pc_module;
        return false;
    }

    ComponentToolBarModules.insert ( p_header->Name, pc_module );

    return true;
}


bool PModulesSystem::parseBaseHeader ( PModuleBaseHeader_t *p_header ) {
    if ( p_header->Type >= MODULES_LAST_ITEM ) {
        QMessageBox::critical ( 0, tr ( "Modules system" ),
                                tr ( "Invalid header..." ), QMessageBox::Ok );

        return false;
    }

    return true;
}
