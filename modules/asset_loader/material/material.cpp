//#include <BImageAsset.h>
#include "../../asset/material/BMaterialAsset.h"

#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/bassetmanager.h>

#include <BoxE/BIODevice>

#include <cstring>
#include <cstdio>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_LOADER, "material", "0.0.1", "Ondra Voves" );
    ASSET_LOADER_MODULE_HEADER ( "Material" );

    bool loadAsset ( BackGenEngine::BAbstractAsset *asset, BoxE::Core::BIODevice *data, BackGenEngine::BAssetManager *pc_asset_manager, BackGenEngine::BLogger *pc_logger ) {
        BMaterialAsset *pc_material_asset = ( BMaterialAsset * ) asset ;

        if ( !pc_material_asset ) {
            //pc_logger->error ( "TGA loader", "Asset is not image type.\n" );
            return false;
        }

        BoxE::Core::BByteArray device_array ( data->readAll() );

        BoxE::Core::BByteArray array;
        array.reserve ( device_array.size() );

        const char *ch = device_array.constData();
        while ( ( *ch ) != '\0' ) {
            if ( ( *ch ) == '\t' ) {
                ++ch;
                continue;
            } else if ( ( *ch ) == '\n' ) {
                array.append ( " " );
            } else {
                array.append ( ( *ch ) );
            }

            ++ch;
        }
        array.squeeze();

        BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = array.split ( ' ' );

        int block_count = 0;
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {

            if ( ( *it ) == "Material" ) {
                if ( ++it == list.constEnd() ) {
                    return false;
                }

                if ( ( *it ) == "{" ) {
                    block_count = 1;
                } else {
                    return false;
                }

                while ( block_count != 0 ) {
                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    if ( ( *it ) == "}" ) {
                        block_count--;

                    } else if ( ( *it ) == "texture" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        bool b = false;
                        int unit = 0;

                        unit = ( *it ).toInt ( &b );

                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name = ( *it );

                        pc_material_asset->setTextureUnit ( unit, ( BTextureAsset * ) pc_asset_manager->getAsset ( *it ) );
                    }
                }
            }

            ++it;
        }


        return true;
    }
}

