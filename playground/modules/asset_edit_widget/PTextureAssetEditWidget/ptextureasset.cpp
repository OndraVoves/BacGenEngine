#include "ptextureasset.h"
#include "ui_ptextureasset.h"

#include <BackGenEngine/bproject.h>
#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bassetmanager.h>

#include <PlaygroundSDK/modulesheader.h>
#include <PlaygroundSDK/pactualproject.h>


#include <BImageAsset.h>
#include <BTextureAsset.h>

PTextureAsset::PTextureAsset ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) :
    PAssetEditWidget ( pc_asset, pc_project ),
    ui ( new Ui::PTextureAsset ) {

    pcTexture = ( BTextureAsset * ) pc_asset;

    ui->setupUi ( this );
}

PTextureAsset::~PTextureAsset() {
    delete ui;
}

void PTextureAsset::ok() {

}

void PTextureAsset::apply() {
    pcTexture->setFilterType ( ( BackGenEngine::BAbstractTexture::ETextureFilterType ) ui->FilterTypeComboBox->currentIndex() );
    pcTexture->setImage ( ( BImageAsset * ) ui->ImageComboBox->itemData ( ui->ImageComboBox->currentIndex() ).value<void *>() );
    pcTexture->setMipmaping ( ui->MipmapingCheckBox->isChecked() );

    pcTexture->generateTexture();
}

void PTextureAsset::cancle() {

}

void PTextureAsset::restore() {
    generateImageAssetsItems();
    ui->FilterTypeComboBox->setCurrentIndex ( pcTexture->getFilterType() );
    ui->MipmapingCheckBox->setChecked ( pcTexture->getMipmaping() );
}

void PTextureAsset::changeEvent ( QEvent *e ) {
    QWidget::changeEvent ( e );
    switch ( e->type() ) {
        case QEvent::LanguageChange:
            ui->retranslateUi ( this );
            break;
        default:
            break;
    }
}

void PTextureAsset::generateImageAssetsItems() {
    ui->ImageComboBox->clear();

    ui->ImageComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );

    BackGenEngine::BAssetManager::asset_hash_t::ConstIterator it = project()->project()->getAssetManager().constBegin();
    while ( it != project()->project()->getAssetManager().constEnd() ) {
        if ( ( *it )->getInterfaceType() ==  "Image" ) {
            ui->ImageComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );

            if ( pcTexture->getImage() == ( *it ) ) {
                ui->ImageComboBox->setCurrentIndex ( ui->ImageComboBox->count() - 1 );
            }
        }

        ++it;
    }

}

extern "C" {
    PBASE_MODULE_HEADER ( ASSET_EDIT_WIDGET, "Texture edit widget", "0.0.1", "Ondra Voves" );
    PASSET_EDIT_WIDGET_MODULE_HEADER ( "Texture" );

    PAssetEditWidget *createAssetEditWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) {
        return new PTextureAsset ( pc_asset, pc_project );
    }
}

