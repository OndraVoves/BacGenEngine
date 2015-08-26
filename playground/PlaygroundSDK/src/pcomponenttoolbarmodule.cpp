#include "../include/pcomponenttoolbarmodule.h"

#include <QLibrary>

PComponentToolBarModule::PComponentToolBarModule (  QLibrary *pc_lib, QString component_type )
    :  CreateFce ( 0 ) , pcLib ( pc_lib ), ComponentType ( component_type ) {
}

PComponentToolBarModule::~PComponentToolBarModule() {
    delete pcLib;
}

QLibrary *PComponentToolBarModule::lib() {
    return pcLib;
}

QString PComponentToolBarModule::componentType() const {
    return ComponentType;
}

bool PComponentToolBarModule::load() {
    CreateFce = ( create_fce_t * ) pcLib->resolve ( "createComponentToolBar" );
    if ( !CreateFce ) {
        return false;
    }

    return true;
}


PComponentToolbar *PComponentToolBarModule::create ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project ) {
    if ( CreateFce ) {
        return CreateFce ( pc_component, pc_mainwindow, pc_project );
    }
    return 0;
}
