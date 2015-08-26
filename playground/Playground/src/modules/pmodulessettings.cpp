#include "../../include/modules/pmodulessettings.h"
#include "ui_pmodulessettings.h"

#include <PlaygroundSDK/pmodulessystem.h>
#include <PlaygroundSDK/pactualproject.h>

#include <PlaygroundSDK/pcomponentpropertiesmodule.h>
#include <PlaygroundSDK/passeteditwidgetmodule.h>
#include <PlaygroundSDK/psettingmodule.h>
#include <PlaygroundSDK/passetitemhelpermodule.h>
#include <PlaygroundSDK/pcomponenttoolbarmodule.h>

#include <QLibrary>

#include <QAbstractButton>

PModulesSettings::PModulesSettings ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent ) :
    PSettingTabWidget ( pc_main_window, pc_project, parent ),
    ui ( new Ui::PModulesSettings ), pcActualProject ( pc_project ) {
    ui->setupUi ( this );

    fillModulesTree();
}

PModulesSettings::~PModulesSettings() {
    delete ui;
}

void PModulesSettings::save() {
}

void PModulesSettings::fillModulesTree() {
    QTreeWidgetItem *pc_new_item = 0;

    // COmponent properties
    PModulesSystem::component_properties_hash_t::ConstIterator it = pcActualProject->moduleSystem()->componentPropertiesHash().constBegin();
    while ( it != pcActualProject->moduleSystem()->componentPropertiesHash().constEnd() ) {
        pc_new_item = new QTreeWidgetItem ( ui->treeWidget );

        pc_new_item->setText ( 0, it.key() );
        pc_new_item->setText ( 1, ( *it )->lib()->fileName() );

        ++it;
    }

    // Asset edit widget
    PModulesSystem::asset_edit_widget_hash_t::ConstIterator it2 = pcActualProject->moduleSystem()->assetEditWidgetHash().constBegin();
    while ( it2 != pcActualProject->moduleSystem()->assetEditWidgetHash().constEnd()  ) {
        pc_new_item = new QTreeWidgetItem ( ui->treeWidget );

        pc_new_item->setText ( 0, it2.key() );
        pc_new_item->setText ( 1, ( *it2 )->lib()->fileName() );

        ++it2;
    }

    // Asset item helper
    PModulesSystem::asset_item_helper_hash_t::ConstIterator it3 = pcActualProject->moduleSystem()->assetItemHelperHash().constBegin();
    while ( it3 != pcActualProject->moduleSystem()->assetItemHelperHash().constEnd()  ) {
        pc_new_item = new QTreeWidgetItem ( ui->treeWidget  );

        pc_new_item->setText ( 0, it3.key() );
        pc_new_item->setText ( 1, ( *it3 )->lib()->fileName() );

        ++it3;
    }

    // Setting tab
    PModulesSystem::setting_tab_hash_t::ConstIterator it4 = pcActualProject->moduleSystem()->settingTabHash().constBegin();
    while ( it4 != pcActualProject->moduleSystem()->settingTabHash().constEnd()  ) {
        pc_new_item = new QTreeWidgetItem ( ui->treeWidget );

        pc_new_item->setText ( 0, it4.key() );
        pc_new_item->setText ( 1, ( *it4 )->lib()->fileName() );

        ++it4;
    }

    // Setting tab
    PModulesSystem::component_toolbar_hash_t::ConstIterator it5 = pcActualProject->moduleSystem()->componentToolBarHash().constBegin();
    while ( it5 != pcActualProject->moduleSystem()->componentToolBarHash().constEnd()  ) {
        pc_new_item = new QTreeWidgetItem ( ui->treeWidget );

        pc_new_item->setText ( 0, it5.key() );
        pc_new_item->setText ( 1, ( *it5 )->lib()->fileName() );

        ++it5;
    }

}
