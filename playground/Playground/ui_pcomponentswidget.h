/********************************************************************************
** Form generated from reading UI file 'pcomponentswidget.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCOMPONENTSWIDGET_H
#define UI_PCOMPONENTSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PComponentsWidget {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;

        void setupUi ( QWidget *PComponentsWidget ) {
            if ( PComponentsWidget->objectName().isEmpty() ) {
                PComponentsWidget->setObjectName ( QString::fromUtf8 ( "PComponentsWidget" ) );
            }
            PComponentsWidget->resize ( 386, 36 );
            verticalLayout = new QVBoxLayout ( PComponentsWidget );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setSpacing ( 0 );
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            horizontalLayout->setSizeConstraint ( QLayout::SetDefaultConstraint );
            horizontalLayout->setContentsMargins ( 0, -1, -1, -1 );

            verticalLayout->addLayout ( horizontalLayout );


            retranslateUi ( PComponentsWidget );

            QMetaObject::connectSlotsByName ( PComponentsWidget );
        } // setupUi

        void retranslateUi ( QWidget *PComponentsWidget ) {
            PComponentsWidget->setWindowTitle ( QApplication::translate ( "PComponentsWidget", "Form", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PComponentsWidget: public Ui_PComponentsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCOMPONENTSWIDGET_H
