#ifndef MODULESHEADER_H
#define MODULESHEADER_H

#include <QString>

#define PBASE_MODULE_HEADER( type, name, version, author )\
    void getBaseHeader( PModuleBaseHeader_t *header ) {\
        header->Type = type;\
        strcpy( header->Name, name );\
        strcpy( header->Version, version );\
        strcpy( header->Author, author );\
    }\
     
#define PCOMPONENT_TOOLBAR_MODULE_HEADER( component_type )\
    void getComponentToolBarModuleHeader( PComponentToolbarHeader_t *header ) {\
        strcpy( header->ComponentType, component_type );\
    }\
     
#define PCOMPONENT_PROPERTIES_MODULE_HEADER( component_type )\
    void getComponentPropertiesModuleHeader( PComponentPropertiesHeader_t *header ) {\
        strcpy( header->ComponentType, component_type );\
    }\
     
#define PASSET_EDIT_WIDGET_MODULE_HEADER( asset_type )\
    void getAssetEditWidgetModuleHeader( PAssetItemHelperHeader_t *header ) {\
        strcpy( header->AssetType, asset_type );\
    }\
     
#define PASSET_ITEM_HELPER_MODULE_HEADER( asset_type )\
    void getAssetItemHelperModuleHeader( PAssetEditWidgetHeader_t *header ) {\
        strcpy( header->AssetType, asset_type );\
    }\
     
typedef enum {
    COMPONENT_PROPERTIES = 0,
    COMPONENT_TOOLBAR,
    ASSET_EDIT_WIDGET,
    ASSET_ITEM_HELPER,
    SETTING_TAB,
    MODULES_LAST_ITEM
} EPModulesType;

typedef struct {
    EPModulesType Type;
    char Name[256];
    char Version[256];
    char Author[256];
} PModuleBaseHeader_t;

typedef struct {
    char ComponentType[256];
} PComponentPropertiesHeader_t;

typedef struct {
    char ComponentType[256];
} PComponentToolbarHeader_t;

typedef struct {
    char AssetType[256];
} PAssetEditWidgetHeader_t;

typedef struct {
    char AssetType[256];
} PAssetItemHelperHeader_t;

/*QString EPModulesType2String ( EPModulesType type ) {
    switch ( type ) {
        case COMPONENT_PROPERTIES:
            return "COMPONENT_PROPERTIES";

        case MODULES_LAST_ITEM:
        default:
            return "UNKNOW";

    }
}*/

#endif // MODULESHEADER_H
