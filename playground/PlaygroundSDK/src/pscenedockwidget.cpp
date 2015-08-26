#include "../include/pscenedockwidget.h"

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pbgeglwidget.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/bproject.h>

#include <bopenglrenderer.h>
#include "../include/beditorcameracomponent.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QToolButton>
#include <QComboBox>
#include <QCheckBox>
#include <QCloseEvent>

#include <PlaygroundSDK/pmyaction.h>

PSceneDockWidget::PSceneDockWidget ( PActualProject *pc_project, QWidget *parent ) :
    PDockWidget ( pc_project, parent ) {
    setWindowTitle ( "Viewport" );

    QWidget *pc_widget = new QWidget();
    QVBoxLayout *pc_main_layout = new QVBoxLayout( );
    pc_widget->setLayout ( pc_main_layout );

    // Pseudo menu.
    QHBoxLayout *pc_menu_layout = new QHBoxLayout( );

    // View type.
    pcViewTypeComboBox = new QComboBox();
    pcViewTypeComboBox->addItem ( tr ( "Perspective" ) );
    pcViewTypeComboBox->addItem ( tr ( "Front" ) );
    pcViewTypeComboBox->addItem ( tr ( "Back" ) );
    pcViewTypeComboBox->addItem ( tr ( "Left" ) );
    pcViewTypeComboBox->addItem ( tr ( "Right" ) );
    pcViewTypeComboBox->addItem ( tr ( "Top" ) );
    pcViewTypeComboBox->addItem ( tr ( "Bottom" ) );

    connect ( pcViewTypeComboBox, SIGNAL ( currentIndexChanged ( int ) ), this, SLOT ( viewTypeComboBoxChanged ( int ) ) );

    pc_menu_layout->addWidget ( pcViewTypeComboBox );


    pcWireframe = new QCheckBox ( "Wireframe" );
    connect ( pcWireframe, SIGNAL ( toggled ( bool ) ), this, SLOT ( setWireframe ( bool ) ) );
    pc_menu_layout->addWidget ( pcWireframe );


    // Layer
    pcRenderLayerMenu = new QMenu();
    QToolButton *pc_tag_button = new QToolButton();
    pc_tag_button->setText ( tr ( "Layers" ) );
    pc_tag_button->setPopupMode ( QToolButton::InstantPopup );
    pc_tag_button->setMenu ( pcRenderLayerMenu );
    pc_tag_button->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
    pc_menu_layout->addWidget ( pc_tag_button );


    pc_main_layout->addLayout ( pc_menu_layout );


    /*    if ( project()->actualScene() != pcScene ) {
            project()->setActualScene ( pcScene );
        }*/

    setWidget ( pc_widget );

    pcBGEGLWidget = new PBGEGLWidget ( pc_project, pc_project->project()->getModuleSystem(), pc_project->getRenderer(), project()->getCentralGL(), this );


    if ( project()->actualScene() != 0  ) {
        sceneOpened ( project()->actualScene() );
    }

    pc_main_layout->addWidget ( pcBGEGLWidget );

    connect ( pc_project, SIGNAL ( sceneOpened ( BackGenEngine::BScene * ) ), this, SLOT ( sceneOpened ( BackGenEngine::BScene * ) ) );

    pcActionRenderAllLayer = new QAction ( tr ( "Render all" ), this );
    connect ( pcActionRenderAllLayer, SIGNAL ( activated() ), this, SLOT ( renderAllLayers() ) );
}

PSceneDockWidget::~PSceneDockWidget() {
    delete pcBGEGLWidget;
}

PBGEGLWidget *PSceneDockWidget::bgeGLEWidget() {
    return pcBGEGLWidget;
}

void PSceneDockWidget::mousePressEvent ( QMouseEvent *event ) {
    project()->setActiveSceneDockWidget ( this );
    event->accept();
    /*    if ( project()->actualScene() != pcScene ) {
            project()->setActualScene ( pcScene );
        }*/
}

void PSceneDockWidget::closeEvent ( QCloseEvent *event ) {
    /*    if ( project()->actualScene() == pcScene ) {
            project()->setActualScene ( 0 );
        }*/

    project()->setActiveSceneDockWidget ( 0 );

    destroy();
    event->accept();
}

void PSceneDockWidget::generateLayersMenu() {
    pcRenderLayerMenu->clear();
    layersAction.clear();

    pcRenderLayerMenu->addAction ( pcActionRenderAllLayer );
    pcRenderLayerMenu->addSeparator();

    BackGenEngine::BLayersManager::blayer_type_hash_t::ConstIterator it1 = project()->actualScene()->getLayersManager().layersTypeHash().constBegin();
    BackGenEngine::BLayersManager::blayer_hash_t::ConstIterator it2 = BackGenEngine::BLayersManager::blayer_hash_t::ConstIterator ( 0 );
    while ( it1 !=  project()->actualScene()->getLayersManager().layersTypeHash().constEnd() ) {
        it2 = ( *it1 )->constBegin();

        while ( it2 != ( *it1 )->constEnd() ) {
            PMyAction *pc_new_action = new PMyAction();
            pc_new_action->setText ( ( *it2 )->getName().constData() );
            pc_new_action->setData ( qVariantFromValue ( ( void * ) *it2 ) );
            pc_new_action->setCheckable ( true );

            connect (  pc_new_action, SIGNAL ( toggled ( PMyAction *, bool ) ), this, SLOT ( layersToggled ( PMyAction *, bool ) ) );

            pcRenderLayerMenu->addAction ( pc_new_action );

            layersAction.append ( pc_new_action );

            ++it2;
        }

        ++it1;
    }
}

void PSceneDockWidget::layersToggled ( PMyAction *pc_action, bool toggled ) {
    BackGenEngine::BLayer *pc_layer = ( ( BackGenEngine::BLayer * ) pc_action->data().value<void *>() );

    if ( toggled ) {
        pcBGEGLWidget->getCameraComponent()->insertLayer ( pc_layer );
    } else {
        pcBGEGLWidget->getCameraComponent()->removeLayer ( pc_layer );
    }
}

void PSceneDockWidget::viewTypeComboBoxChanged ( int i ) {
    pcBGEGLWidget->getCameraComponent()->setViewType ( ( BEditorCameraComponent::EViewType ) i );
    pcBGEGLWidget->getCameraComponent()->resize ( pcBGEGLWidget->width(), pcBGEGLWidget->height() );
}

void PSceneDockWidget::setWireframe ( bool wireframe ) {
    //pcBGEGLWidget->getCameraComponent()->setWireframe ( wireframe );
}

void PSceneDockWidget::sceneOpened ( BackGenEngine::BScene *pc_scene ) {
    pcBGEGLWidget->setScene ( pc_scene );
    generateLayersMenu();
    if ( pc_scene ) {
        renderAllLayers();
    }
}

void PSceneDockWidget::renderAllLayers() {
    PMyAction a;
    QVector< PMyAction * >::ConstIterator it = layersAction.constBegin();
    while ( it != layersAction.constEnd() ) {
        ( *it )->setChecked ( true );
        ++it;
    }
}
