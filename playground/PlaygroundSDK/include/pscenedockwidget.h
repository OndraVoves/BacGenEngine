#ifndef PSCENEDOCKWIDGET_H
#define PSCENEDOCKWIDGET_H

#include <PlaygroundSDK/pdockwidget.h>

namespace BackGenEngine {
    class BScene;
    class BObject;
}

class BOpenGLRenderer;
class BEditorCameraComponent;
class PBGEGLWidget;

class QMenu;
class QComboBox;
class QCheckBox;

class PMyAction;

class PSceneDockWidget : public PDockWidget {
        Q_OBJECT
    public:
        explicit PSceneDockWidget ( PActualProject *pc_project, QWidget *parent = 0 );
        virtual ~PSceneDockWidget();

        PBGEGLWidget *bgeGLEWidget();

    protected:
        virtual void mousePressEvent ( QMouseEvent *event );
        virtual void closeEvent ( QCloseEvent *event );
    private:
        PBGEGLWidget *pcBGEGLWidget;

        QComboBox *pcViewTypeComboBox;
        QCheckBox *pcWireframe;
        QMenu *pcRenderLayerMenu;
        QAction *pcActionRenderAllLayer;

        QVector< PMyAction * > layersAction;

        void generateLayersMenu();

    signals:

    private slots:
        void layersToggled ( PMyAction *pc_action, bool toggled );
        void viewTypeComboBoxChanged ( int i );
        void setWireframe ( bool wireframe );
        void sceneOpened ( BackGenEngine::BScene *pc_scene );

        void renderAllLayers();
};

#endif // PSCENEDOCKWIDGET_H
