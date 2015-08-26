#ifndef PCOMPONENTSWIDGET_H
#define PCOMPONENTSWIDGET_H

#include <QWidget>

class PActualProject;
class MainWindow;

class PComponentToolbar;

namespace BackGenEngine {
    class BObject;
    class BAbstractComponent;
}

namespace Ui {
    class PComponentsWidget;
}

class QMenu;

class PComponentProperties;
class PScrollComponentsWidget;

class PComponentsWidget : public QWidget {
        Q_OBJECT

    public:
        explicit PComponentsWidget ( MainWindow *main_window, PActualProject *actual_project );
        virtual ~PComponentsWidget();

    private:
        Ui::PComponentsWidget *ui;
        MainWindow *pcMainWindow;
        PActualProject *pcActualProject;

        QMenu *pcAddComponentMenu;
        QList<PComponentToolbar *> ComponentToolBarList;

        PComponentProperties *pcComponentWidget;

        PScrollComponentsWidget *pcComponentScroll;

        void generateAddComponentMenu();
        void createToolbars();

    public slots:
        void objectActivated();
        void addComponent ( QString name );
};

#endif // PCOMPONENTSWIDGET_H
