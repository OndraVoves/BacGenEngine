//#include <BImageAsset.h>
#include "../../asset/material/BMaterialAsset.h"

#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/babstracttexture.h>
#include <BackGenEngine/babstractasset.h>

#include <BoxE/BIODevice>

#include <cstring>
#include <cstdio>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_SAVER, "material", "0.0.1", "Ondra Voves" );
    ASSET_SAVER_MODULE_HEADER ( "Material" );

    bool saveAsset ( BackGenEngine::BAbstractAsset *asset, BoxE::Core::BIODevice *data, BackGenEngine::BLogger *pc_logger ) {
        BMaterialAsset *pc_material_asset = ( BMaterialAsset * ) asset ;

        if ( !pc_material_asset ) {
            //pc_logger->error ( "TGA loader", "Asset is not image type.\n" );
            return false;
        }


        BoxE::Core::BByteArray str ( "Material {\n"
                                     "%1"
                                     "}\n" );

        BoxE::Core::BByteArray texures;
        for ( int i = 0; i < 4; i++ ) {
            if ( pc_material_asset->getTextureUnit ( i ) ) {
                texures.append ( "\ttexture " );
                texures.append ( BoxE::Core::BByteArray::number ( i ) );
                texures.append ( " " );
                texures.append ( pc_material_asset->getTextureUnit ( i )->getName() );
                texures.append ( "\n" );
            }
        }

        str.replace ( "%1", texures );

        data->write ( str.constData(), str.size() );
    }

}
