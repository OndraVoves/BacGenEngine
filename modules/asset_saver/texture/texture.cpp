//#include <BImageAsset.h>
#include "../../asset/texture/BTextureAsset.h"

#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/babstracttexture.h>
#include <BackGenEngine/babstractasset.h>

#include <BoxE/BIODevice>

#include <cstring>
#include <cstdio>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_SAVER, "texture", "0.0.1", "Ondra Voves" );
    ASSET_SAVER_MODULE_HEADER ( "Texture" );

    bool saveAsset ( BackGenEngine::BAbstractAsset *asset, BoxE::Core::BIODevice *data, BackGenEngine::BLogger *pc_logger ) {
        BTextureAsset *pc_texture_asset = ( BTextureAsset * ) asset ;

        if ( !pc_texture_asset ) {
            //pc_logger->error ( "TGA loader", "Asset is not image type.\n" );
            return false;
        }


        BoxE::Core::BByteArray str ( "Texture {\n"
                                     "\timage %1\n"
                                     "\tfilter %2\n"
                                     "\tmipmaping %3\n"
                                     "}\n" );

        if ( pc_texture_asset->getImage() ) {
            str.replace ( "%1", pc_texture_asset->getImage()->getName()  );
        } else {
            str.replace ( "%1", BoxE::Core::BByteArray ( "0" )  );
        }

        str.replace ( "%2", BackGenEngine::BAbstractTexture::textureFilter2string ( pc_texture_asset->getFilterType() ) );

        if ( pc_texture_asset->getMipmaping() ) {
            str.replace ( "%3", BoxE::Core::BByteArray ( "1" ) );
        } else {
            str.replace ( "%3", BoxE::Core::BByteArray ( "0" ) );
        }

        data->write ( str.constData(), str.size() );
    }

}
