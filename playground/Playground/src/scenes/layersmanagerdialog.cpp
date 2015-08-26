#include "../../include/scenes/layersmanagerdialog.h"
#include "ui_layersmanagerdialog.h"

#include <PlaygroundSDK/pactualproject.h>

#include <QMessageBox>
#include <QKeyEvent>

#include <BackGenEngine/bscene.h>
#include <BackGenEngine/blayersmanager.h>

LayersManagerDialog::LayersManagerDialog ( BackGenEngine::BScene *pc_scene, PActualProject *pc_actual_project, QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::LayersManagerDialog ), pcScene ( pc_scene ), pcActualLayer ( 0 ), pcActualProject ( pc_actual_project ) {
    ui->setupUi ( this );

    // TODO
    connect ( ui->LayersListWidget, SIGNAL ( itemActivated ( QListWidgetItem * ) ), this, SLOT ( layerActivated ( QListWidgetItem * ) ) );

    fillLayersList();
}

LayersManagerDialog::~LayersManagerDialog() {
    delete ui;
}

void LayersManagerDialog::keyPressEvent ( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
//        case Qt::Key_Escape:
            break;

        default:
            QDialog::keyPressEvent ( event );
    }

}

void LayersManagerDialog::fillLayersList() {
    BackGenEngine::BLayersManager::blayer_type_hash_t::ConstIterator it1 = pcScene->getLayersManager().layersTypeHash().constBegin();
    BackGenEngine::BLayersManager::blayer_hash_t::ConstIterator it2 ( 0 );
    while ( it1 !=  pcScene->getLayersManager().layersTypeHash().constEnd() ) {
        it2 = ( *it1 )->constBegin();

        while ( it2 != ( *it1 )->constEnd() ) {
            QListWidgetItem *pc_new_item = new QListWidgetItem ( ui->LayersListWidget );

            updateLayerItem ( ( *it2 ), pc_new_item );

            ++it2;
        }

        ++it1;
    }
}

void LayersManagerDialog::updateLayerItem ( BackGenEngine::BLayer *pc_layer, QListWidgetItem *pc_item ) {
    pc_item->setText ( pc_layer->getName().constData() );
    pc_item->setData ( Qt::UserRole, qVariantFromValue ( ( void * ) pc_layer ) );
    pc_item->setIcon ( QIcon ( ":/images/document-multiple.png" ) );
}

void LayersManagerDialog::addNewLayer() {

    QString name ( "NewLayer_1" );

    int i = 2;
    while ( pcScene->getLayersManager().containLayer ( name.toStdString().c_str() ) ) {
        name = QString ( "NewLayer_%1" ).arg ( i );
        i++;
    }

    BackGenEngine::BLayer *pc_new_layer = pcScene->getLayersManager().createLayer ( name.toStdString().c_str(), BackGenEngine::BLayer::NORMAL );

    if ( !pc_new_layer ) {
        QMessageBox::critical ( this, tr ( "Layer manager" ), tr ( "Could not create layer." ), QMessageBox::Ok );
        return;
    }

    QListWidgetItem *pc_new_item = new QListWidgetItem ( ui->LayersListWidget );

    updateLayerItem ( pc_new_layer, pc_new_item );
    pcActualProject->changeLayerManager();
}

void LayersManagerDialog::removeLayer() {
    QListWidgetItem *pc_item = ui->LayersListWidget->selectedItems().first();
    BackGenEngine::BLayer *pc_layer = ( BackGenEngine::BLayer * ) pc_item->data ( Qt::UserRole ).value<void *>();

    int ret = QMessageBox::question ( this, tr ( "Do you really want..." ),
                                      tr ( "Do you really want to delete \"%1\" layer?" ).arg ( pc_layer->getName().constData() ),
                                      QMessageBox::Ok | QMessageBox::Cancel );

    if ( ret == QMessageBox::Cancel ) {
        return;
    }

    pcScene->getLayersManager().removeLayer ( pc_layer );

    delete pc_layer;
    delete pc_item;

    ui->NameLineEdit->setText ( "" );
    ui->NameLineEdit->setDisabled ( true );
    ui->TypeComboBox->setDisabled ( true );
    ui->removePushButton->setEnabled ( false );
    pcActualProject->changeLayerManager();
}

void LayersManagerDialog::setName() {
    QString old_name = pcActualLayer->getName().constData();

    // No name changed.
    if ( old_name == ui->NameLineEdit->text().toStdString().c_str() ) {
        return;
    }

    if ( ui->NameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Layers manager" ),
                               tr ( "Layer name is empty.\nPleas set name" ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( old_name );
        return;
    }

    if ( pcScene->getLayersManager().containLayer ( ui->NameLineEdit->text().toStdString().c_str() ) ) {
        QMessageBox::warning ( this, tr ( "Layers manager" ),
                               tr ( "Layer with this name is exist.\nPleas set name" ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( old_name );
        return;
    }

    QList<QListWidgetItem *> items_list = ui->LayersListWidget->findItems ( old_name, Qt::MatchCaseSensitive );
    if ( items_list.count() != 1 ) {
        return;
    }

    items_list.first()->setText ( ui->NameLineEdit->text() );

    pcActualLayer->setName ( ui->NameLineEdit->text().toStdString().c_str() );
    pcActualProject->changeLayerManager();
}

void LayersManagerDialog::setType ( QString type_name ) {
    if ( type_name == "NORMAL"  ) {
        pcActualLayer->setLayerType ( BackGenEngine::BLayer::NORMAL );
    } else if ( type_name == "TRANSPARENT" ) {
        pcActualLayer->setLayerType ( BackGenEngine::BLayer::TRANSPARENT );
    } else if ( type_name == "GUI" ) {
        pcActualLayer->setLayerType ( BackGenEngine::BLayer::GUI );
    }

    pcActualProject->changeLayerManager();
}

void LayersManagerDialog::layerActivated ( QListWidgetItem *pc_item ) {

    pcActualLayer = ( BackGenEngine::BLayer * ) pc_item->data ( Qt::UserRole ).value<void *>();

    ui->NameLineEdit->setText ( pc_item->text() );

    BackGenEngine::BLayer::ELayerType type = pcActualLayer->getLayerType();
    switch ( type  ) {
        case BackGenEngine::BLayer::NORMAL:
            ui->TypeComboBox->setCurrentIndex ( 0 );
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            ui->TypeComboBox->setCurrentIndex ( 1 );
            break;

        case BackGenEngine::BLayer::GUI:
            ui->TypeComboBox->setCurrentIndex ( 2 );
            break;
    }

    ui->NameLineEdit->setEnabled ( true );
    ui->TypeComboBox->setEnabled ( true );
    ui->removePushButton->setEnabled ( true );
}
