#ifndef PCOMPONENTPROPERTIES_H
#define PCOMPONENTPROPERTIES_H

#include <QWidget>

namespace BackGenEngine {
    class BAbstractComponent;
}

class PActualProject;
class MainWindow;

class QTreeWidget;
class QTreeWidgetItem;

class PComponentProperties : public QWidget {
        Q_OBJECT
    public:
        explicit PComponentProperties ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project );

        virtual void updateData() = 0;
    signals:

    public slots:

    protected:
        PActualProject *project();

    private:
        PActualProject *pcActualProject;
};

#endif // PCOMPONENTPROPERTIES_H
