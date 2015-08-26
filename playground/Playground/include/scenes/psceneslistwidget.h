#ifndef PSCENESLISTWIDGET_H
#define PSCENESLISTWIDGET_H

#include <QListWidget>

class PActualProject;
class MainWindow;

namespace BackGenEngine {
    class BScene;
    class BSceneManager;
}

class PScenesListWidget : public QListWidget {
        Q_OBJECT
    public:
        explicit PScenesListWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent = 0 );

        void fillSceneList();

        virtual ~PScenesListWidget();

    private:
        MainWindow *pcMainWindow;
        PActualProject *ActualProject;
        BackGenEngine::BSceneManager *pcSceneManager;

        QAction *pcActionNewScene;
        QAction *pcActionDeleteScene;
        QAction *pcActionEditScene;

    protected:
        void contextMenuEvent ( QContextMenuEvent * );

    private:
        void createActions();
        void deleteActions();

        void updateSceneItem ( BackGenEngine::BScene *pc_scene, QListWidgetItem *pc_item );

    signals:

    public slots:
        void addNewScene();
        void deleteSelectedScene();
        void editSelectedScene();
        void sceneDoubleClicked ( QListWidgetItem *pc_item );

};

#endif // PSCENESLISTWIDGET_H
