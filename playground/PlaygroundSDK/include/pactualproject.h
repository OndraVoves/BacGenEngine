#ifndef PACTUALPROJECT_H
#define PACTUALPROJECT_H

#include <QObject>

namespace BackGenEngine {
    class BProject;
    class BScene;
    class BObject;
    class BAbstractAsset;
    class BLogger;
    class BLayer;
}

class BOpenGLRenderer;
class QGLWidget;

class PScrollComponentsWidget;
class PModulesSystem;
class PSceneDockWidget;
class PComponentProperties;

class PActualProject : public QObject {
        Q_OBJECT
    public:
        explicit PActualProject ( PModulesSystem *pc_module_system, QObject *parent = 0 );
        virtual ~PActualProject ();

        BOpenGLRenderer *getRenderer();

        BackGenEngine::BProject *project( );
        bool create ( const QString &name, const QString &dir );
        bool open ( const QString &dir );
        void close();
        void setModified ( bool modified );
        bool isModifed() const;
        void setActualScene ( BackGenEngine::BScene *pc_scene ) ;

        BackGenEngine::BScene *actualScene();
        void activateObject ( BackGenEngine::BObject *pc_object );
        BackGenEngine::BObject *activeObject( );
        void changeObject ( QString old_name, BackGenEngine::BObject *pc_object );
        void changeLayerManager();
        void changeTagManager();
        PModulesSystem *moduleSystem();
        void changeAsset ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset );
        BackGenEngine::BLogger *logger();
        void setActiveSceneDockWidget ( PSceneDockWidget *pc_scene_dock_widget );
        PSceneDockWidget *activeSceneDockWidget();


        PScrollComponentsWidget *getComponentsScroll();
        void setComponentsScroll ( PScrollComponentsWidget *pc_scroll );


        // SAVE
        void saveScene ( BackGenEngine::BScene *pc_scene );
        void saveAllScene( );
        void saveAssets( );

        QGLWidget *getCentralGL();

        BackGenEngine::BLayer *getEditorLayer();
    private:
        BackGenEngine::BProject *Project;
        BackGenEngine::BScene *ActualScene;
        BackGenEngine::BObject *pcActiveObject;
        BackGenEngine::BLogger *pcLogger;
        PModulesSystem *pcModuleSystem;
        PSceneDockWidget *pcActiveSceneDockWidget;
        BOpenGLRenderer *pcRenderer;
        PScrollComponentsWidget *pcComponentsScroll;
        bool Modifed;

        QGLWidget *pcCentralGL;
        BackGenEngine::BLayer *pcEditorLayer;
    signals:
        // Project
        void projectOpened();
        void projectClosed();
        void projectModified ( bool );

        //scene.
        void sceneOpened ( BackGenEngine::BScene * );
        void sceneDockWidgetActivated();


        //void sceneClosed( );
        void layerManagerChanged();
        void tagManagerChanged();

        // Object.
        void objectActivated();
        void objectChanged ( QString old_name, BackGenEngine::BObject *pc_object );

        // Asset.
        void assetChanged ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset );

    public slots:
        void saveProject();
        void maybeSave();
        void closeProject();

};

#endif // PACTUALPROJECT_H
