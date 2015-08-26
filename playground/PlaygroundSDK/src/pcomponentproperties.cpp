#include "../include/pcomponentproperties.h"

PComponentProperties::PComponentProperties ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project ) :
    QWidget ( 0 ), pcActualProject ( pc_actual_project ) {
}

PActualProject *PComponentProperties::project() {
    return pcActualProject;
}
