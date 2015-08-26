#ifndef PCOMPONENTTOOLBAR_H
#define PCOMPONENTTOOLBAR_H

#include <QToolBar>

namespace BackGenEngine {
    class BAbstractComponent;
}

class MainWindow;
class PActualProject;


class PComponentToolbar : public QToolBar {
        Q_OBJECT
    public:
        explicit PComponentToolbar ( BackGenEngine::BAbstractComponent *pc_component, MainWindow *pc_mainwindow, PActualProject *pc_project );
        virtual ~PComponentToolbar();

    protected:
        MainWindow *mainWindow();

        PActualProject *actualProject();

    private:
        MainWindow *pcMainWindow;
        PActualProject *pcActualProject;

    signals:

    public slots:

};

#endif // PCOMPONENTTOOLBAR_H
