#ifndef LAYERSMANAGERDIALOG_H
#define LAYERSMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
    class LayersManagerDialog;
}

namespace BackGenEngine {
    class BScene;
    class BLayer;
};

class QListWidgetItem;
class PActualProject;

class LayersManagerDialog : public QDialog {
        Q_OBJECT

    public:
        explicit LayersManagerDialog ( BackGenEngine::BScene *pc_scene, PActualProject *pc_actual_project, QWidget *parent = 0 );
        ~LayersManagerDialog();

    protected:
        virtual void keyPressEvent ( QKeyEvent *event );

    private:
        Ui::LayersManagerDialog *ui;
        BackGenEngine::BScene *pcScene;
        BackGenEngine::BLayer *pcActualLayer;
        PActualProject *pcActualProject;

        void fillLayersList();
        void updateLayerItem ( BackGenEngine::BLayer *pc_layer, QListWidgetItem *pc_item );

    private slots:
        void addNewLayer();
        void removeLayer();

        void setName();
        void setType ( QString type_name );
        void layerActivated ( QListWidgetItem *pc_item );
};

#endif // LAYERSMANAGERDIALOG_H
