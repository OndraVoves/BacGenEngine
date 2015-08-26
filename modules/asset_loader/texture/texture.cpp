//#include <BImageAsset.h>
#include "../../asset/texture/BTextureAsset.h"

#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/bassetmanager.h>

#include <BoxE/BIODevice>

#include <cstring>
#include <cstdio>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_LOADER, "texture", "0.0.1", "Ondra Voves" );
    ASSET_LOADER_MODULE_HEADER ( "Texture" );

    bool loadAsset ( BackGenEngine::BAbstractAsset *asset, BoxE::Core::BIODevice *data, BackGenEngine::BAssetManager *pc_asset_manager, BackGenEngine::BLogger *pc_logger ) {
        BTextureAsset *pc_texture_asset = ( BTextureAsset * ) asset ;

        if ( !pc_texture_asset ) {
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

            if ( ( *it ) == "Texture" ) {
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

                    } else if ( ( *it ) == "image" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name = ( *it );

                        if ( ( *it ) == "0" ) {
                            pc_texture_asset->setImage ( 0 );

                        } else {
                            BImageAsset *pc_image_asset =  ( BImageAsset * ) pc_asset_manager->getAsset ( name );
                            pc_texture_asset->setImage ( pc_image_asset );
                        }

                    } else if ( ( *it ) == "mipmaping" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray value = ( *it );

                        if ( ( *it ) == "0" ) {
                            pc_texture_asset->setMipmaping ( false );
                        } else if ( ( *it ) == "1" ) {
                            pc_texture_asset->setMipmaping ( true );
                        }

                    } else if ( ( *it ) == "filter" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        pc_texture_asset->setFilterType ( BackGenEngine::BAbstractTexture::string2textureFilter ( ( *it ) ) );
                    }
                }
            }

            ++it;
        }


        return true;
    }
}

