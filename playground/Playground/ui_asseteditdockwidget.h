/********************************************************************************
** Form generated from reading UI file 'asseteditdockwidget.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSETEDITDOCKWIDGET_H
#define UI_ASSETEDITDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AssetEditDockWidget {
    public:
        QWidget *dockWidgetContents;
        QVBoxLayout *verticalLayout;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDockWidget *AssetEditDockWidget ) {
            if ( AssetEditDockWidget->objectName().isEmpty() ) {
                AssetEditDockWidget->setObjectName ( QString::fromUtf8 ( "AssetEditDockWidget" ) );
            }
            AssetEditDockWidget->resize ( 332, 188 );
            AssetEditDockWidget->setStyleSheet ( QString::fromUtf8 ( "" ) );
            dockWidgetContents = new QWidget();
            dockWidgetContents->setObjectName ( QString::fromUtf8 ( "dockWidgetContents" ) );
            verticalLayout = new QVBoxLayout ( dockWidgetContents );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            buttonBox = new QDialogButtonBox ( dockWidgetContents );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setStandardButtons ( QDialogButtonBox::Apply | QDialogButtonBox::Reset );

            verticalLayout->addWidget ( buttonBox );

            AssetEditDockWidget->setWidget ( dockWidgetContents );

            retranslateUi ( AssetEditDockWidget );

            QMetaObject::connectSlotsByName ( AssetEditDockWidget );
        } // setupUi

        void retranslateUi ( QDockWidget *AssetEditDockWidget ) {
            AssetEditDockWidget->setWindowTitle ( QApplication::translate ( "AssetEditDockWidget", "DockWidget", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class AssetEditDockWidget: public Ui_AssetEditDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSETEDITDOCKWIDGET_H
