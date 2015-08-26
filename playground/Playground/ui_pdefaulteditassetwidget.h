/********************************************************************************
** Form generated from reading UI file 'pdefaulteditassetwidget.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDEFAULTEDITASSETWIDGET_H
#define UI_PDEFAULTEDITASSETWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PDefaultEditAssetWidget {
    public:
        QVBoxLayout *verticalLayout;
        QGroupBox *groupBox;
        QVBoxLayout *verticalLayout_2;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QLineEdit *NameLineEdit;
        QHBoxLayout *horizontalLayout_2;
        QLabel *label_2;
        QLineEdit *PathLineEdit;
        QPushButton *OpenAssetButton;

        void setupUi ( QWidget *PDefaultEditAssetWidget ) {
            if ( PDefaultEditAssetWidget->objectName().isEmpty() ) {
                PDefaultEditAssetWidget->setObjectName ( QString::fromUtf8 ( "PDefaultEditAssetWidget" ) );
            }
            PDefaultEditAssetWidget->resize ( 471, 104 );
            verticalLayout = new QVBoxLayout ( PDefaultEditAssetWidget );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            groupBox = new QGroupBox ( PDefaultEditAssetWidget );
            groupBox->setObjectName ( QString::fromUtf8 ( "groupBox" ) );
            verticalLayout_2 = new QVBoxLayout ( groupBox );
            verticalLayout_2->setObjectName ( QString::fromUtf8 ( "verticalLayout_2" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( groupBox );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            NameLineEdit = new QLineEdit ( groupBox );
            NameLineEdit->setObjectName ( QString::fromUtf8 ( "NameLineEdit" ) );

            horizontalLayout->addWidget ( NameLineEdit );


            verticalLayout_2->addLayout ( horizontalLayout );

            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName ( QString::fromUtf8 ( "horizontalLayout_2" ) );
            label_2 = new QLabel ( groupBox );
            label_2->setObjectName ( QString::fromUtf8 ( "label_2" ) );

            horizontalLayout_2->addWidget ( label_2 );

            PathLineEdit = new QLineEdit ( groupBox );
            PathLineEdit->setObjectName ( QString::fromUtf8 ( "PathLineEdit" ) );

            horizontalLayout_2->addWidget ( PathLineEdit );

            OpenAssetButton = new QPushButton ( groupBox );
            OpenAssetButton->setObjectName ( QString::fromUtf8 ( "OpenAssetButton" ) );

            horizontalLayout_2->addWidget ( OpenAssetButton );


            verticalLayout_2->addLayout ( horizontalLayout_2 );


            verticalLayout->addWidget ( groupBox );


            retranslateUi ( PDefaultEditAssetWidget );

            QMetaObject::connectSlotsByName ( PDefaultEditAssetWidget );
        } // setupUi

        void retranslateUi ( QWidget *PDefaultEditAssetWidget ) {
            PDefaultEditAssetWidget->setWindowTitle ( QApplication::translate ( "PDefaultEditAssetWidget", "Form", 0, QApplication::UnicodeUTF8 ) );
            groupBox->setTitle ( QApplication::translate ( "PDefaultEditAssetWidget", "General properties", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "PDefaultEditAssetWidget", "Name:", 0, QApplication::UnicodeUTF8 ) );
            label_2->setText ( QApplication::translate ( "PDefaultEditAssetWidget", "Path:", 0, QApplication::UnicodeUTF8 ) );
            OpenAssetButton->setText ( QApplication::translate ( "PDefaultEditAssetWidget", "...", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PDefaultEditAssetWidget: public Ui_PDefaultEditAssetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDEFAULTEDITASSETWIDGET_H
