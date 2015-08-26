#ifndef PMODULESSETTINGS_H
#define PMODULESSETTINGS_H

#include <QTabWidget>

#include <PlaygroundSDK/psettingtabwidget.h>

namespace Ui {
    class PModulesSettings;
}

class PActualProject;

class PModulesSettings : public PSettingTabWidget {
        Q_OBJECT

    public:
        explicit PModulesSettings ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent = 0 );
        virtual ~PModulesSettings();

        virtual void save();

    private:
        Ui::PModulesSettings *ui;
        PActualProject *pcActualProject;

    private:
        void fillModulesTree();

};

#endif // PMODULESSETTINGS_H
