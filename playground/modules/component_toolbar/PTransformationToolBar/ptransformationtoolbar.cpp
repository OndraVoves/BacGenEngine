#include "ptransformationtoolbar.h"

#include <PlaygroundSDK/modulesheader.h>

#include <PlaygroundSDK/pscenedockwidget.h>
#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pbgeglwidget.h>
#include <PlaygroundSDK/pcomponentproperties.h>
#include <PlaygroundSDK/pscrollcomponentswidget.h>


#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

#include <BTransformationComponent.h>
#include <PlaygroundSDK/beditorcameracomponent.h>

#include <BoxE/BoxECore>

//gizmo sceleton.
PGizmoSceleton::PGizmoSceleton ( BackGenEngine::BScene *pc_scene ) : BRenderableComponent ( pc_scene ) {
    ArrowSteps = 64;

    ArrowRadius = 0.1f;
    ArrowHeight = 0.3f;
    LineHeight = 1.0f;
    LineSquareSize = 0.3f;

    //ArrowConeIB
    ArrowConeIB = new int[ ArrowSteps + 2 ];

    for ( int i = 0; i < ArrowSteps + 1; i++ ) {
        ArrowConeIB[i] = i;
    }

    ArrowConeIB[ ArrowSteps + 1 ] = 1;

    //ArrowConeIB
    LinesIB = new int[ 18 ]; // Make without new;

    for ( int i = 0; i < 18; i++ ) {
        LinesIB[i] = i;
    }


    generateXAarrow();
    generateYAarrow();
    generateZAarrow();

    generateLines();
}

PGizmoSceleton::~PGizmoSceleton() {
}

void PGizmoSceleton::render() {
    BTransformationComponent *pc_transform = getOwnerObject()->getParent()->getComponent<BTransformationComponent>();

    BoxE::Math::BMatrix4x4f mat;
    mat.setToIdentity();
    mat.translate ( pc_transform->position()  );

    glColor3f ( 1.0f, 1.0f, 1.0f );
    glBegin ( GL_LINES );
    glVertex3f ( start.x(), start.y(), start.z() );
    glVertex3f ( end.x(), end.y(), end.z() );
    glEnd();


    getScene()->getRenderer()->pushMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD );
    getScene()->getRenderer()->multMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD, mat );

    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_LINES, LinesVB, LinesIB, 9 );

    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, XArrowCone1VB, ArrowConeIB, ArrowSteps );
    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, XArrowCone2VB, ArrowConeIB, ArrowSteps );

    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, YArrowCone1VB, ArrowConeIB, ArrowSteps );
    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, YArrowCone2VB, ArrowConeIB, ArrowSteps );


    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, ZArrowCone1VB, ArrowConeIB, ArrowSteps );
    getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES_FAN, ZArrowCone2VB, ArrowConeIB, ArrowSteps );

    getScene()->getRenderer()->popMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD );

}

BackGenEngine::BAbstractComponent *PGizmoSceleton::duplicate() const {
    return 0;
}

float PGizmoSceleton::getLineSquareSize() const {
    return LineSquareSize;
}

void PGizmoSceleton::generateXAarrow() {
    float angle_step = BoxE::Math::TWO_PI / ( float ) ArrowSteps;
    float angle = 0.0f;

    BackGenEngine::BVertex c;
    c.getPosition().setXYZ ( LineHeight, 0.0f, 0.0f );
    XArrowCone1VB.append ( c );

    c.getPosition().setXYZ ( LineHeight + ArrowHeight , 0.0f, 0.0f );
    XArrowCone2VB.append ( c );

    for ( int i = 0; i < ArrowSteps; i++ ) {
        BackGenEngine::BVertex v;
        v.getPosition().x ( LineHeight );
        v.getPosition().y ( ArrowRadius * sin ( angle ) );
        v.getPosition().z ( ArrowRadius * cos ( angle ) );
        XArrowCone1VB.append ( v );

        v.getPosition().y ( ArrowRadius * sin ( BoxE::Math::TWO_PI - angle ) );
        v.getPosition().z ( ArrowRadius * cos ( BoxE::Math::TWO_PI - angle ) );
        XArrowCone2VB.append ( v );

        angle += angle_step;
    }

    XArrowCone1VB.setColor ( BoxE::Math::BVector4f ( 1.0f, 0.0f, 0.0f, 1.0f ) );
    XArrowCone2VB.setColor ( BoxE::Math::BVector4f ( 1.0f, 0.0f, 0.0f, 1.0f ) );
}

void PGizmoSceleton::generateYAarrow() {
    float angle_step = BoxE::Math::TWO_PI / ( float ) ArrowSteps;
    float angle = 0.0f;

    BackGenEngine::BVertex c;
    c.getPosition().setXYZ ( 0.0f, LineHeight, 0.0f );
    YArrowCone1VB.append ( c );

    c.getPosition().setXYZ ( 0.0f, LineHeight + ArrowHeight , 0.0f );
    YArrowCone2VB.append ( c );

    for ( int i = 0; i < ArrowSteps; i++ ) {
        BackGenEngine::BVertex v;
        v.getPosition().y ( LineHeight );
        v.getPosition().x ( ArrowRadius * sin ( angle ) );
        v.getPosition().z ( ArrowRadius * cos ( angle ) );
        YArrowCone1VB.append ( v );

        v.getPosition().x ( ArrowRadius * sin ( BoxE::Math::TWO_PI - angle ) );
        v.getPosition().z ( ArrowRadius * cos ( BoxE::Math::TWO_PI - angle ) );
        YArrowCone2VB.append ( v );

        angle += angle_step;
    }

    YArrowCone1VB.setColor ( BoxE::Math::BVector4f ( 0.0f, 1.0f, 0.0f, 1.0f ) );
    YArrowCone2VB.setColor ( BoxE::Math::BVector4f ( 0.0f, 1.0f, 0.0f, 1.0f ) );
}

void PGizmoSceleton::generateZAarrow() {
    float angle_step = BoxE::Math::TWO_PI / ( float ) ArrowSteps;
    float angle = 0.0f;

    BackGenEngine::BVertex c;
    c.getPosition().setXYZ ( 0.0f, 0.0f, LineHeight );
    ZArrowCone1VB.append ( c );

    c.getPosition().setXYZ ( 0.0f, 0.0f, LineHeight + ArrowHeight );
    ZArrowCone2VB.append ( c );

    for ( int i = 0; i < ArrowSteps; i++ ) {
        BackGenEngine::BVertex v;
        v.getPosition().z ( LineHeight );
        v.getPosition().x ( ArrowRadius * sin ( angle ) );
        v.getPosition().y ( ArrowRadius * cos ( angle ) );
        ZArrowCone1VB.append ( v );

        v.getPosition().x ( ArrowRadius * sin ( BoxE::Math::TWO_PI - angle ) );
        v.getPosition().y ( ArrowRadius * cos ( BoxE::Math::TWO_PI - angle ) );
        ZArrowCone2VB.append ( v );

        angle += angle_step;
    }

    ZArrowCone1VB.setColor ( BoxE::Math::BVector4f ( 0.0f, 0.0f, 1.0f, 1.0f ) );
    ZArrowCone2VB.setColor ( BoxE::Math::BVector4f ( 0.0f, 0.0f, 1.0f, 1.0f ) );
}

void PGizmoSceleton::generateLines() {
    BackGenEngine::BVertex v;

    //X
    v.getColor().setXYZW ( 1.0f, 0.0f, 0.0f, 1.0f );
    v.getPosition().setXYZ ( 0.0f, 0.0f, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( LineHeight, 0.0f, 0.0f );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( LineSquareSize, 0.0f, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( LineSquareSize, LineSquareSize, 0.0f );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( LineSquareSize, 0.0f, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( LineSquareSize, 0.0f, LineSquareSize );
    LinesVB.append ( v );

    //Y
    v.getColor().setXYZW ( 0.0f, 1.0f, 0.0f, 1.0f );
    v.getPosition().setXYZ ( 0.0f, 0.0f, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( 0.0f, LineHeight, 0.0f );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( 0.0f, LineSquareSize, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( LineSquareSize, LineSquareSize, 0.0f );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( 0.0f, LineSquareSize, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( 0.0f, LineSquareSize, LineSquareSize );
    LinesVB.append ( v );

    //Z
    v.getColor().setXYZW ( 0.0f, 0.0f, 1.0f, 1.0f );
    v.getPosition().setXYZ ( 0.0f, 0.0f, 0.0f );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( 0.0f, 0.0f, LineHeight );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( 0.0f, 0.0f, LineSquareSize );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( LineSquareSize, 0.0f, LineSquareSize );
    LinesVB.append ( v );

    v.getPosition().setXYZ ( 0.0f, 0.0f, LineSquareSize );
    LinesVB.append ( v );
    v.getPosition().setXYZ ( 0.0f, LineSquareSize, LineSquareSize );
    LinesVB.append ( v );
}

// trans. toolbar
PTransformationToolBar::PTransformationToolBar ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project )
    : PComponentToolbar ( pc_component, pc_mainwindow, pc_project ), pcActualSceneDockWidget ( 0 ) {
    setObjectName ( "PTransforamtionToolBar" );
    setWindowTitle ( "Transformation toolbar" );
    pcComponent = ( BTransformationComponent * ) pc_component;

    createButtons();
    createGizmo();

    if ( actualProject()->activeSceneDockWidget() != 0 ) {
        sceneDockActivated();
    }

    connect ( actualProject(), SIGNAL ( sceneDockWidgetActivated() ), this, SLOT ( sceneDockActivated() ) );
}

PTransformationToolBar::~PTransformationToolBar( ) {
    delete pcGizmoObject;
}

void PTransformationToolBar::createButtons() {
    pcMoveButton = new QPushButton ( tr ( "Move" ) );
    pcMoveButton->setCheckable ( true );
    pcMoveButton->setShortcut (  QKeySequence ( "Ctrl+Shift+T" ) );
    connect ( pcMoveButton, SIGNAL ( toggled ( bool ) ), this, SLOT ( moveToggled ( bool ) ) );
    addWidget ( pcMoveButton );

    pcRotateButton = new QPushButton ( tr ( "Rotate" ) );
    pcRotateButton->setCheckable ( true );
    pcRotateButton->setShortcut (  QKeySequence ( "Ctrl+Shift+R" ) );
    connect ( pcRotateButton, SIGNAL ( toggled ( bool ) ), this, SLOT ( rotateToggled ( bool ) ) );
    addWidget ( pcRotateButton );

    pcScaleButton  = new QPushButton ( tr ( "Scale" ) );
    pcScaleButton->setCheckable ( true );
    pcScaleButton->setShortcut (  QKeySequence ( "Ctrl+Shift+S" ) );
    connect ( pcScaleButton, SIGNAL ( toggled ( bool ) ), this, SLOT ( scaleToggled ( bool ) ) );
    addWidget ( pcScaleButton );
}

void PTransformationToolBar::move() {
}

void PTransformationToolBar::rotate() {
    BEditorCameraComponent *pc_camera_component = pcActualSceneDockWidget->bgeGLEWidget()->getCameraComponent();

}

void PTransformationToolBar::scale() {
    BEditorCameraComponent *pc_camera_component = pcActualSceneDockWidget->bgeGLEWidget()->getCameraComponent();
}


void PTransformationToolBar::createGizmo() {
    // todo: deleete
    pcGizmoObject = new BackGenEngine::BObject ( "Gizmo", 0 );
    pcGizmoObject->setParent ( pcComponent->getOwnerObject() );

    pcGizmoSceleton = new PGizmoSceleton ( actualProject()->actualScene() );

    pcGizmoObject->insertComponent ( pcGizmoSceleton );

    actualProject()->getEditorLayer()->insertObject ( pcGizmoObject );
}

void PTransformationToolBar::moveToggled ( bool toggled ) {
    if ( toggled ) {
        if ( pcScaleButton->isChecked() ) {
            pcScaleButton->setChecked ( false );

        } else if ( pcRotateButton->isChecked() ) {
            pcRotateButton->setChecked ( false );
        }
    }
}

void PTransformationToolBar::rotateToggled ( bool toggled ) {
    if ( toggled ) {
        if ( pcScaleButton->isChecked() ) {
            pcScaleButton->setChecked ( false );

        } else if ( pcMoveButton->isChecked() ) {
            pcMoveButton->setChecked ( false );
        }
    }
}

void PTransformationToolBar::scaleToggled ( bool toggled ) {
    if ( toggled ) {
        if ( pcMoveButton->isChecked() ) {
            pcMoveButton->setChecked ( false );

        } else if ( pcRotateButton->isChecked() ) {
            pcRotateButton->setChecked ( false );
        }
    }
}

void PTransformationToolBar::sceneDockActivated() {
    if ( pcActualSceneDockWidget == actualProject()->activeSceneDockWidget() ) {
        return;
    }

    if ( pcActualSceneDockWidget ) {
        disconnect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMouseMoveEvent ( QMouseEvent * ) ), this, SLOT ( onMouseMoveEvent ( QMouseEvent * ) ) );
        disconnect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMousePressEvent ( QMouseEvent * ) ), this, SLOT ( onMousePressEvent ( QMouseEvent * ) ) );
        disconnect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMouseReleaseEvent ( QMouseEvent * ) ), this, SLOT ( onMouseReleaseEvent ( QMouseEvent * ) ) );
    }

    pcActualSceneDockWidget = actualProject()->activeSceneDockWidget();

    connect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMouseMoveEvent ( QMouseEvent * ) ), this, SLOT ( onMouseMoveEvent ( QMouseEvent * ) ) );
    connect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMousePressEvent ( QMouseEvent * ) ), this, SLOT ( onMousePressEvent ( QMouseEvent * ) ) );
    connect ( pcActualSceneDockWidget->bgeGLEWidget(), SIGNAL ( onMouseReleaseEvent ( QMouseEvent * ) ), this, SLOT ( onMouseReleaseEvent ( QMouseEvent * ) ) );
}

