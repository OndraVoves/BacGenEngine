#include "../include/pcomponentpropertiesmodule.h"

#include <QLibrary>
#include <QMessageBox>

PComponentPropertiesModule::PComponentPropertiesModule ( QLibrary *pc_lib, QString component_type ) : CreateFce ( 0 ) , pcLib ( pc_lib ), ComponentType ( component_type ) {

}

PComponentPropertiesModule::~PComponentPropertiesModule() {
    delete pcLib;
}

QLibrary *PComponentPropertiesModule::lib() {
    return pcLib;
}

QString PComponentPropertiesModule::componentType() const {
    return ComponentType;
}

bool PComponentPropertiesModule::load() {
    CreateFce = ( create_fce_t * ) pcLib->resolve ( "createComponentProperties" );
    if ( !CreateFce ) {
        return false;
    }

    return true;
}

PComponentProperties *PComponentPropertiesModule::create ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project ) {
    if ( CreateFce ) {
        return CreateFce ( pc_component, pc_actual_project  );
    }
    return 0;
}
