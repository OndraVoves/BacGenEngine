#include <cstring>
#include <clocale>

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bmodulesheader.h>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET, "Pokus", "0.0.1", "JA-a" );

    BackGenEngine::BAbstractAsset *createAsset () {
        printf ( "create me...\n" );
    }
}
