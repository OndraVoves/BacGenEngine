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


#include "../include/babstractasset.h"
#include "../include/babstractmodulesystem.h"
#include "../include/bproject.h"
#include "../include/blogger.h"

#include <BoxE/BFile>

namespace BackGenEngine {
    BAbstractAsset::BAbstractAsset (  BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BLogger *pc_logger, BAbstractModuleSystem *module_system, BAssetManager *pc_asset_manager  ) : pcProject ( pc_project ),  pcLogger ( pc_logger ), ModuleSystem ( module_system ), pcAssetManager ( pc_asset_manager ),  Loaded ( false ) {
        BGE_LOGGER_DEBUG ( pcLogger, "BAbstractAsset", "BAbstractAsset", "Creating me" );
    }

    BAbstractAsset::~BAbstractAsset() {
        BGE_LOGGER_DEBUG ( pcLogger, "BAbstractAsset", "~BAbstractAsset", BoxE::Core::BAsciiString ( "Destroing me \"%1\"" ).replace ( "%1", Name ) );
    }


    BoxE::Core::BAsciiString BAbstractAsset::getName() const {
        return Name;
    }


    void BAbstractAsset::setName ( const BoxE::Core::BAsciiString &name ) {
        OnNameChanged.emitSignal ( this, name );
        Name = name;
    }


    BoxE::Core::BAsciiString BAbstractAsset::getPath() const {
        return Path;
    }

    void BAbstractAsset::setPath ( const BoxE::Core::BAsciiString &path ) {
        Path = path;
    }


    bool BAbstractAsset::isLoaded() const {
        return Loaded;
    }

    bool BAbstractAsset::realod() {
        unload();
        load();

        OnRealod.emitSignal();
    }

    bool BAbstractAsset::use() {
        if ( !Loaded ) {
            load();
        }

        return true;
    }

    bool BAbstractAsset::unuse() {
        return true;
    }

    bool BAbstractAsset::save() {
        if ( getPath().isEmpty() ) {
            return false;
        }

        if ( getModuleSystem() == 0 ) {
            return false;
        }

        BGE_LOGGER_DEBUG ( getLogger(), "BAbstractAsset", "~BAbstractAsset", BoxE::Core::BAsciiString ( "Saving \"%1\"" ).replace ( "%1", getName() ) );

        BoxE::Core::BAsciiString ext = getPath().split ( '.' ).last();

        BoxE::Core::BAsciiString full_path  = getProject()->getBaseDir();
        full_path.append ( "data/assets/" );
        full_path.append ( getAssetType().toLower() );
        full_path.append ( "/" );
        full_path.append ( getPath() );

        BoxE::Core::BFile file ( full_path );
        file.open ( BoxE::Core::BFile::WriteOnly );

        bool b = getModuleSystem()->saveAsset ( ext, this, &file, getLogger() );

        file.close();

        return b;
    }



    void BAbstractAsset::setLoaded ( bool loaded ) {
        Loaded = loaded;
    }

    BAbstractModuleSystem *BAbstractAsset::getModuleSystem( ) {
        return ModuleSystem;
    }

    BLogger *BAbstractAsset::getLogger() {
        return pcLogger;
    }

    BProject *BAbstractAsset::getProject() {
        return pcProject;
    }

    bool BAbstractAsset::load( ) {
        if ( getPath().isEmpty() ) {
            return false;
        }

        if ( getModuleSystem() == 0 ) {
            return false;
        }

        BGE_LOGGER_DEBUG ( getLogger(), "BAbstractAsset", "~BAbstractAsset", BoxE::Core::BAsciiString ( "Reloading \"%1\"" ).replace ( "%1", getName() ) );

        BoxE::Core::BAsciiString ext = getPath().split ( '.' ).last();

        BoxE::Core::BAsciiString full_path  = getProject()->getBaseDir();
        full_path.append ( "data/assets/" );
        full_path.append ( getAssetType().toLower() );
        full_path.append ( "/" );
        full_path.append ( getPath() );

        BoxE::Core::BFile file ( full_path );
        file.open ( BoxE::Core::BFile::ReadOnly );

        setLoaded ( getModuleSystem()->loadAsset ( ext, this, &file, getAssetManager(), 0 ) );

        return isLoaded();
    }

    BAssetManager *BAbstractAsset::getAssetManager() {
        return pcAssetManager;
    }

    BoxE::Core::BSignal0 &BAbstractAsset::onReload() {
        return OnRealod;
    }

    BoxE::Core::BSignal0 &BAbstractAsset::onDestroy() {
        return OnDestroy;
    }


    BoxE::Core::BSignal2< BAbstractAsset *, BoxE::Core::BAsciiString >& BAbstractAsset::onNameChanged() {
        return OnNameChanged;
    }
}