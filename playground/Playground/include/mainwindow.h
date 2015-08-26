#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pmodulessystem.h>

#include <QHash>

namespace Ui {
    class MainWindow;
}

namespace BackGenEngine {
    class BScene;
}

class PSceneDockWidget;
class PMainTabWidget;

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow ( QWidget *parent = 0 );
        ~MainWindow();

        QMenu *assetMenu();
        QMenu *sceneMenu();
        QMenu *objectMenu();
        QMenu *componentMenu();

    protected:
        void closeEvent ( QCloseEvent * );

    private slots:
        // PRoject
        void projectOpened();
        void projectClosed();
        void openProject();

        void sceneOpened ( BackGenEngine::BScene *  );
        //void sceneClosed();

        void showModulesSettingsDialog();

        void newProject(); // TODO: HADEJ =D
        void projectSetting();
        void quit();
        void aboutQt();

    private:
        Ui::MainWindow *ui;
        PModulesSystem ModuleSystem;
        PActualProject ActualProject;

        QDockWidget *pcScenesDockWidget;
        QDockWidget *pcObjectsTreeDockWidget;
        QDockWidget *pcObjectDocWidget;
        QDockWidget *pcAssetDockWidget;

        PMainTabWidget *pcMainTabWidget;

        QHash<QString, PSceneDockWidget *> ViewportsHash;

    private:
        void writeSettings();
        void readSettings();
        void loadPlaygroundModules();

    private slots:
        void newViewport();
        void viewportDestroyed ( QObject *pc_object );

};

#endif // MAINWINDOW_H
