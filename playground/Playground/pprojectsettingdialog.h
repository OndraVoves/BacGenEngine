#ifndef PPROJECTSETTINGDIALOG_H
#define PPROJECTSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
    class PProjectSettingDialog;
}

class PActualProject;

class PProjectSettingDialog : public QDialog {
        Q_OBJECT

    public:
        explicit PProjectSettingDialog ( PActualProject *pc_actual_project, QWidget *parent = 0 );
        ~PProjectSettingDialog();

    protected:
        void changeEvent ( QEvent *e );

    private:
        Ui::PProjectSettingDialog *ui;
        PActualProject *pcActualProject;

    private slots:
        void parseName();
        void changeData();
};

#endif // PPROJECTSETTINGDIALOG_H
