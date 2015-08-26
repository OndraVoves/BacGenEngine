#ifndef PTAGSMANAGERDIALOG_H
#define PTAGSMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
    class PTagsManagerDialog;
}


namespace BackGenEngine {
    class BScene;
    class BTag;
};

class QListWidgetItem;
class PActualProject;

class PTagsManagerDialog : public QDialog {
        Q_OBJECT

    public:
        explicit PTagsManagerDialog ( BackGenEngine::BScene *pc_scene, PActualProject *pc_actual_project, QWidget *parent = 0 );
        ~PTagsManagerDialog();

    protected:
        virtual void keyPressEvent ( QKeyEvent *event );

    private:
        Ui::PTagsManagerDialog *ui;
        BackGenEngine::BScene *pcScene;
        BackGenEngine::BTag *pcActualTag;
        PActualProject *pcActualProject;

        void fillTagsList();
        void updateTagItem ( BackGenEngine::BTag *pc_tag, QListWidgetItem *pc_item );

    private slots:
        void newTag();
        void removeTag();

        void setName();

        void tagActivated ( QListWidgetItem *pc_item );
};

#endif // PTAGSMANAGERDIALOG_H
