#ifndef ASSETEDITDOCKWIDGET_H
#define ASSETEDITDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class AssetEditDockWidget;
}

namespace BackGenEngine {
    class BAbstractAsset;
}

class PActualProject;
class PAssetEditWidget;
class PDefaultEditAssetWidget;

class QAbstractButton;

class AssetEditDockWidget : public QDockWidget {
        Q_OBJECT

    public:
        explicit AssetEditDockWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *actual_project, QWidget *parent = 0 );
        ~AssetEditDockWidget();

        void setAssetWidget ( PAssetEditWidget *pc_widget );

    protected:
        virtual void closeEvent ( QCloseEvent *event );

    private:
        Ui::AssetEditDockWidget *ui;
        BackGenEngine::BAbstractAsset *pcAsset;
        PActualProject *pcActualProject;
        PAssetEditWidget *pcMainWidget;
        PDefaultEditAssetWidget *pcDefaultWidget;

    private slots:
        void buttonClicked ( QAbstractButton *pc_button );
        void assetChanged ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset );
};

#endif // ASSETEDITDOCKWIDGET_H
