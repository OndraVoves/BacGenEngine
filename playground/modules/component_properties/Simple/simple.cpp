#include "simple.h"

#include <PlaygroundSDK/modulesheader.h>

#include <QTreeWidget>
#include <QTreeWidgetItem>

Simple::Simple (  PActualProject *pc_project  )
    : PSettingTabWidget ( pc_project )  {
}

void Simple::save() {

}

extern "C" {
    PBASE_MODULE_HEADER ( SETTING_TAB, "Simple", "0.0.1", "Ondra Voves" );

    PSettingTabWidget *createSettingTab ( PActualProject *pc_project  ) {
        return new Simple ( pc_project );
    }
}
