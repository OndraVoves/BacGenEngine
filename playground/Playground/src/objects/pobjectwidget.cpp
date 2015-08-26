#include "../../include/objects/pobjectwidget.h"

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/btagsmanager.h>
#include <BackGenEngine/blayersmanager.h>

#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include <QSpacerItem>
#include <QGroupBox>
#include <QScrollArea>

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pmyaction.h>

#include "../../include/components/pcomponentswidget.h"
#include "./include/scenes/layersmanagerdialog.h"
#include "./include/scenes/ptagsmanagerdialog.h"

PObjectWidget::PObjectWidget (  MainWindow *main_window, PActualProject *actual_project, QWidget *parent ) :
    QWidget ( parent ),  pcMainWindow ( main_window ), pcActualProject ( actual_project ), pcObject ( 0 ) {
    QVBoxLayout *pc_v_main_layout = new QVBoxLayout();


    QGroupBox *pc_object_box = new QGroupBox ( tr ( "Properties" ) );
    QVBoxLayout *pc_v_object_layout = new QVBoxLayout();
    pc_object_box->setLayout ( pc_v_object_layout );
    pc_v_main_layout->addWidget ( pc_object_box );

    // Name.
    QHBoxLayout *pc_h_name_layout = new QHBoxLayout();
    pc_h_name_layout->addWidget ( new QLabel ( tr ( "Name:" ) ) );

    pcNameLineEdit = new QLineEdit();
    connect ( pcNameLineEdit, SIGNAL ( editingFinished() ), this, SLOT ( nameChanged() ) );
    pc_h_name_layout->addWidget ( pcNameLineEdit );

    // Layer.
    QHBoxLayout *pc_h_layer_layout = new QHBoxLayout();
    pc_h_layer_layout->addWidget ( new QLabel ( "Layer:" ) );

    pcLayerComboBox = new QComboBox();
    pcLayerComboBox->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
    connect ( pcLayerComboBox, SIGNAL ( activated ( int ) ), this, SLOT ( layerChanged ( int ) ) );
    pc_h_layer_layout->addWidget ( pcLayerComboBox );

    QPushButton *pc_edit_layers = new QPushButton ( tr ( "Edit" ), this );
    pc_h_layer_layout->addWidget ( pc_edit_layers );
    connect ( pc_edit_layers, SIGNAL ( clicked() ), this, SLOT ( openLayersManager() ) );

    //Tags.
    QHBoxLayout *pc_h_tag_layer = new QHBoxLayout();
    pcTagsMenu = new QMenu();
    QToolButton *pc_tag_button = new QToolButton();
    pc_tag_button->setText ( tr ( "Tags" ) );
    pc_tag_button->setPopupMode ( QToolButton::InstantPopup );
    pc_tag_button->setMenu ( pcTagsMenu );
    pc_tag_button->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
    pc_h_tag_layer->addWidget ( pc_tag_button );

    QPushButton *pc_edit_tags = new QPushButton ( tr ( "Edit" ), this );
    pc_h_tag_layer->addWidget ( pc_edit_tags );
    connect ( pc_edit_tags, SIGNAL ( clicked() ), this, SLOT ( openTagsManager() ) );

    pc_v_object_layout->addLayout ( pc_h_name_layout );
    pc_v_object_layout->addLayout ( pc_h_layer_layout );
    pc_v_object_layout->addLayout ( pc_h_tag_layer );

    // Components
    QGroupBox *pc_components_box = new QGroupBox ( tr ( "Components" ) );
    QVBoxLayout *pc_v_components_layout = new QVBoxLayout();

    pcComponentsWidget = new PComponentsWidget ( pcMainWindow, pcActualProject );
    pc_components_box->setLayout ( pc_v_components_layout );
    pc_v_components_layout->addWidget ( pcComponentsWidget );

    pc_v_main_layout->addWidget ( pc_components_box );

    //QSpacerItem *pc_spacer = new QSpacerItem ( 0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding );
    //pc_v_main_layout->addItem ( pc_spacer );

    setEnabled ( false );
    setLayout ( pc_v_main_layout );


    connect ( pcActualProject, SIGNAL ( objectActivated() ), this, SLOT ( objectActivated() ) );
    connect ( pcActualProject, SIGNAL ( layerManagerChanged() ), this, SLOT ( layerManagerChanged() )  );
    connect ( pcActualProject, SIGNAL ( tagManagerChanged() ), this, SLOT ( tagManagerChanged() ) );
}

PObjectWidget::~PObjectWidget() {
    delete pcComponentsWidget;
}

void PObjectWidget::setLayer() {
    if ( pcObject == 0 ) {
        return;
    }

    if ( pcObject->layer() ) {
        pcLayerComboBox->setCurrentIndex ( pcLayerComboBox->findText ( pcObject->layer()->getName().constData()  ) );
    } else {
        pcLayerComboBox->setCurrentIndex ( pcLayerComboBox->findText ( tr ( "None" ) ) );
    }
}

void PObjectWidget::setTag() {
    if ( pcObject == 0 ) {
        return;
    }

    QList< QAction * >::ConstIterator it = pcTagsMenu->actions().constBegin();

    BackGenEngine::BTag *pc_tag = 0;
    while ( it != pcTagsMenu->actions().constEnd() ) {
        pc_tag = ( BackGenEngine::BTag * ) ( *it )->data().value<void *>();

        if ( pc_tag->containObject ( pcObject ) ) {
            ( *it )->setChecked ( true );
        } else {
            ( *it )->setChecked ( false );
        }

        ++it;
    }

}

