#include "../../include/components/pcomponentswidget.h"
#include "ui_pcomponentswidget.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QScrollArea>

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/babstractcomponent.h>
#include <BackGenEngine/bdynamicmodulesystem.h>

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pmyaction.h>
#include <PlaygroundSDK/pmodulessystem.h>
#include <PlaygroundSDK/pcomponentproperties.h>
#include <PlaygroundSDK/pcomponentpropertiesmodule.h>
#include <PlaygroundSDK/pcomponenttoolbar.h>
#include <PlaygroundSDK/pcomponenttoolbarmodule.h>
#include <PlaygroundSDK/pscrollcomponentswidget.h>
#include "./include/mainwindow.h"

#include <BackGenEngine/bobject.h>

PComponentsWidget::PComponentsWidget ( MainWindow *main_window, PActualProject *actual_project ) :
    QWidget ( 0 ),
    ui ( new Ui::PComponentsWidget ), pcMainWindow ( main_window ), pcActualProject ( actual_project ), pcComponentWidget ( 0 ), pcComponentScroll ( 0 ) {
    ui->setupUi ( this );


    pcAddComponentMenu = new QMenu ( tr ( "&Add" ) );
    generateAddComponentMenu();

    pcMainWindow->componentMenu()->addMenu ( pcAddComponentMenu );


    pcComponentScroll = new PScrollComponentsWidget ( pcActualProject );
    ui->verticalLayout->addWidget ( pcComponentScroll );
    pcActualProject->setComponentsScroll ( pcComponentScroll );

    setDisabled ( true );
    connect ( pcActualProject, SIGNAL ( objectActivated() ), this, SLOT ( objectActivated() ) );
}

PComponentsWidget::~PComponentsWidget() {
    delete ui;
}


void PComponentsWidget::generateAddComponentMenu() {
    BackGenEngine::BDynamicModuleSystem *pc_module_system = ( BackGenEngine::BDynamicModuleSystem * ) pcActualProject->project()->getModuleSystem();

    int i = 0;
    PMyAction *pc_action = 0;
    BackGenEngine::BDynamicModuleSystem::component_module_hash_t::ConstIterator it = pc_module_system->constComponentBegin();
    while ( it != pc_module_system->constComponentEnd() ) {
        pc_action = new PMyAction();
        pc_action->setIcon ( QIcon ( QString ( "./images/components/%1.png" ).arg ( it.key().constData() ) ) );
        pc_action->setText ( QString ( "&%1. %2" ).arg ( i++ ).arg ( it.key().constData() ) );

        connect ( pc_action, SIGNAL ( activated ( QString ) ), this, SLOT ( addComponent ( QString ) ) );

        pcAddComponentMenu->addAction ( pc_action );

        ++it;
    }
}

void PComponentsWidget::createToolbars() {
    if ( !pcActualProject->activeObject() ) {
        return;
    }

    BackGenEngine::BObject::component_vector_t::ConstIterator it = pcActualProject->activeObject()->getComponentVector().constBegin();
    while ( it != pcActualProject->activeObject()->getComponentVector().constEnd() ) {

        // toolbars
        PComponentToolbar *pc_toolbar;
        PModulesSystem::component_toolbar_hash_t::ConstIterator it2 = pcActualProject->moduleSystem()->componentToolBarHash().constBegin();
        while ( it2 !=  pcActualProject->moduleSystem()->componentToolBarHash().constEnd() ) {
            if ( ( *it2 )->componentType() == ( *it )->getName() ) {
                pc_toolbar = ( *it2 )->create ( ( *it ), pcMainWindow, pcActualProject );
                ComponentToolBarList.append ( pc_toolbar );
                pcMainWindow->addToolBar ( pc_toolbar );
            }
            ++it2;
        }

        ++it;
    }
}


void PComponentsWidget::objectActivated() {
    QList<PComponentToolbar *>::Iterator it = ComponentToolBarList.begin();
    while ( it != ComponentToolBarList.end() ) {
        delete ( *it );
        it = ComponentToolBarList.erase ( it );
    }

    if ( pcComponentWidget ) {
        delete pcComponentWidget;
        pcComponentWidget = 0;
    }

    pcComponentScroll->generateComponents ( pcActualProject->activeObject() );
    createToolbars();

    if ( pcActualProject->activeObject() ) {
        setEnabled ( true );
        pcAddComponentMenu->setEnabled ( true );
    } else {
        pcAddComponentMenu->setDisabled ( true );
        setDisabled ( true );
    }
}

void PComponentsWidget::addComponent ( QString name ) {
    QString comp_name = name.split ( ". " ).at ( 1 );
    BackGenEngine::BAbstractComponent *pc_component = pcActualProject->project()->getModuleSystem()->createComponent ( comp_name.toStdString().c_str(), pcActualProject->actualScene() );

    if ( ! pcActualProject->activeObject()->insertComponent ( pc_component ) ) {
        return;
    }

    pcComponentScroll->addComponent ( comp_name );


    // toolbars
    PComponentToolbar *pc_toolbar;
    PModulesSystem::component_toolbar_hash_t::ConstIterator it = pcActualProject->moduleSystem()->componentToolBarHash().constBegin();
    while ( it !=  pcActualProject->moduleSystem()->componentToolBarHash().constEnd() ) {
        if ( ( *it )->componentType() == comp_name ) {
            pc_toolbar = ( *it )->create ( pc_component, pcMainWindow, pcActualProject );
            ComponentToolBarList.append ( pc_toolbar );
            pcMainWindow->addToolBar ( pc_toolbar );
        }
        ++it;
    }

    pcActualProject->changeObject ( pcActualProject->activeObject()->getName().constData(), pcActualProject->activeObject() );
}

