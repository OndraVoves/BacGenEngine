#ifndef PSETTINGTABWIDGET_H
#define PSETTINGTABWIDGET_H

#include <QTabWidget>

class PActualProject;
class MainWindow;

class PSettingTabWidget : public QTabWidget {
        Q_OBJECT
    public:
        explicit PSettingTabWidget ( MainWindow *pc_main_window, PActualProject *pc_project, QWidget *parent = 0 );

        virtual ~PSettingTabWidget();

        bool isModified() const;
        void setModified ( bool modified );

        virtual void save() = 0;
    private:
        bool Modified;

    signals:

    public slots:

};

#endif // PSETTINGTABWIDGET_H
