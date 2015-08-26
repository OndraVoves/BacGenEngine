#ifndef PDOCKWIDGET_H
#define PDOCKWIDGET_H

#include <QDockWidget>

class PActualProject;

class PDockWidget : public QDockWidget {
        Q_OBJECT
    public:
        explicit PDockWidget ( PActualProject *pc_project, QWidget *parent = 0 );

    protected:
        PActualProject *project();

    private:
        PActualProject *pcActualProject;

    signals:

    public slots:

};

#endif // PDOCKWIDGET_H
