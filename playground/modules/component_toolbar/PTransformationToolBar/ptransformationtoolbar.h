#ifndef PTRANSFORMATIONTOOLBAR_H
#define PTRANSFORMATIONTOOLBAR_H

#include "PTransformationToolBar_global.h"

#include <PlaygroundSDK/pcomponenttoolbar.h>

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/brenderablecomponent.h>
#include <BackGenEngine/bvertexbuffer.h>

#include <BoxE/BVector3f>

class PGizmoSceleton : public BackGenEngine::BRenderableComponent {
    public:
        PGizmoSceleton ( BackGenEngine::BScene *pc_scene );
        virtual ~PGizmoSceleton();

        virtual BoxE::Core::BAsciiString getName() const {
            return "GizmoSceleton";
        }

        virtual void render();
        virtual BackGenEngine::BAbstractComponent *duplicate() const;

        BoxE::Math::BVector3f start;
        BoxE::Math::BVector3f end;

        float getLineSquareSize() const;

    private:
        int ArrowSteps;
        float ArrowRadius;
        float ArrowHeight;
        float LineHeight;
        float LineSquareSize;

        // XArrow
        BackGenEngine::BVertexBuffer XArrowCone1VB;
        BackGenEngine::BVertexBuffer XArrowCone2VB;
        void generateXAarrow();

        // YArrow
        BackGenEngine::BVertexBuffer YArrowCone1VB;
        BackGenEngine::BVertexBuffer YArrowCone2VB;
        void generateYAarrow();

        // ZArrow
        BackGenEngine::BVertexBuffer ZArrowCone1VB;
        BackGenEngine::BVertexBuffer ZArrowCone2VB;
        void generateZAarrow();

        BackGenEngine::BVertexBuffer LinesVB;
        void generateLines();

        int *ArrowConeIB;
        int *LinesIB;
};

class QPushButton;
class PSceneDockWidget;
class BTransformationComponent;

class PTRANSFORMATIONTOOLBARSHARED_EXPORT PTransformationToolBar: public PComponentToolbar {
        Q_OBJECT
    public:
        PTransformationToolBar ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project );
        virtual ~PTransformationToolBar( );

    private:
        BTransformationComponent *pcComponent;
        QPushButton *pcMoveButton;
        QPushButton *pcRotateButton;
        QPushButton *pcScaleButton;
        PSceneDockWidget *pcActualSceneDockWidget;

        QPoint LastMousePosition;

        void createButtons();
        void move();
        void rotate();
        void scale();


        BackGenEngine::BObject *pcGizmoObject;
        PGizmoSceleton *pcGizmoSceleton;
        void createGizmo();

        bool XSelected;
        bool YSelected;
        bool ZSelected;

        bool XYSelected;
        bool YZSelected;
        bool XZSelected;

        BoxE::Math::BVector3f ClickPosition;

    private slots:
        void moveToggled ( bool toggled );
        void rotateToggled ( bool toggled );
        void scaleToggled ( bool toggled );

        void sceneDockActivated();
        void onMouseMoveEvent ( QMouseEvent *event );
        void onMousePressEvent ( QMouseEvent *event );
        void onMouseReleaseEvent ( QMouseEvent *event );
};

#endif // PTRANSFORMATIONTOOLBAR_H
