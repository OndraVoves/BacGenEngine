/********************************************************************************
** Form generated from reading UI file 'pmodulessettings.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PMODULESSETTINGS_H
#define UI_PMODULESSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PModulesSettings {
    public:
        QWidget *tab;
        QVBoxLayout *verticalLayout;
        QTreeWidget *treeWidget;

        void setupUi ( QTabWidget *PModulesSettings ) {
            if ( PModulesSettings->objectName().isEmpty() ) {
                PModulesSettings->setObjectName ( QString::fromUtf8 ( "PModulesSettings" ) );
            }
            PModulesSettings->resize ( 459, 340 );
            tab = new QWidget();
            tab->setObjectName ( QString::fromUtf8 ( "tab" ) );
            verticalLayout = new QVBoxLayout ( tab );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            treeWidget = new QTreeWidget ( tab );
            treeWidget->setObjectName ( QString::fromUtf8 ( "treeWidget" ) );
            treeWidget->setColumnCount ( 2 );

            verticalLayout->addWidget ( treeWidget );

            PModulesSettings->addTab ( tab, QString() );

            retranslateUi ( PModulesSettings );

            PModulesSettings->setCurrentIndex ( 0 );


            QMetaObject::connectSlotsByName ( PModulesSettings );
        } // setupUi

        void retranslateUi ( QTabWidget *PModulesSettings ) {
            PModulesSettings->setWindowTitle ( QApplication::translate ( "PModulesSettings", "TabWidget", 0, QApplication::UnicodeUTF8 ) );
            QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
            ___qtreewidgetitem->setText ( 1, QApplication::translate ( "PModulesSettings", "Path", 0, QApplication::UnicodeUTF8 ) );
            ___qtreewidgetitem->setText ( 0, QApplication::translate ( "PModulesSettings", "Name", 0, QApplication::UnicodeUTF8 ) );
            PModulesSettings->setTabText ( PModulesSettings->indexOf ( tab ), QApplication::translate ( "PModulesSettings", "General", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PModulesSettings: public Ui_PModulesSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PMODULESSETTINGS_H
