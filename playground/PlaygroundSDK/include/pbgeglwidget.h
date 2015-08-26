#ifndef PBGEGLWIDGET_H
#define PBGEGLWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>

#include <BoxE/BoxECore>

#include <QTimer>

namespace BackGenEngine {
    class BObject;
    class BScene;
    class BAbstractModuleSystem;
}

class BOpenGLRenderer;
class BEditorCameraComponent;
class BTransformationComponent;
class PActualProject;

class PBGEGLWidget : public QGLWidget {
        Q_OBJECT
    public:
        explicit PBGEGLWidget ( PActualProject *pc_actual_project, BackGenEngine::BAbstractModuleSystem *pc_module_system, BOpenGLRenderer *pc_renderer, QGLWidget *pc_central_gl, QWidget *parent = 0 );
        virtual ~PBGEGLWidget();

        void setScene ( BackGenEngine::BScene *pc_scene );
        BackGenEngine::BScene *getScene( );


        BEditorCameraComponent *getCameraComponent();
        BTransformationComponent *getCameraTransformation();


    protected:
        void keyPressEvent ( QKeyEvent *event );
        void mousePressEvent ( QMouseEvent * );
        void mouseReleaseEvent ( QMouseEvent * );
        void mouseMoveEvent ( QMouseEvent *event );
        void wheelEvent ( QWheelEvent * );

        void initializeGL();
        void resizeGL ( int w, int h );
        void paintGL();

    private:
        PActualProject *pcActualProject;

        BoxE::Math::BMatrix4x4f ScreenOrtho;
        BoxE::Math::BVector3f ScreenSize;

        QTimer Timer;

        BOpenGLRenderer *pcRenderer;
        BackGenEngine::BScene *pcScene;
        BackGenEngine::BAbstractModuleSystem *pcModuleSystem;

        BackGenEngine::BObject *pcCameraObject;
        BTransformationComponent *pcCameraTransformation;
        BEditorCameraComponent *pcCameraComponent;

        QGLWidget *pcCentralGL;
        QPoint LastMousePosition;

    signals:
        void onMouseMoveEvent ( QMouseEvent *event );
        void onMousePressEvent ( QMouseEvent *event );
        void onMouseReleaseEvent ( QMouseEvent *event  );
    private slots:
        void timeout();

};

#endif // PBGEGLWIDGET_H
