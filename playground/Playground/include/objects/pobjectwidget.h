#ifndef POBJECTWIDGET_H
#define POBJECTWIDGET_H

#include <QWidget>

class PActualProject;
class MainWindow;

class QLineEdit;
class QComboBox;
class QMenu;
class PMyAction;

namespace BackGenEngine {
    class BObject;
}

class PComponentsWidget;

class PObjectWidget : public QWidget {
        Q_OBJECT
    public:
        explicit PObjectWidget (  MainWindow *main_window, PActualProject *actual_project, QWidget *parent = 0 );
        virtual ~PObjectWidget();

    private:
        MainWindow *pcMainWindow;
        PActualProject *pcActualProject;

        BackGenEngine::BObject *pcObject;

        QLineEdit *pcNameLineEdit;
        QComboBox *pcLayerComboBox;
        QMenu     *pcTagsMenu;

        PComponentsWidget *pcComponentsWidget;

    private:
        void setLayer();
        void setTag();

    signals:

    public slots:
        void objectActivated();
        void nameChanged();

        void layerChanged ( int index );

        void generateLayerComboBoxItem();
        void generateTagMenu();

    private slots:
        void openLayersManager();
        void openTagsManager();
        void layerManagerChanged();
        void tagManagerChanged();

        void tagToggled ( PMyAction *pc_action, bool toggled );

};

#endif // POBJECTWIDGET_H
