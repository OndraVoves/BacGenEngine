//#include <BImageAsset.h>
#include "../../asset/image/BImageAsset.h"

#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/blogger.h>

#include <BoxE/BIODevice>

#include <cstring>
#include <cstdio>

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET_LOADER, "tga", "0.0.1", "Ondra Voves" );
    ASSET_LOADER_MODULE_HEADER ( "Image" );

    bool loadTGARAW ( BImageAsset *pc_asset, unsigned char *p_tga_header, BoxE::Core::BIODevice *pc_buffer, BackGenEngine::BLogger *pc_logger );
    bool loadTGARLE ( BImageAsset *pc_asset, unsigned char *p_tga_header, BoxE::Core::BIODevice *pc_buffer, BackGenEngine::BLogger *pc_logger );

    bool loadAsset (  BackGenEngine::BAbstractAsset *asset, BoxE::Core::BIODevice *data, BackGenEngine::BAssetManager *pc_asset_manager, BackGenEngine::BLogger *pc_logger ) {
        BImageAsset *pc_image_asset = ( BImageAsset * ) asset ;

        if ( !pc_image_asset ) {
            //pc_logger->error ( "TGA loader", "Asset is not image type.\n" );
            return false;
        }

        unsigned char tga_header[18];

//        BGE::Base::CString full_path = pc_image_asset->scenePtr()->applicationPtr()->baseDir() + pc_image_asset->path();
//        image_file = fopen ( full_path.toCStr(), "rb" );

//        if ( image_file == 0 ) {
        //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Could not open file \"%0\".\n" ).arg ( 0, full_path ) );
//            return false;
//        }



        /*        if (  buffer.read ( ( char* )tga_header, 18 ) != 1 ) {
                    //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Could not read tga header for file \"%0\".\n" ).arg ( 0, pc_asset->path() ) );
                    return false;
                }*/

        printf ( "load\n" );

        int  i = data->read ( ( char * ) tga_header, 18 );

        if ( ( ( unsigned int ) tga_header[2] == 2 ) || ( ( unsigned int ) tga_header[2] == 3 ) ) {
            return loadTGARAW ( pc_image_asset, tga_header, data, pc_logger );
        } else if ( ( ( unsigned int ) tga_header[2] == 10 ) || ( ( unsigned int ) tga_header[2] == 11 ) ) {
            return loadTGARLE ( pc_image_asset, tga_header, data, pc_logger );
        }

        //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Wrong TGA image \"%0\".\n" ).arg ( 0, pc_asset->path() ) );

        return false;
    }

    bool loadTGARAW ( BImageAsset *pc_asset, unsigned char *p_tga_header, BoxE::Core::BIODevice *pc_buffer, BackGenEngine::BLogger *pc_logger ) {
        printf ( "load raw\n" );
        unsigned int  image_size;
        unsigned int  bypp;
        unsigned int  temp;

        int Width = 0;
        int Height = 0;
        int BPP = 0;
        unsigned char *aPixels = 0;

        memcpy ( &Width, p_tga_header + 12, 2 );
        memcpy ( &Height, p_tga_header + 14, 2 );
        memcpy ( &BPP, p_tga_header + 16, 1 );

        aPixels = new unsigned char[ Width * Height * BPP ];

        bypp = BPP / 8;

        image_size = Width * Height * bypp;

        /*        if ( pc_buffer->read( ( char*)aPixels, image_size) != 1 ) {
                    //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Could not read tga data for file \"%0\".\n" ).arg ( 0, pc_asset->path() ) );
                    return false;
                }*/
        pc_buffer->read ( ( char * ) aPixels, image_size );

        for ( unsigned int i = 0; i < image_size; i += bypp ) {
            temp = aPixels[ i ];
            aPixels[ i ] = aPixels[ i + 2 ];
            aPixels[ i + 2 ] = temp;
        }

        pc_asset->width ( Width );
        pc_asset->height ( Height );
        pc_asset->bpp ( BPP );
        pc_asset->pixels ( aPixels );

        return true;
    }

    bool loadTGARLE ( BImageAsset *pc_asset, unsigned char *p_tga_header, BoxE::Core::BIODevice *pc_buffer, BackGenEngine::BLogger *pc_logger ) {
        printf ( "load rle\n" );
        unsigned int  image_size;
        unsigned int  bypp;

        int Width = 0;
        int Height = 0;
        int BPP = 0;
        unsigned char *aPixels;

        memcpy ( &Width, p_tga_header + 12, 2 );
        memcpy ( &Height, p_tga_header + 14, 2 );
        memcpy ( &BPP, p_tga_header + 16, 1 );

        aPixels = new unsigned char[ Width * Height * BPP ];


        bypp = BPP / 8;

        image_size = Width * Height * bypp;

        /* RLE. */
        unsigned int pixel_count = Width * Height;
        unsigned int curent_pixel = 0;
        unsigned int curent_byte = 0;


        unsigned char *color_buffer = new unsigned char[ sizeof ( unsigned char ) * bypp ];

        do {
            unsigned char chunkheader = 0;

            pc_buffer->read ( ( char * ) &chunkheader, sizeof ( unsigned char ) );

            if ( chunkheader < 128 ) {
                chunkheader += 1;

                for ( short counter = 0; counter < chunkheader; counter++ ) {
                    pc_buffer->read ( ( char * ) color_buffer, bypp );
                    aPixels[curent_byte] = color_buffer[2];
                    aPixels[curent_byte + 1] = color_buffer[1];
                    aPixels[curent_byte + 2] = color_buffer[0];
                    if ( bypp == 4 ) {
                        aPixels[curent_byte + 3] = color_buffer[3];
                    }

                    curent_byte += bypp;
                    curent_pixel++;

                    if ( curent_pixel > pixel_count ) {
                        //loggerPtr()->log ( Base::CLogger::LL_ERROR, "CImageAsset::LoadTGARLE()", Base::CString ( "Wrong RLE for file \"%0\"." ).arg ( 0, filename ) );
                        //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Wrong RLE for file \"%0\".\n" ).arg ( 0, pc_asset->path() ) );
                        return false;
                    }
                }
            } else {
                chunkheader -= 127;

                pc_buffer->read ( ( char * ) color_buffer, bypp );

                for ( short counter = 0; counter < chunkheader; counter++ ) {
                    aPixels[curent_byte] = color_buffer[2];
                    aPixels[curent_byte + 1] = color_buffer[1];
                    aPixels[curent_byte + 2] = color_buffer[0];
                    if ( bypp == 4 ) {
                        aPixels[curent_byte + 3] = color_buffer[3];
                    }

                    curent_byte += bypp;
                    curent_pixel++;

                    if ( curent_pixel > pixel_count ) {
                        //loggerPtr()->log ( Base::CLogger::LL_ERROR, "CImageAsset::LoadTGARLE()", Base::CString ( "Wrong RLE for file \"%0\"." ).arg ( 0, filename ) );
                        //pc_logger->error ( "TGA loader", BGE::Base::CString ( "Wrong RLE for file \"%0\".\n" ).arg ( 0, pc_asset->path() ) );
                        return false;
                    }
                }
            }

        } while ( curent_pixel < pixel_count );

        delete [] color_buffer;

        pc_asset->width ( Width );
        pc_asset->height ( Height );
        pc_asset->bpp ( bypp * 8 ); // BUG: BPP is zero;
        pc_asset->pixels ( aPixels );

        return true;

    }
}
