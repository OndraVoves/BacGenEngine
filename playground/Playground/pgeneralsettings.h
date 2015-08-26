#ifndef PGENERALSETTINGS_H
#define PGENERALSETTINGS_H

#include <QTabWidget>

#include <PlaygroundSDK/psettingtabwidget.h>

namespace Ui {
    class PGeneralSettings;
}

class PActualProject;

class PGeneralSettings : public PSettingTabWidget {
        Q_OBJECT

    public:
        explicit PGeneralSettings (  MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent = 0 );
        virtual ~PGeneralSettings();

        void loadSettings();

        virtual void save();

    private:
        Ui::PGeneralSettings *ui;
        PActualProject *pcActualProject;
        MainWindow *pcMainWindow;
};

#endif // PGENERALSETTINGS_H
