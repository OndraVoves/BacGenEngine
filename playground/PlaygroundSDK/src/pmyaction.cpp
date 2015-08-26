#include "../include/pmyaction.h"

PMyAction::PMyAction ( QObject *parent ) :
    QAction ( parent ) {
    connect ( this, SIGNAL ( activated() ), this, SLOT ( onActivated() ) );
    connect ( this, SIGNAL ( toggled ( bool ) ), this, SLOT ( onToggled ( bool ) ) );
}

void PMyAction::onActivated() {
    emit activated ( text() );
}

void PMyAction::onToggled ( bool b ) {
    emit toggled ( this, b );
}
