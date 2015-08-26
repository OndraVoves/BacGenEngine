#include <QtGui/QApplication>
#include "../include/mainwindow.h"

int main ( int argc, char *argv[] ) {
    QApplication a ( argc, argv );

    a.setOrganizationName ( "BackGen" );
    a.setApplicationName ( "Playground" );

    MainWindow w;
    w.show();

    return a.exec();
}
