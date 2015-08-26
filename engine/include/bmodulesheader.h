/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef BMODULESHEADER_H
#define BMODULESHEADER_H

#include <BoxE/BAsciiString>

#define BASE_MODULE_HEADER( type, name, version, author )\
    void getBaseHeader( BackGenEngine::BBaseModuleHeader_t *header ) {\
        header->Type = type;\
        strcpy( header->Name, name );\
        strcpy( header->Version, version );\
        strcpy( header->Author, author );\
    }\
     
#define ASSET_LOADER_MODULE_HEADER( asset_name )\
    void getAssetLoaderModuleHeader( BackGenEngine::BAssetLoaderModuleHeader_t *header ) {\
        strcpy( header->AssetName, asset_name );\
    }\
     
#define ASSET_SAVER_MODULE_HEADER( asset_name )\
    void getAssetSaverModuleHeader( BackGenEngine::BAssetSaverModuleHeader_t *header ) {\
        strcpy( header->AssetName, asset_name );\
    }\
     
namespace BackGenEngine {

    typedef enum EModulesType {
        COMPONENT = 0,
        ASSET,
        ASSET_LOADER,
        ASSET_SAVER,
        MODULES_TYPE_LAST_ITEM
    } EModulesType;

    typedef struct {
        EModulesType Type;
        char Name[256];
        char Version[256];
        char Author[256];
    } BBaseModuleHeader_t;

    typedef struct {
        char AssetName[256];
    } BAssetLoaderModuleHeader_t;

    typedef struct {
        char AssetName[256];
    } BAssetSaverModuleHeader_t;

    /*!
     * Convert module type to string.
     * \param type Module type.
     * \return Module type as string.
     */
    BoxE::Core::BAsciiString EModulesType2String ( EModulesType type );

}

#endif  // BMODULESHEADER_H