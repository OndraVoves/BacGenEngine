#include "pimage.h"
#include "ui_pimage.h"

#include <PlaygroundSDK/modulesheader.h>
#include <PlaygroundSDK/pactualproject.h>

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bdynamicmodulesystem.h>

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

#include <BImageAsset.h>


Pimage::Pimage ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) :
    PAssetEditWidget ( pc_asset, pc_project ),
    ui ( new Ui::Pimage ) {
    ui->setupUi ( this );

    pcImageAsset = ( BImageAsset * ) pc_asset;

}

Pimage::~Pimage() {
    delete ui;
}

void Pimage::changeEvent ( QEvent *e ) {
    QWidget::changeEvent ( e );
    switch ( e->type() ) {
        case QEvent::LanguageChange:
            ui->retranslateUi ( this );
            break;
        default:
            break;
    }
}

void Pimage::ok() {

}

void Pimage::apply() {
    asset()->realod();
}

void Pimage::cancle() {

}

void Pimage::restore() {
    ui->widthLabel->setText ( QString ( "%1" ).arg ( pcImageAsset->width() ) );
    ui->heightLabel->setText ( QString ( "%1" ).arg ( pcImageAsset->height() ) );
    ui->bppLabel->setText ( QString ( "%1" ).arg ( pcImageAsset->bpp() ) );

    if ( pcImageAsset->pixels() ) {
        QPixmap pixmap;
        QImage image ( pcImageAsset->pixels(), pcImageAsset->width(), pcImageAsset->height(), QImage::Format_RGB888 );

        image = image.scaled ( 128, 128, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
        pixmap.convertFromImage ( image );

        ui->PreviewLabel->setPixmap ( pixmap );
    }
}


extern "C" {
    PBASE_MODULE_HEADER ( ASSET_EDIT_WIDGET, "Image edit widget", "0.0.1", "Ondra Voves" );
    PASSET_EDIT_WIDGET_MODULE_HEADER ( "Image" );

    PAssetEditWidget *createAssetEditWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project ) {
        return new Pimage ( pc_asset, pc_project );
    }
}
