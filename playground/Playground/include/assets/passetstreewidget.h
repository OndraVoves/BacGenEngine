#ifndef PASSETSTREEWIDGET_H
#define PASSETSTREEWIDGET_H

#include <QTreeWidget>

namespace BackGenEngine {
    class BAbstractAsset;
    class BDynamicModuleSystem;
    class BAssetManager;
}

class PActualProject;
class MainWindow;


class PAssetsTreeWidget : public QTreeWidget {
        Q_OBJECT
    public:
        typedef enum {
            OPEN_IN_DOCK = 0,
            OPEN_IN_EXTERNAL_EDITOR
        } EDoubleClickAction;

    public:
        explicit PAssetsTreeWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent = 0 );
        virtual ~PAssetsTreeWidget();

        void generateItems();

        void loadSettings();
    protected:
        void contextMenuEvent ( QContextMenuEvent *event );

    private:
        MainWindow *pcMainWindow;
        PActualProject *pcActualProject;
        BackGenEngine::BDynamicModuleSystem *pcModuleSystem;
        BackGenEngine::BAssetManager *pcAssetManager;

        QAction *pcActionNewAsset;
        QAction *pcActionRemoveAsset;
        QAction *pcActionEditInExternal;
        QAction *pcActionEditInDock;

        EDoubleClickAction DoubleClickAction;

        void createActions();

    private:
        void createTopLevelItems();
        void createAssetItem ( BackGenEngine::BAbstractAsset *pc_asset, QString type );
        void updateAssetItem ( BackGenEngine::BAbstractAsset *pc_asset, QTreeWidgetItem *pc_item );

    signals:

    private slots:
        void addAsset();
        void newAsset();
        void newAsset ( QString asset );
        void removeAsset();

        void editInDock();
        void editInExternalEditor();

        void assetChanged ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset );

        void itemDClicked ( QTreeWidgetItem *pc_item, int col );
};

#endif // PASSETSTREEWIDGET_H
