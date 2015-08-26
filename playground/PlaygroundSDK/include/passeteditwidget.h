#ifndef PASSETEDITWIDGET_H
#define PASSETEDITWIDGET_H

#include <QWidget>

namespace BackGenEngine {
    class BAbstractAsset;
}

class PActualProject;
class MainWindow;

class PAssetEditWidget : public QWidget {
        Q_OBJECT
    public:
        explicit PAssetEditWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QWidget *parent = 0 );

        virtual void ok() = 0;
        virtual void apply() = 0;
        virtual void cancle() = 0;
        virtual void restore() = 0;

    protected:
        BackGenEngine::BAbstractAsset *asset();

        PActualProject *project( );

    private:
        BackGenEngine::BAbstractAsset *pcAsset;
        PActualProject *pcActualProject;
};

#endif // PASSETEDITWIDGET_H
