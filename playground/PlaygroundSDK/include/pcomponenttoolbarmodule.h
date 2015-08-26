#ifndef PCOMPONENTTOOLBARMODULE_H
#define PCOMPONENTTOOLBARMODULE_H

#include <QString>

class QLibrary;

namespace BackGenEngine {
    class BAbstractComponent;
}

class PComponentToolbar;
class PActualProject;
class MainWindow;

class PComponentToolBarModule {
    public:
        PComponentToolBarModule (  QLibrary *pc_lib, QString component_type  );
        ~PComponentToolBarModule();

        QLibrary *lib();
        QString componentType() const;

        bool load();

        PComponentToolbar *create ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project );

    private:
        typedef PComponentToolbar * ( create_fce_t ) ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project );
        create_fce_t *CreateFce;

    private:
        QLibrary *pcLib;
        QString ComponentType;
};

#endif // PCOMPONENTTOOLBARMODULE_H
