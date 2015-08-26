#include "../../include/assets/asseteditdockwidget.h"
#include "ui_asseteditdockwidget.h"

#include <BackGenEngine/babstractasset.h>

#include <PlaygroundSDK/pmodulessystem.h>
#include <PlaygroundSDK/passeteditwidgetmodule.h>
#include <PlaygroundSDK/pactualproject.h>

#include "./include/assets/pdefaulteditassetwidget.h"

AssetEditDockWidget::AssetEditDockWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *actual_project, QWidget *parent ) :
    QDockWidget ( parent ),
    ui ( new Ui::AssetEditDockWidget ),  pcAsset ( pc_asset ), pcActualProject ( actual_project ), pcMainWidget ( 0 ) {
    ui->setupUi ( this );

    pcDefaultWidget = new PDefaultEditAssetWidget ( pc_asset, actual_project );
    ui->verticalLayout->addWidget ( pcDefaultWidget );
    pcDefaultWidget->restore();

    PModulesSystem::asset_edit_widget_hash_t::ConstIterator it = pcActualProject->moduleSystem()->assetEditWidgetHash().constBegin();
    while ( it != pcActualProject->moduleSystem()->assetEditWidgetHash().constEnd() ) {
        if ( ( *it )->assetType() == pc_asset->getAssetType().constData() ) {
            setAssetWidget ( ( *it )->create ( pc_asset, actual_project ) );
            break;
        }

        ++it;
    }

    setWindowTitle ( pc_asset->getName().constData() );

    connect ( ui->buttonBox, SIGNAL ( clicked ( QAbstractButton * ) ), this, SLOT ( buttonClicked ( QAbstractButton * ) ) );

    connect ( actual_project, SIGNAL ( assetChanged ( QString, BackGenEngine::BAbstractAsset * ) ),
              this, SLOT ( assetChanged ( QString, BackGenEngine::BAbstractAsset * ) ) );
}

AssetEditDockWidget::~AssetEditDockWidget() {
    delete ui;
}

void AssetEditDockWidget::setAssetWidget ( PAssetEditWidget *pc_widget ) {
    if ( pcMainWidget ) {
        delete pcMainWidget;
    }

    pcMainWidget = pc_widget;

    if ( pcMainWidget ) {
        ui->verticalLayout->addWidget ( pc_widget );
        pcAsset->use();
        pc_widget->restore();
        pcAsset->unuse();
    }
}

void AssetEditDockWidget::closeEvent ( QCloseEvent *event ) {
    ( void ) event;
    delete this;
}

void AssetEditDockWidget::buttonClicked ( QAbstractButton *pc_button ) {
    switch ( ui->buttonBox->buttonRole ( pc_button ) ) {
        case QDialogButtonBox::ApplyRole:
            pcDefaultWidget->apply();

            if ( pcMainWidget ) {
                pcMainWidget->apply();
            }

            pcAsset->save();

            pcActualProject->changeAsset ( pcAsset->getName().constData(), pcAsset );
            pcAsset->realod();
            break;

        case QDialogButtonBox::ResetRole:
            pcDefaultWidget->restore();

            if ( pcMainWidget ) {
                pcAsset->use();
                pcMainWidget->restore();
                pcAsset->unuse();
            }
            pcActualProject->changeAsset ( pcAsset->getName().constData(), pcAsset );
            pcAsset->realod();
            break;

        default:
            break;
    }
}

void AssetEditDockWidget::assetChanged ( QString old_name, BackGenEngine::BAbstractAsset *pc_asset ) {

    if ( pcAsset != pc_asset ) {
        return;
    }

    pcDefaultWidget->restore();
    if ( pcMainWidget ) {
        pcMainWidget->restore();
    }
}
