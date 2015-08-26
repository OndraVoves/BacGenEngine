#include "../../include/modules/pmodulessettingsdialog.h"
#include "ui_pmodulessettingsdialog.h"

#include <PlaygroundSDK/pactualproject.h>
#include <PlaygroundSDK/pmodulessystem.h>
#include <PlaygroundSDK/psettingmodule.h>

#include <QAbstractButton>
#include <QKeyEvent>

#include "./include/modules/pmodulessettings.h"
#include "./include/assets/passetsettings.h"
#include "../../pgeneralsettings.h"

PModulesSettingsDialog::PModulesSettingsDialog ( MainWindow *pc_main_window, PActualProject *pc_actual_project, QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::PModulesSettingsDialog ), pcActualPoject ( pc_actual_project ), pcActualTabWidget ( 0 ), pcMainWindow ( pc_main_window ) {
    ui->setupUi ( this );

    ui->ItemListWidget->setItemSelected ( ui->ItemListWidget->item ( 0 ), true );
    itemSelected ( ui->ItemListWidget->item ( 0 ) );

    // MODULES
    PModulesSystem::setting_tab_hash_t::ConstIterator it = pcActualPoject->moduleSystem()->settingTabHash().constBegin();
    while ( it != pcActualPoject->moduleSystem()->settingTabHash().constEnd() ) {
        QListWidgetItem *pc_item = new QListWidgetItem( );
        pc_item->setText ( it.key() );
        ui->ItemListWidget->addItem ( pc_item );
        ++it;
    }

    connect ( ui->ItemListWidget, SIGNAL ( itemActivated ( QListWidgetItem * ) ), this, SLOT ( itemSelected ( QListWidgetItem * ) ) );
    connect ( ui->buttonBox, SIGNAL ( clicked ( QAbstractButton * ) ), this, SLOT ( buttonClicked ( QAbstractButton * ) ) );

}

PModulesSettingsDialog::~PModulesSettingsDialog() {
    if ( pcActualTabWidget ) {
        pcActualTabWidget->save();
        delete pcActualTabWidget;
    }

    delete ui;
}

void PModulesSettingsDialog::keyPressEvent ( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            //case Qt::Key_Escape:
            break;

        default:
            QDialog::keyPressEvent ( event );
    }

}

void PModulesSettingsDialog::loadSettings() {

}

void PModulesSettingsDialog::itemSelected ( QListWidgetItem *pc_item ) {
    if ( pcActualTabWidget ) {
        pcActualTabWidget->save();
        delete pcActualTabWidget;
    }

    if ( pc_item->text() == tr ( "General" ) ) {
        pcActualTabWidget = new PGeneralSettings ( pcMainWindow, pcActualPoject, this );

    } else if ( pc_item->text() == tr ( "Modules" )  ) {
        pcActualTabWidget = new PModulesSettings ( pcMainWindow, pcActualPoject );

    } else if ( pc_item->text() == tr ( "Assets" ) ) {
        pcActualTabWidget = new PAssetSettings ( pcMainWindow, pcActualPoject );

    } else {
        PModulesSystem::setting_tab_hash_t::ConstIterator it = pcActualPoject->moduleSystem()->settingTabHash().find (  pc_item->text()  );
        PSettingTabWidget *pc_tab =  ( *it )->create ( pcActualPoject );

        pcActualTabWidget = pc_tab;
    }


    if ( pcActualTabWidget ) {
        ui->horizontalLayout->addWidget ( pcActualTabWidget );
    }
}

void PModulesSettingsDialog::buttonClicked ( QAbstractButton *pc_button ) {
    if ( !pcActualTabWidget ) {
        return;
    }

    switch ( ui->buttonBox->buttonRole ( pc_button ) ) {
        case QDialogButtonBox::ApplyRole:
            pcActualTabWidget->save();
            break;

        case QDialogButtonBox::RejectRole:
            close();
            break;

        default:
            break;
    }
}
