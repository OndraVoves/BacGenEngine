#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
    class NewProjectDialog;
}

class PActualProject;

class NewProjectDialog : public QDialog {
        Q_OBJECT

    public:
        explicit NewProjectDialog ( PActualProject *actual_project, QWidget *parent = 0 );
        ~NewProjectDialog();

        QString gameDir() const;

    private:
        Ui::NewProjectDialog *ui;
        PActualProject *ActualProject;

    private slots:
        bool parseName();
        bool parseDir();
        void openDir();
        void createProject();
};

#endif // NEWPROJECTDIALOG_H
