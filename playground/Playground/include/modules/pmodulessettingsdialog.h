#ifndef PMODULESSETTINGSDIALOG_H
#define PMODULESSETTINGSDIALOG_H

#include <QDialog>

class QListWidgetItem;

namespace Ui {
    class PModulesSettingsDialog;
}

class PActualProject;
class PSettingTabWidget;
class MainWindow;
class QAbstractButton;

class PModulesSettingsDialog : public QDialog {
        Q_OBJECT

    public:
        explicit PModulesSettingsDialog ( MainWindow *pc_main_window, PActualProject *pc_actual_project, QWidget *parent = 0 );
        ~PModulesSettingsDialog();

    protected:
        virtual void keyPressEvent ( QKeyEvent *event );

    private:
        Ui::PModulesSettingsDialog *ui;
        PActualProject *pcActualPoject;
        PSettingTabWidget *pcActualTabWidget;
        MainWindow *pcMainWindow;

        void loadSettings();

    private slots:
        void itemSelected ( QListWidgetItem *pc_item );
        void buttonClicked ( QAbstractButton *pc_button );
};

#endif // PMODULESSETTINGSDIALOG_H
