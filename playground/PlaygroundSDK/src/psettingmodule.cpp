#include "../include/psettingmodule.h"

#include <QLibrary>

PSettingModule::PSettingModule ( QLibrary *pc_lib ) : pcLib ( pc_lib ) {
}


PSettingModule::~PSettingModule() {
    delete pcLib;
}

QLibrary *PSettingModule::lib() {
    return pcLib;
}


bool PSettingModule::load() {
    CreateFce = ( create_fce_t * ) pcLib->resolve ( "createSettingTab" );
    if ( !CreateFce ) {
        return false;
    }

    return true;
}

PSettingTabWidget *PSettingModule::create ( PActualProject *pc_project ) {
    if ( CreateFce ) {
        return CreateFce ( pc_project );
    }
    return 0;
}
