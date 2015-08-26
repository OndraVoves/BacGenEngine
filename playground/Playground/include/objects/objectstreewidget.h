#ifndef OBJECTSTREEWIDGET_H
#define OBJECTSTREEWIDGET_H

#include <QTreeWidget>

class PActualProject;
class MainWindow;

namespace BackGenEngine {
    class BObject;
    class BScene;
}

class ObjectsTreeWidget : public QTreeWidget {
        Q_OBJECT
    public:
        explicit ObjectsTreeWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent = 0 );
        virtual ~ObjectsTreeWidget();

        void fillObjectTree();

        void dropEvent ( QDropEvent *event );

        void enableMe();
        void disableMe();

    protected:
        void contextMenuEvent ( QContextMenuEvent * );

    private:
        MainWindow *pcMainWindow;
        PActualProject *pcActualProject;

        QAction *pcActionNewObject;
        QAction *pcActionDeleteObject;
        QAction *pcActionDuplicateObject;
        QMenu *pcMenu;

        void createActions();
        void deleteActions();

        void updateObjectItem ( BackGenEngine::BObject *pc_object, QTreeWidgetItem *pc_item );
        void createObjectTreeItems ( BackGenEngine::BObject *pc_object, QTreeWidgetItem *pc_item );
    signals:

    public slots:
        void createNewObject();
        void deleteSelectedObject();
        void duplicateSelectedObject();

        void objectActivated ( QTreeWidgetItem *, int );

        void updateObjectItem ( QString old_name, BackGenEngine::BObject *pc_object );

    private slots:
        void sceneActivated ( BackGenEngine::BScene *pc_scene );

};

#endif // OBJECTSTREEWIDGET_H
