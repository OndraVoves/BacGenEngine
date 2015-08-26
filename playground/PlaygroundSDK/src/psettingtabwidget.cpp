#include "../include/psettingtabwidget.h"

PSettingTabWidget::PSettingTabWidget ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent ) :
    QTabWidget ( parent ) {
}

PSettingTabWidget::~PSettingTabWidget() {

}

bool PSettingTabWidget::isModified() const {
    return Modified;
}

void PSettingTabWidget::setModified ( bool modified ) {
    Modified = modified;
}
