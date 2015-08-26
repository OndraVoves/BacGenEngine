#include "../../include/assets/passetsettings.h"
#include "ui_passetsettings.h"

#include <BackGenEngine/bproject.h>
#include <BackGenEngine/bdynamicmodulesystem.h>

#include <PlaygroundSDK/pactualproject.h>

#include <QSettings>

PAssetSettings::PAssetSettings ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent ) :
    PSettingTabWidget ( pc_main_window, pc_project, parent ),
    ui ( new Ui::PAssetSettings ), pcActualProject ( pc_project ) {
    ui->setupUi ( this );

    fillAssetTypeComboBox();

    loadSettings();

    if ( ui->AssetTypeComboBox->count() ) {
        externalEditorItemChanged ( ui->AssetTypeComboBox->currentIndex() );
    }

    connect ( ui->AssetTypeComboBox, SIGNAL ( currentIndexChanged ( int ) ), this, SLOT ( externalEditorItemChanged ( int ) ) );
    connect ( ui->ExternalEditorPathLineEdit, SIGNAL ( editingFinished() ), this, SLOT ( parseExternalEditorPath() ) );
}

PAssetSettings::~PAssetSettings() {
    delete ui;
}

void PAssetSettings::save() {
    QSettings s;

    s.beginGroup ( "AssetTree" );
    s.setValue ( "DoubleClickAction", ui->comboBox->currentIndex() );
    s.setValue ( "EditDockWidgetPosition", ui->comboBox_2->currentIndex() );
    s.endGroup();

    s.beginGroup ( "AssetsEditor" );

    for ( int i = 0 ; i < ui->AssetTypeComboBox->count(); i++ ) {
        s.setValue ( ui->AssetTypeComboBox->itemText ( i ), ui->AssetTypeComboBox->itemData ( i ) );
    }

    s.endGroup();
}

void PAssetSettings::loadSettings() {
    QSettings s;

    s.beginGroup ( "AssetTree" );
    ui->comboBox->setCurrentIndex ( s.value ( "DoubleClickAction", 0 ).toInt() );
    ui->comboBox_2->setCurrentIndex ( s.value ( "EditDockWidgetPosition", 0 ).toInt() );
    s.endGroup();
}

void PAssetSettings::fillAssetTypeComboBox() {
    ui->AssetTypeComboBox->clear();

    BackGenEngine::BDynamicModuleSystem *pc_module_system = ( BackGenEngine::BDynamicModuleSystem * ) pcActualProject->project()->getModuleSystem();
    BackGenEngine::BDynamicModuleSystem::asset_module_hash_t::ConstIterator it = pc_module_system->getAssetModuleHash().constBegin();

    QSettings s;
    QString asset_type;
    while ( it != pc_module_system->getAssetModuleHash().constEnd() ) {
        asset_type = it.key().constData();
        ui->AssetTypeComboBox->addItem ( asset_type, s.value ( QString ( "AssetsEditor/%1" ).arg ( asset_type ) ) );
        ++it;
    }
}

void PAssetSettings::externalEditorItemChanged ( int index ) {
    QString path = ui->AssetTypeComboBox->itemData ( index ).toString();
    ui->ExternalEditorPathLineEdit->setText ( path );
}

void PAssetSettings::parseExternalEditorPath() {
    ui->AssetTypeComboBox->setItemData ( ui->AssetTypeComboBox->currentIndex(),
                                         ui->ExternalEditorPathLineEdit->text() );
}

