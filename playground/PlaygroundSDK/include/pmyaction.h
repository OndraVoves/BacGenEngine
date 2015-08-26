#ifndef MYACTION_H
#define MYACTION_H

#include <QAction>

class PMyAction : public QAction {
        Q_OBJECT
    public:
        explicit PMyAction ( QObject *parent = 0 );


    signals:
        void activated ( QString );
        void toggled ( PMyAction *, bool );

    public slots:

    private slots:
        void onActivated();
        void onToggled ( bool );

};

#endif // MYACTION_H