void PObjectWidget::objectActivated() {
    pcObject = pcActualProject->activeObject();

    if ( pcObject == 0 ) {
        setEnabled ( false );
        return;
    }

    pcNameLineEdit->setText ( pcObject->getName().constData() );
    generateLayerComboBoxItem();
    generateTagMenu();

    setEnabled ( true );
    setLayer();
    setTag();
}

void PObjectWidget::nameChanged() {
    if ( pcObject == 0 ) {
        return;
    }

    QString old_name (  pcObject->getName().constData() );

    if ( old_name == pcNameLineEdit->text().toStdString().c_str() ) {
        return;
    }

    // Empty name.
    if ( pcNameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Object" ),
                               tr ( "Object have empty name. Please set name." ), QMessageBox::Ok );

        pcNameLineEdit->setText ( old_name );
        return;
    }

    // Exist name.
    if ( pcActualProject->actualScene()->getTagsManager().rootTag().containObject ( pcNameLineEdit->text().toStdString().c_str() ) ) {
        QMessageBox::warning ( this, tr ( "Object" ),
                               tr ( "Object with this name is exist. Please set name." ), QMessageBox::Ok );

        pcNameLineEdit->setText ( old_name );
        return;
    }

    pcObject->setName ( pcNameLineEdit->text().toStdString().c_str() );
    pcActualProject->changeObject ( old_name, pcObject );
}

void PObjectWidget::layerChanged ( int index ) {
    if ( pcObject == 0 ) {
        return;
    }

    BackGenEngine::BLayer *pc_layer = ( ( BackGenEngine::BLayer * ) pcLayerComboBox->itemData ( index ).value<void *>() );

    if ( pc_layer ) {
        pc_layer->insertObject ( pcObject );

    } else {
        if ( pcObject->layer() ) {
            pcObject->layer()->removeObject ( pcObject );
        }
    }

    pcActualProject->changeObject ( pcObject->getName().constData(), pcObject );
}

void PObjectWidget::generateLayerComboBoxItem() {
    pcLayerComboBox->clear();

    pcLayerComboBox->addItem ( QIcon ( ":/images/document-multiple.png" ), tr ( "None" ),
                               qVariantFromValue ( ( void * ) 0 ) );

    BackGenEngine::BLayersManager::blayer_type_hash_t::ConstIterator it1 = pcActualProject->actualScene()->getLayersManager().layersTypeHash().constBegin();
    BackGenEngine::BLayersManager::blayer_hash_t::ConstIterator it2 = BackGenEngine::BLayersManager::blayer_hash_t::ConstIterator ( 0 );
    while ( it1 !=  pcActualProject->actualScene()->getLayersManager().layersTypeHash().constEnd() ) {
        it2 = ( *it1 )->constBegin();

        while ( it2 != ( *it1 )->constEnd() ) {
            pcLayerComboBox->addItem ( QIcon ( ":/images/document-multiple.png" ), ( *it2 )->getName().constData(),
                                       qVariantFromValue ( ( void * ) ( *it2 ) ) );

            ++it2;
        }

        ++it1;
    }
}

void PObjectWidget::generateTagMenu() {
    pcTagsMenu->clear();

    BackGenEngine::BTagsManager::btag_hash_t::ConstIterator it = pcActualProject->actualScene()->getTagsManager().tagsHash().constBegin();
    while ( it != pcActualProject->actualScene()->getTagsManager().tagsHash().constEnd() ) {
        PMyAction *pc_new_action = new PMyAction ( pcTagsMenu );
        pc_new_action->setText ( ( *it )->getName().constData() );
        pc_new_action->setCheckable ( true );
        pc_new_action->setData ( qVariantFromValue ( ( void * ) *it ) );
        pc_new_action->setIcon ( QIcon ( ":/images/mail-tagged.png" ) );

        connect ( pc_new_action, SIGNAL ( toggled ( PMyAction *, bool ) ), this, SLOT ( tagToggled ( PMyAction *, bool ) ) );

        pcTagsMenu->addAction ( pc_new_action );

        ++it;
    }
}

void PObjectWidget::openLayersManager() {
    LayersManagerDialog dialog ( pcActualProject->actualScene(), pcActualProject, this );
    dialog.exec();
}

void PObjectWidget::openTagsManager() {
    PTagsManagerDialog dialog ( pcActualProject->actualScene(), pcActualProject, this );
    dialog.exec();
}

void PObjectWidget::layerManagerChanged() {
    generateLayerComboBoxItem();
    setLayer();
}

void PObjectWidget::tagManagerChanged() {
    generateTagMenu();
    setTag();
}

void PObjectWidget::tagToggled ( PMyAction *pc_action, bool toggled ) {
    BackGenEngine::BTag *pc_tag = ( ( BackGenEngine::BTag * ) pc_action->data().value<void *>() );

    if ( toggled ) {
        pc_tag->insertObject ( pcObject );
    } else {
        pc_tag->removeObject ( pcObject );
    }

    pcActualProject->changeObject ( pcObject->getName().constData(), pcObject );
}
