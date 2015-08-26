#include "../include/pscrollcomponentswidget.h"

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pmodulessystem.h>

#include <PlaygroundSDK/pcomponentproperties.h>
#include <PlaygroundSDK/pcomponentpropertiesmodule.h>
#include <PlaygroundSDK/pmyaction.h>

#include <BackGenEngine/bobject.h>

#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


PScrollComponentsWidget::PScrollComponentsWidget ( PActualProject *actual_project ) :
    QScrollArea ( 0 ), pcActualProject ( actual_project ) {

    setWidgetResizable ( true );
    setFrameShape ( QFrame::NoFrame );

    QWidget *pc_main_widget = new QWidget();
    pcMainVLayout = new QVBoxLayout();
    pc_main_widget->setLayout ( pcMainVLayout );

    setWidget ( pc_main_widget );

}

void PScrollComponentsWidget::generateComponents ( BackGenEngine::BObject *pc_object ) {
    clear();

    pcObject = pc_object;

    if ( !pc_object ) {
        return;
    }

    BackGenEngine::BObject::component_vector_t::ConstIterator it = pc_object->getComponentVector().constBegin();
    while ( it != pc_object->getComponentVector().constEnd() ) {
        addComponent ( ( *it )->getName().constData() );

        ++it;
    }


}

void PScrollComponentsWidget::updateComponent ( QString name ) {
    QHash< QString, PComponentProperties *>::Iterator it = ComponentPropertiesHash.find ( name );
    if ( it != ComponentPropertiesHash.end() ) {
        ( *it )->updateData();
    }
}

void PScrollComponentsWidget::addComponent (  QString name  ) {
    BackGenEngine::BAbstractComponent *pc_component = pcObject->getComponentByName ( name.toStdString().c_str() );

    PMyAction *pc_my_act = new PMyAction();
    connect ( pc_my_act, SIGNAL ( activated ( QString ) ), this, SLOT ( removeAction ( QString ) )  );

    PMyAction *pc_my_act2 = new PMyAction();
    connect ( pc_my_act2, SIGNAL ( activated ( QString ) ), this, SLOT ( clickAction ( QString ) )  );

    QPushButton *pc_push_button =  new QPushButton ( QIcon ( QString ( "./images/components/%1.png" ).arg ( pc_component->getName().constData() ) ) , pc_component->getName().constData() );
    pc_push_button->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
    connect ( pc_push_button, SIGNAL ( clicked() ), pc_my_act2, SLOT ( onActivated() ) );

    QPushButton *pc_remove_component = new QPushButton ( QIcon ( ":images/component-remove.png" ), QString() );
    pc_remove_component->setSizePolicy ( QSizePolicy::Minimum, QSizePolicy::Fixed );

    connect ( pc_remove_component, SIGNAL ( clicked() ), pc_my_act, SLOT ( onActivated() ) );

    pc_my_act2->setText ( pc_component->getName().constData()  );
    pc_my_act->setText ( pc_component->getName().constData()  );

    QHBoxLayout *pc_buttons_layout = new QHBoxLayout();
    pc_buttons_layout->addWidget ( pc_push_button );
    pc_buttons_layout->addWidget ( pc_remove_component );

    pcMainVLayout->addLayout ( pc_buttons_layout );

    ComponentHBoxHash.insert ( pc_component->getName().constData(), pc_buttons_layout );

    PModulesSystem::component_properties_hash_t::ConstIterator it2 = pcActualProject->moduleSystem()->componentPropertiesHash().constBegin();
    while ( it2 != pcActualProject->moduleSystem()->componentPropertiesHash().constEnd() ) {
        if ( ( *it2 )->componentType() == pc_component->getName() ) {
            PComponentProperties *pc_component_widget = ( *it2 )->create ( pc_component, pcActualProject );
            pc_component_widget->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Minimum );

            pcMainVLayout->addWidget ( pc_component_widget );

            ComponentPropertiesHash.insert ( pc_component->getName().constData(), pc_component_widget );
            break;
        }

        ++it2;
    }
}

void PScrollComponentsWidget::clickAction ( QString component ) {
    QHash< QString, PComponentProperties *>::Iterator it = ComponentPropertiesHash.find ( component );
    if ( it != ComponentPropertiesHash.end() ) {
        if ( ( *it )->isHidden() ) {
            ( *it )->show();
        } else {
            ( *it )->hide();
        }

    }
}

void PScrollComponentsWidget::clear() {
    QHash< QString, QHBoxLayout *>::Iterator it2 = ComponentHBoxHash.begin();
    while ( it2 != ComponentHBoxHash.end() ) {
        QHBoxLayout *pc_l = ( *it2 );

        for ( int i = 0; i < pc_l->count(); i++ ) {
            pc_l->itemAt ( i )->widget()->close();
        }

        delete ( *it2 );

        it2 = ComponentHBoxHash.erase ( it2 );
    }

    QHash< QString, PComponentProperties *>::Iterator it = ComponentPropertiesHash.begin();
    while ( it != ComponentPropertiesHash.end() ) {
        delete ( *it );

        it = ComponentPropertiesHash.erase ( it );
    }

}

void PScrollComponentsWidget::removeAction ( QString component ) {
    QHash< QString, QHBoxLayout *>::Iterator it2 = ComponentHBoxHash.find ( component );
    if ( it2 != ComponentHBoxHash.end() ) {
        QHBoxLayout *pc_l = ( *it2 );

        for ( int i = 0; i < pc_l->count(); i++ ) {
            pc_l->itemAt ( i )->widget()->close();
        }

        delete ( *it2 );

        ComponentHBoxHash.erase ( it2 );
    }

    QHash< QString, PComponentProperties *>::Iterator it = ComponentPropertiesHash.find ( component );
    if ( it != ComponentPropertiesHash.end() ) {
        delete ( *it );

        ComponentPropertiesHash.erase ( it );
    }


    BackGenEngine::BAbstractComponent *pc_component = pcObject->getComponentByName ( component.toStdString().c_str() );
    pcObject->removeComponent (  pc_component );

    delete pc_component;

}
