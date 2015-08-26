#include <cstring>
#include <clocale>

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bmodulesheader.h>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_LOADER, "png", "0.0.1", "JA-a" )
    ASSET_LOADER_MODULE_HEADER ( "Image" )

    bool loadAsset ( BackGenEngine::BAbstractAsset *asset ) {
        printf ( "saving..... \n" );
        return true;
    }
}
