#include "../include/pdockwidget.h"

PDockWidget::PDockWidget ( PActualProject *pc_project, QWidget *parent ) :
    QDockWidget ( parent ), pcActualProject ( pc_project ) {
}

PActualProject *PDockWidget::project() {
    return pcActualProject;
}
