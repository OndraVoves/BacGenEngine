#include "../include/pbgeglwidget.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>

#include <bopenglrenderer.h>
#include <BTransformationComponent.h>

#include "../include/pactualproject.h"

#include "../include/beditorcameracomponent.h"

#include <iostream>

#include <QDebug>

PBGEGLWidget::PBGEGLWidget ( PActualProject *pc_actual_project, BackGenEngine::BAbstractModuleSystem *pc_module_system, BOpenGLRenderer *pc_renderer, QGLWidget *pc_central_gl, QWidget *parent ) :
    QGLWidget ( parent ), pcActualProject ( pc_actual_project ),  pcRenderer ( pc_renderer ), pcScene ( 0 ), pcModuleSystem ( pc_module_system ), pcCameraObject ( 0 ), pcCameraComponent ( 0 ), pcCameraTransformation ( 0 ), pcCentralGL ( pc_central_gl ) {

    setFocusPolicy ( Qt::StrongFocus );
    setMouseTracking ( true );
}

PBGEGLWidget::~PBGEGLWidget() {

}

void PBGEGLWidget::setScene ( BackGenEngine::BScene *pc_scene ) {
    if ( pcScene == pc_scene ) {
        return;
    }

    pcScene = pc_scene;

    if ( pcCameraComponent ) {
        delete pcCameraComponent;
    }

    if ( pcCameraTransformation ) {
        delete pcCameraTransformation;
    }

    if ( pcCameraComponent ) {
        delete pcCameraObject;
    }

    if ( !pc_scene ) {
        return;
    }

    initializeGL();
    resizeGL ( width(), height() );

    pcCameraObject = new BackGenEngine::BObject ( "Camera", 0 );

    pcCameraTransformation = new BTransformationComponent ( pcScene );
    pcCameraComponent = new BEditorCameraComponent ( pcScene );

    pcCameraObject->insertComponent ( pcCameraTransformation );
    pcCameraObject->insertComponent ( pcCameraComponent );

    pcCameraComponent->setNormalEditorLayer ( pcActualProject->getEditorLayer() );
}

BackGenEngine::BScene *PBGEGLWidget::getScene( ) {
    return pcScene;
}


BEditorCameraComponent *PBGEGLWidget::getCameraComponent() {
    return pcCameraComponent;
}

BTransformationComponent *PBGEGLWidget::getCameraTransformation() {
    return pcCameraTransformation;
}

void PBGEGLWidget::keyPressEvent ( QKeyEvent *event ) {
    if ( !pcCameraObject ) {
        return;
    }

    if ( event->key() == Qt::Key_Up ) {
        pcCameraComponent->goFront();
    }

    if ( event->key() == Qt::Key_Down ) {
        pcCameraComponent->goBack();
    }

    if ( event->key() == Qt::Key_Left ) {
        pcCameraComponent->goLeft();
    }

    if ( event->key() == Qt::Key_Right ) {
        pcCameraComponent->goRight();
    }

}

void PBGEGLWidget::mousePressEvent ( QMouseEvent *event ) {
    QGLWidget::mousePressEvent ( event );
    emit onMousePressEvent ( event );
}

void PBGEGLWidget::mouseReleaseEvent ( QMouseEvent *event ) {
    QGLWidget::mouseReleaseEvent ( event );
    emit onMouseReleaseEvent ( event );
}


void PBGEGLWidget::mouseMoveEvent ( QMouseEvent *event ) {
    QGLWidget::mouseMoveEvent ( event );

    int rel_x = event->x() - LastMousePosition.x();
    int rel_y = event->y() - LastMousePosition.y();


    LastMousePosition = event->pos();

    if ( event->buttons() & Qt::RightButton ) {
        pcCameraComponent->rotate ( rel_x, -rel_y );
    }

    emit onMouseMoveEvent ( event );
}


void PBGEGLWidget::wheelEvent ( QWheelEvent *event ) {
    int relDelta = event->delta();
    if ( relDelta > 0 ) {
        relDelta /= relDelta;
    } else if ( relDelta < 0 ) {
        relDelta /= -relDelta;
    }

    if ( !pcCameraObject ) {
        return;
    }

    event->accept();
}

void PBGEGLWidget::initializeGL() {
    //makeCurrent();

    pcRenderer->init();

    Timer.start ( ( 1.0f / 25.0f ) * 1000.0f );
    //Timer.start();
    connect ( &Timer, SIGNAL ( timeout() ), this, SLOT ( timeout() ) );

    //doneCurrent();
}

void PBGEGLWidget::resizeGL ( int w, int h ) {
    //makeCurrent();

    ScreenSize.x ( w );
    ScreenSize.y ( h );
    ScreenOrtho.setOrthographic (  0, w, 0, h, 0.0f, 1.0f );


    if ( pcCameraComponent ) {
        pcCameraComponent->resize ( w, h );
    }
    //doneCurrent();
}

void PBGEGLWidget::paintGL() {
    if ( !pcCameraObject ) {
        return;
    }
    //makeCurrent();

    pcCameraComponent->render();


    pcRenderer->beginRender ( true, true, BoxE::Math::BVector3f ( 1.0f, 0.0f, 0.0f ) );

    pcRenderer->pushMatrix ( BOpenGLRenderer::MT_PROJECTION );
    pcRenderer->setMatrix ( BOpenGLRenderer::MT_PROJECTION, ScreenOrtho );

    pcRenderer->pushMatrix ( BOpenGLRenderer::MT_WORLD );
    pcRenderer->loadIdentityMatrix ( BOpenGLRenderer::MT_WORLD );

    glColor3f ( 1.0f, 1.0f, 1.0f  );

    pcRenderer->useTexture ( pcCameraComponent->getOutputTexture(), 0 );

    glBegin ( GL_TRIANGLES );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex2f ( 0.0f, 0.0f );

    glTexCoord2f ( 1.0f, 0.0f );
    glVertex2f ( ScreenSize.x(), 0.0f );

    glTexCoord2f ( 1.0f, 1.0f );
    glVertex2f ( ScreenSize.x(), ScreenSize.y() );

    glTexCoord2f ( 1.0f, 1.0f );
    glVertex2f ( ScreenSize.x(), ScreenSize.y() );

    glTexCoord2f ( 0.0f, 1.0f );
    glVertex2f ( 0.0f, ScreenSize.y() );

    glTexCoord2f ( 0.0f, 0.0f );
    glVertex2f ( 0.0f, 0.0f );
    glEnd();

    pcRenderer->useTexture ( 0, 0 );

    pcRenderer->popMatrix ( BOpenGLRenderer::MT_PROJECTION );
    pcRenderer->popMatrix ( BOpenGLRenderer::MT_WORLD );

    pcRenderer->endRender();
    //doneCurrent();
}

void PBGEGLWidget::timeout() {
    updateGL();
}
