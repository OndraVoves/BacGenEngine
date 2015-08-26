#ifndef PSCROLLCOMPONENTSWIDGET_H
#define PSCROLLCOMPONENTSWIDGET_H

#include <QScrollArea>

#include <QHash>


namespace BackGenEngine {
    class BObject;
}

class QHBoxLayout;
class QVBoxLayout;

class PActualProject;
class PComponentProperties;

class PScrollComponentsWidget : public QScrollArea {
        Q_OBJECT
    public:
        explicit PScrollComponentsWidget ( PActualProject *actual_project );

        void generateComponents ( BackGenEngine::BObject *pc_object );

        void updateComponent ( QString name );

        void addComponent (  QString name  );

    private:
        PActualProject *pcActualProject;
        BackGenEngine::BObject *pcObject;

        QVBoxLayout *pcMainVLayout;

        QHash< QString, PComponentProperties *> ComponentPropertiesHash;
        QHash< QString, QHBoxLayout *> ComponentHBoxHash;

        void clear();
    signals:

    public slots:

    private slots:
        void removeAction ( QString component );
        void clickAction ( QString component );
};

#endif // PSCROLLCOMPONENTSWIDGET_H
