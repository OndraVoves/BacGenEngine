/********************************************************************************
** Form generated from reading UI file 'pprojectsettingdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PPROJECTSETTINGDIALOG_H
#define UI_PPROJECTSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PProjectSettingDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QLineEdit *NameLineEdit;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *PProjectSettingDialog ) {
            if ( PProjectSettingDialog->objectName().isEmpty() ) {
                PProjectSettingDialog->setObjectName ( QString::fromUtf8 ( "PProjectSettingDialog" ) );
            }
            PProjectSettingDialog->resize ( 408, 65 );
            verticalLayout = new QVBoxLayout ( PProjectSettingDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( PProjectSettingDialog );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            NameLineEdit = new QLineEdit ( PProjectSettingDialog );
            NameLineEdit->setObjectName ( QString::fromUtf8 ( "NameLineEdit" ) );

            horizontalLayout->addWidget ( NameLineEdit );


            verticalLayout->addLayout ( horizontalLayout );

            buttonBox = new QDialogButtonBox ( PProjectSettingDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Cancel | QDialogButtonBox::Ok );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( PProjectSettingDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), PProjectSettingDialog, SLOT ( accept() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), PProjectSettingDialog, SLOT ( reject() ) );

            QMetaObject::connectSlotsByName ( PProjectSettingDialog );
        } // setupUi

        void retranslateUi ( QDialog *PProjectSettingDialog ) {
            PProjectSettingDialog->setWindowTitle ( QApplication::translate ( "PProjectSettingDialog", "Project setting", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "PProjectSettingDialog", "Name:", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PProjectSettingDialog: public Ui_PProjectSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PPROJECTSETTINGDIALOG_H
