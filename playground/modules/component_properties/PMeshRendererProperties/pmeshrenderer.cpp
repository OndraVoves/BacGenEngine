#include "pmeshrenderer.h"
#include "ui_pmeshrenderer.h"


#include <BackGenEngine/bproject.h>
#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bassetmanager.h>

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/modulesheader.h>

#include <BMaterialAsset.h>
#include <BMeshRendererComponent.h>

PMeshRenderer::PMeshRenderer ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project ) :
    PComponentProperties ( pc_component, pc_actual_project ),
    ui ( new Ui::PMeshRenderer ) {
    pcComponent = ( BMeshRendererComponent * ) pc_component;

    ui->setupUi ( this );

    updateData();

    connect ( ui->MeshAssetComboBox, SIGNAL ( currentIndexChanged ( int ) ), this, SLOT ( materialAssetItemChanged ( int ) ) );
    connect ( ui->TXSpinBox, SIGNAL ( valueChanged ( int ) ), this, SLOT ( changeTX ( int ) ) );
    connect ( ui->TYSpinBox, SIGNAL ( valueChanged ( int ) ), this, SLOT ( changeTY ( int ) ) );
}

PMeshRenderer::~PMeshRenderer() {
    delete ui;
}

void PMeshRenderer::updateData() {
    generateMaterialsItems();

    ui->TXSpinBox->setValue ( pcComponent->getTiling().x() );
    ui->TYSpinBox->setValue ( pcComponent->getTiling().y() );
}

void PMeshRenderer::changeEvent ( QEvent *e ) {
    QWidget::changeEvent ( e );
    switch ( e->type() ) {
        case QEvent::LanguageChange:
            ui->retranslateUi ( this );
            break;
        default:
            break;
    }
}

void PMeshRenderer::generateMaterialsItems() {
    ui->MeshAssetComboBox->clear();

    ui->MeshAssetComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );

    BackGenEngine::BAssetManager::asset_hash_t::ConstIterator it = project()->project()->getAssetManager().constBegin();
    while ( it != project()->project()->getAssetManager().constEnd() ) {
        if ( ( *it )->getInterfaceType() ==  "Material" ) {
            ui->MeshAssetComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );
        }

        ++it;
    }

    if ( pcComponent->getMaterialAsset() ) {
        ui->MeshAssetComboBox->setCurrentIndex ( ui->MeshAssetComboBox->findText ( pcComponent->getMaterialAsset()->getName().constData() ) );
    } else {
        ui->MeshAssetComboBox->setCurrentIndex ( 0 );
    }

}

void PMeshRenderer::materialAssetItemChanged ( int index ) {
    pcComponent->setMaterialAsset ( ( BMaterialAsset * ) ui->MeshAssetComboBox->itemData ( index ).value<void *>() );
}

void PMeshRenderer::changeTX ( int x ) {
    BoxE::Math::BVector2f tile = pcComponent->getTiling();
    tile.x ( x );
    pcComponent->setTiling ( tile );
}

void PMeshRenderer::changeTY ( int y ) {
    BoxE::Math::BVector2f tile = pcComponent->getTiling();
    tile.y ( y );
    pcComponent->setTiling ( tile );
}

extern "C" {
    PBASE_MODULE_HEADER ( COMPONENT_PROPERTIES, "MeshRenderer", "0.0.1", "Ondra Voves" );
    PCOMPONENT_PROPERTIES_MODULE_HEADER ( "MeshRenderer" );

    PComponentProperties *createComponentProperties ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project  ) {
        return new PMeshRenderer ( pc_component, pc_actual_project );
    }
}
