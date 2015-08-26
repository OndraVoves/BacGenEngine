#include "../include/pcomponenttoolbar.h"

PComponentToolbar::PComponentToolbar ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project  ) :
    QToolBar ( 0 ), pcMainWindow ( pc_mainwindow ), pcActualProject ( pc_project ) {
}

PComponentToolbar::~PComponentToolbar() {

}

MainWindow *PComponentToolbar::mainWindow() {
    return pcMainWindow;
}

PActualProject *PComponentToolbar::actualProject() {
    return pcActualProject;
}
