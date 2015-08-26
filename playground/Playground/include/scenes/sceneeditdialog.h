#ifndef SCENEEDITDIALOG_H
#define SCENEEDITDIALOG_H

#include <QDialog>

namespace BackGenEngine {
    class BScene;
}

class PActualProject;

namespace Ui {
    class SceneEditDialog;
}

class SceneEditDialog : public QDialog {
        Q_OBJECT

    public:
        explicit SceneEditDialog ( PActualProject *pc_actual_project, BackGenEngine::BScene *pc_actual_scene, QWidget *parent = 0 );
        ~SceneEditDialog();

    protected:
        virtual void keyPressEvent ( QKeyEvent *event );

    private:
        Ui::SceneEditDialog *ui;
        PActualProject *pcActualProject;
        BackGenEngine::BScene *pcScene;

    public slots:
        void parseName();
        void changeData();

};

#endif // SCENEEDITDIALOG_H