void PTransformationToolBar::onMouseMoveEvent ( QMouseEvent *event ) {
    bool changed = false;

    /*int rel_x = event->x() - LastMousePosition.x();
    int rel_y = event->y() - LastMousePosition.y();*/

    LastMousePosition = event->pos();

    BTransformationComponent *pc_transform = pcGizmoObject->getParent()->getComponent<BTransformationComponent>();

    BoxE::Math::BVector3f rel_pos;
    if ( pcMoveButton->isChecked() ) {
        if ( XSelected || YSelected || ZSelected || XYSelected || YZSelected || XZSelected ) {
            BoxE::Math::BRay3f ray = pcActualSceneDockWidget->bgeGLEWidget()->getCameraComponent()->getRayFromScreen ( event->x(), event->y() );
            BTransformationComponent *pc_transform = pcGizmoObject->getParent()->getComponent<BTransformationComponent>();

            BoxE::Math::BVector3f pos;

            BoxE::Math::BVector3f n ( pcActualSceneDockWidget->bgeGLEWidget()->getCameraTransformation()->position() - pc_transform->position() );
            n.normalize();

            BoxE::Math::BPlane3f plane ( n, -pc_transform->position().z() );

            float t  = 100.0f;
            if ( BoxE::Math::Bintersect3::intersect ( ray, plane, t ) == BoxE::Math::Hit )  {
                pos = ray.origin() + ( ray.direction() * t );
//                pcGizmoSceleton->POS = pos ;
            }

            ///pcGizmoSceleton->POS2 = ClickPosition;

            rel_pos = pos - ClickPosition;
            ClickPosition = pos;
        }


        if ( XSelected ) {
            pc_transform->position().x ( pc_transform->position().x() + rel_pos.x() );
            changed = true;

        } else if ( YSelected ) {
            pc_transform->position().y ( pc_transform->position().y() + rel_pos.y() );
            changed = true;

        } else if ( ZSelected ) {
            pc_transform->position().z ( pc_transform->position().z() + rel_pos.z() );
            changed = true;

        } else if ( XYSelected ) {
            pc_transform->position().x ( pc_transform->position().x() + rel_pos.x() );
            pc_transform->position().y ( pc_transform->position().y() + rel_pos.y() );
            changed = true;

        } else if ( YZSelected ) {
            pc_transform->position().z ( pc_transform->position().z() + rel_pos.z() );
            pc_transform->position().y ( pc_transform->position().y() + rel_pos.y() );
            changed = true;

        } else if ( XZSelected ) {
            pc_transform->position().z ( pc_transform->position().z() + rel_pos.z() );
            pc_transform->position().x ( pc_transform->position().x() + rel_pos.x() );
            changed = true;
        }

    }


    if ( changed ) {
        actualProject()->getComponentsScroll()->updateComponent ( "Transformation" );
    }

}

