#include "../../include/assets/pdefaulteditassetwidget.h"
#include "ui_pdefaulteditassetwidget.h"

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bdynamicmodulesystem.h>
#include <BackGenEngine/bassetloadermodule.h>

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

#include <PlaygroundSDK/pactualproject.h>

PDefaultEditAssetWidget::PDefaultEditAssetWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QWidget *parent ) :
    PAssetEditWidget ( pc_asset, pc_project, parent ),
    ui ( new Ui::PDefaultEditAssetWidget ) {
    ui->setupUi ( this );

    generateSuportedFormats();

    connect ( ui->OpenAssetButton, SIGNAL ( clicked() ), this, SLOT ( openFile() ) );
}

PDefaultEditAssetWidget::~PDefaultEditAssetWidget() {
    delete ui;
}

QLayout *PDefaultEditAssetWidget::getMainLayout() {
    return  ui->verticalLayout;
}


void PDefaultEditAssetWidget::ok() {
    apply();
}

void PDefaultEditAssetWidget::apply() {
    if ( parseName() ) {
        QString old_name = asset()->getName().constData();
        asset()->setName ( ui->NameLineEdit->text().toStdString().c_str() );
        project()->changeAsset ( old_name , asset() );
    }

    asset()->setPath ( ui->PathLineEdit->text().toStdString().c_str() );
}

void PDefaultEditAssetWidget::cancle() {

}

void PDefaultEditAssetWidget::restore() {
    ui->NameLineEdit->setText ( asset()->getName().constData() );
    ui->PathLineEdit->setText ( asset()->getPath().constData() );
}

void PDefaultEditAssetWidget::generateSuportedFormats() {
    SuportedFormats.clear();

    BackGenEngine::BDynamicModuleSystem *pc_modules_system = ( BackGenEngine::BDynamicModuleSystem * ) project()->project()->getModuleSystem();
    BackGenEngine::BDynamicModuleSystem::asset_loader_module_hash_t::ConstIterator it = pc_modules_system->getAssetLoaderHash().constBegin();

    while ( it != pc_modules_system->getAssetLoaderHash().constEnd() ) {
        if ( ( *it )->getAssetType() == asset()->getAssetType() ) {
            QString str ( QString ( "%1 (*.%1) (*.%1);;" ).arg ( it.key().constData() ) );
            SuportedFormats.append ( str );
        }
        ++it;
    }
}

bool PDefaultEditAssetWidget::parseName() {
    if ( asset()->getName() == ui->NameLineEdit->text().toStdString().c_str() ) {
        return false;
    }

    if ( ui->NameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Asset" ),
                               tr ( "Asset have empty name. Please set name." ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( asset()->getName().constData() );
        return false;
    }

    if ( project()->project()->getAssetManager().containAsset ( ui->NameLineEdit->text().toStdString().c_str() ) ) {
        QMessageBox::warning ( this, tr ( "Object" ),
                               tr ( "Asset with this name is exist. Please set name." ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( asset()->getName().constData() );
        return false;
    }

    return true;
}

void makeDirSceleton ( QString base_dir_str, QString asset_type ) {
    // Data dir
    QDir base_dir ( base_dir_str );
    base_dir.mkdir ( "data" );
    base_dir.mkdir ( "data/assets" );
    base_dir.mkdir ( QString ( "data/assets/%1" ).arg ( asset_type.toLower() ) );
}

void PDefaultEditAssetWidget::openFile() {
    QString file_name = QFileDialog::getOpenFileName (  this, tr ( "Open asset.." ), QString(), SuportedFormats  );

    if ( file_name.isEmpty()  ) {
        return;
    }

    QFileInfo file_info ( file_name );

    QString base_dir_str ( project()->project()->getBaseDir().constData() );
    if ( !base_dir_str.endsWith ( '/' ) ) {
        base_dir_str.append ( '/' );
    }

    QString asset_type ( asset()->getAssetType().constData() );

    QString short_filename = file_info.fileName();
    QString full_path ( QString ( "%1data/assets/%2/%3" ).arg ( base_dir_str ).arg ( asset_type.toLower() ).arg ( short_filename ) );

    makeDirSceleton ( base_dir_str, asset()->getAssetType().constData() );

    QFile file ( full_path );
    if ( file.exists() ) {
        int ret = QMessageBox::question ( this, "Asset exist", "Asset is exist, replace it?", QMessageBox::Ok | QMessageBox::Cancel );

        if ( ret == QMessageBox::Ok ) {
            QFile::copy ( file_name, full_path );
        } else {
            return;
        }

    } else {
        QFile::copy ( file_name, full_path );
    }

    ui->PathLineEdit->setText ( short_filename );

}
