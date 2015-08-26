#include "pmaterialasset.h"
#include "ui_pmaterialasset.h"

#include <BackGenEngine/bproject.h>
#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bassetmanager.h>

#include <PlaygroundSDK/modulesheader.h>
#include <PlaygroundSDK/pactualproject.h>

#include <BMaterialAsset.h>

PMaterialAsset::PMaterialAsset ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) :
    PAssetEditWidget ( pc_asset, pc_project ),
    ui ( new Ui::PMaterialAsset ) {
    pcMaterial = ( BMaterialAsset * ) pc_asset;

    ui->setupUi ( this );
}

PMaterialAsset::~PMaterialAsset() {
    delete ui;
}

void PMaterialAsset::ok() {

}

void PMaterialAsset::apply() {
    pcMaterial->setTextureUnit ( 0, ( BTextureAsset * ) ui->Unit0ComboBox->itemData ( ui->Unit0ComboBox->currentIndex() ).value<void *>() );
    pcMaterial->setTextureUnit ( 1, ( BTextureAsset * ) ui->Unit1ComboBox->itemData ( ui->Unit1ComboBox->currentIndex() ).value<void *>() );
    pcMaterial->setTextureUnit ( 2, ( BTextureAsset * ) ui->Unit2ComboBox->itemData ( ui->Unit2ComboBox->currentIndex() ).value<void *>() );
    pcMaterial->setTextureUnit ( 3, ( BTextureAsset * ) ui->Unit3ComboBox->itemData ( ui->Unit3ComboBox->currentIndex() ).value<void *>() );
}

void PMaterialAsset::cancle() {

}

void PMaterialAsset::restore() {
    generateUnitItems();
}

void PMaterialAsset::changeEvent ( QEvent *e ) {
    QWidget::changeEvent ( e );
    switch ( e->type() ) {
        case QEvent::LanguageChange:
            ui->retranslateUi ( this );
            break;
        default:
            break;
    }
}

void PMaterialAsset::generateUnitItems() {
    ui->Unit0ComboBox->clear();
    ui->Unit1ComboBox->clear();
    ui->Unit2ComboBox->clear();
    ui->Unit3ComboBox->clear();

    ui->Unit0ComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );
    ui->Unit1ComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );
    ui->Unit2ComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );
    ui->Unit3ComboBox->addItem ( tr ( "None" ), qVariantFromValue ( ( void * ) 0 )  );

    BackGenEngine::BAssetManager::asset_hash_t::ConstIterator it = project()->project()->getAssetManager().constBegin();
    while ( it != project()->project()->getAssetManager().constEnd() ) {
        if ( ( *it )->getInterfaceType() ==  "Texture" ) {
            ui->Unit0ComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );
            ui->Unit1ComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );
            ui->Unit2ComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );
            ui->Unit3ComboBox->addItem ( ( *it )->getName().constData(), qVariantFromValue ( ( void * ) ( *it ) )  );


            if ( pcMaterial->getTextureUnit ( 0 ) == ( *it ) ) {
                ui->Unit0ComboBox->setCurrentIndex ( ui->Unit0ComboBox->count() - 1 );

            } else if ( pcMaterial->getTextureUnit ( 1 ) == ( *it ) ) {
                ui->Unit1ComboBox->setCurrentIndex ( ui->Unit1ComboBox->count() - 1 );

            } else if ( pcMaterial->getTextureUnit ( 2 ) == ( *it ) ) {
                ui->Unit2ComboBox->setCurrentIndex ( ui->Unit2ComboBox->count() - 1 );

            } else if ( pcMaterial->getTextureUnit ( 3 ) == ( *it ) ) {
                ui->Unit3ComboBox->setCurrentIndex ( ui->Unit3ComboBox->count() - 1 );
            }
        }

        ++it;
    }
}

extern "C" {
    PBASE_MODULE_HEADER ( ASSET_EDIT_WIDGET, "Material edit widget", "0.0.1", "Ondra Voves" );
    PASSET_EDIT_WIDGET_MODULE_HEADER ( "Material" );

    PAssetEditWidget *createAssetEditWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) {
        return new PMaterialAsset ( pc_asset, pc_project );
    }
}