void PTransformationToolBar::onMousePressEvent ( QMouseEvent *event ) {
    if ( event->button() != Qt::LeftButton ) {
        return;
    }


    BoxE::Math::BRay3f ray = pcActualSceneDockWidget->bgeGLEWidget()->getCameraComponent()->getRayFromScreen ( event->x(), event->y() );
    BTransformationComponent *pc_transform = pcGizmoObject->getParent()->getComponent<BTransformationComponent>();


    pcGizmoSceleton->start = ray.origin();
    pcGizmoSceleton->end = ray.origin() + ( ray.direction() * 1000.0f );

    BoxE::Math::BSphere3f sphere_x (  pc_transform->position() + BoxE::Math::BVector3f ( 1.125, 0.0f, 0.0f ), 0.125f  );
    BoxE::Math::BSphere3f sphere_y (  pc_transform->position() + BoxE::Math::BVector3f ( 0.0f, 1.25f, 0.0f ), 0.25f  );
    BoxE::Math::BSphere3f sphere_z (  pc_transform->position() + BoxE::Math::BVector3f ( 0.0f, 0.0f, 1.125 ), 0.125f  );

    BoxE::Math::BPlane3f plane_xy ( BoxE::Math::BVector3f ( 0.0f, 0.0f, 1.0f ), -pc_transform->position().z() );
    BoxE::Math::BPlane3f plane_yz ( BoxE::Math::BVector3f ( 1.0f, 0.0f, 0.0f ), -pc_transform->position().x() );
    BoxE::Math::BPlane3f plane_xz ( BoxE::Math::BVector3f ( 0.0f, 1.0f, 0.0f ), -pc_transform->position().y() );

    XSelected = false;
    YSelected = false;
    ZSelected = false;
    XYSelected = false;
    YZSelected = false;
    XZSelected = false;


    float t = 100.0f;
    if ( BoxE::Math::Bintersect3::intersect ( ray, sphere_x, t ) == BoxE::Math::Hit ) {
        XSelected = true;

    } else if ( BoxE::Math::Bintersect3::intersect ( ray, sphere_y, t ) == BoxE::Math::Hit ) {
        YSelected = true;

    } else if ( BoxE::Math::Bintersect3::intersect ( ray, sphere_z, t ) == BoxE::Math::Hit ) {
        ZSelected = true;

    }


    t = 100.0f;
    if ( BoxE::Math::Bintersect3::intersect ( ray, plane_xy, t ) == BoxE::Math::Hit ) {
        ClickPosition = ray.origin() + ( ray.direction() * t );

        if ( ( ClickPosition.x() >= pc_transform->position().x() ) &&
                ( ClickPosition.x() <= ( pc_transform->position().x() + pcGizmoSceleton->getLineSquareSize() ) ) &&
                ( ClickPosition.y() >= pc_transform->position().y() ) &&
                ( ClickPosition.y() <= ( pc_transform->position().y() + pcGizmoSceleton->getLineSquareSize() ) ) ) {

            XYSelected = true;
        }

    }

    t = 100.0f;
    if ( BoxE::Math::Bintersect3::intersect ( ray, plane_yz, t ) == BoxE::Math::Hit ) {
        ClickPosition = ray.origin() + ( ray.direction() * t );

        if ( ( ClickPosition.z() >= pc_transform->position().z() ) &&
                ( ClickPosition.z() <= ( pc_transform->position().z() + pcGizmoSceleton->getLineSquareSize() ) ) &&
                ( ClickPosition.y() >= pc_transform->position().y() ) &&
                ( ClickPosition.y() <= ( pc_transform->position().y() + pcGizmoSceleton->getLineSquareSize() ) ) ) {

            XYSelected = false;
            YZSelected = true;
        }
    }

    t = 100.0f;
    if ( BoxE::Math::Bintersect3::intersect ( ray, plane_xz, t ) == BoxE::Math::Hit ) {
        ClickPosition = ray.origin() + ( ray.direction() * t );

        if ( ( ClickPosition.z() >= pc_transform->position().z() ) &&
                ( ClickPosition.z() <= ( pc_transform->position().z() + pcGizmoSceleton->getLineSquareSize() ) ) &&
                ( ClickPosition.x() >= pc_transform->position().x() ) &&
                ( ClickPosition.x() <= ( pc_transform->position().x() + pcGizmoSceleton->getLineSquareSize() ) ) ) {

            XYSelected = false;
            YZSelected = false;
            XZSelected = true;
        }
    }

    if ( XSelected || YSelected || ZSelected || XYSelected || YZSelected || XZSelected ) {
        BoxE::Math::BVector3f n ( pcActualSceneDockWidget->bgeGLEWidget()->getCameraTransformation()->position() - pc_transform->position() );
        n.normalize();

        BoxE::Math::BPlane3f plane ( n, -pc_transform->position().z() );

        float t  = 100.0f;
        if ( BoxE::Math::Bintersect3::intersect ( ray, plane, t ) == BoxE::Math::Hit )  {
            ClickPosition = ray.origin() + ( ray.direction() * t );
        }
    }
}

void PTransformationToolBar::onMouseReleaseEvent ( QMouseEvent *event ) {
    XSelected = false;
    YSelected = false;
    ZSelected = false;
    XYSelected = false;
    YZSelected = false;
    XZSelected = false;
}


extern "C" {
    PBASE_MODULE_HEADER ( COMPONENT_TOOLBAR, "Transformation toolbar", "0.0.1", "Ondra Voves" );
    PCOMPONENT_TOOLBAR_MODULE_HEADER ( "Transformation" );

    PComponentToolbar *createComponentToolBar ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project ) {
        return new PTransformationToolBar ( pc_component, pc_mainwindow, pc_project );
    }
}
