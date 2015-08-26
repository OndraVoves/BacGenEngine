#include "pgeneralsettings.h"
#include "ui_pgeneralsettings.h"

#include <QSettings>
#include <PlaygroundSDK/pactualproject.h>

#include "./include/mainwindow.h"

// TODO: nastaveni pozice tabu...
PGeneralSettings::PGeneralSettings ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent ) :
    PSettingTabWidget ( pc_main_window, pc_project, parent ),
    ui ( new Ui::PGeneralSettings ), pcMainWindow ( pc_main_window ) {
    ui->setupUi ( this );

    loadSettings();
}

PGeneralSettings::~PGeneralSettings() {
    delete ui;
}

void PGeneralSettings::loadSettings() {
    QSettings s;

    s.beginGroup ( "Dock" );
    ui->TabPositionComboBox->setCurrentIndex ( s.value ( "DockTabPosition", 0 ).toInt() );
    s.endGroup();

}

inline QTabWidget::TabPosition int2TabPositiom ( int i ) {
    switch ( i ) {
        default:
        case 0:
            return QTabWidget::North;

        case 1:
            return QTabWidget::South;

        case 2:
            return QTabWidget::West;

        case 3:
            return QTabWidget::East;
    }
}

void PGeneralSettings::save() {
    QSettings s;

    s.beginGroup ( "Dock" );
    s.setValue ( "DockTabPosition", ui->TabPositionComboBox->currentIndex() );
    s.endGroup();

    pcMainWindow->setTabPosition ( Qt::AllDockWidgetAreas, int2TabPositiom ( s.value ( "Dock/DockTabPosition", 0 ).toInt() ) );
}
