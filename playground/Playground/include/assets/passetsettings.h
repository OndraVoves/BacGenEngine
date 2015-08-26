#ifndef PASSETSETTINGS_H
#define PASSETSETTINGS_H

#include <PlaygroundSDK/psettingtabwidget.h>


namespace Ui {
    class PAssetSettings;
}

class PActualProject;

class PAssetSettings : public PSettingTabWidget  {
        Q_OBJECT

    public:
        explicit PAssetSettings ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent = 0 );
        virtual ~PAssetSettings();
        virtual void save();

        void loadSettings();
    private:
        Ui::PAssetSettings *ui;
        PActualProject *pcActualProject;

    private:
        void fillAssetTypeComboBox();

    private slots:
        void externalEditorItemChanged ( int index );
        void parseExternalEditorPath();
};

#endif // PASSETSETTINGS_H
