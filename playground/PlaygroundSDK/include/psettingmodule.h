#ifndef PSETTINGMODULE_H
#define PSETTINGMODULE_H

class QLibrary;

class PSettingTabWidget;
class PActualProject;
class MainWindow;

class PSettingModule {
    public:
        PSettingModule ( QLibrary *pc_lib );
        ~PSettingModule();

        QLibrary *lib();

        bool load();
        PSettingTabWidget *create ( PActualProject *pc_project );

    private:
        typedef PSettingTabWidget * ( create_fce_t ) ( PActualProject *pc_project );
        create_fce_t *CreateFce;

    private:
        QLibrary *pcLib;
};

#endif // PSETTINGMODULE_H
