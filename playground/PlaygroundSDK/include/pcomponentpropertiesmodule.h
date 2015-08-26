#ifndef PCOMPONENTPROPERTIESMODULE_H
#define PCOMPONENTPROPERTIESMODULE_H

#include <QString>

class QLibrary;
class QTreeWidgetItem;
class QTreeWidget;

namespace BackGenEngine {
    class BAbstractComponent;
}

class PActualProject;

class PComponentProperties;

class PComponentPropertiesModule {
    public:
        PComponentPropertiesModule ( QLibrary *pc_lib, QString component_type );
        ~PComponentPropertiesModule();

        QLibrary *lib();

        QString componentType() const;

        bool load();

        PComponentProperties *create ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project );

    private:
        typedef PComponentProperties * ( create_fce_t ) ( BackGenEngine::BAbstractComponent *pc_component, PActualProject * );
        create_fce_t *CreateFce;

    private:
        QLibrary *pcLib;
        QString ComponentType;
};

#endif // PCOMPONENTPROPERTIESMODULE_H
