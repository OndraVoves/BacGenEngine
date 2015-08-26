/********************************************************************************
** Form generated from reading UI file 'sceneeditdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEEDITDIALOG_H
#define UI_SCENEEDITDIALOG_H

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

class Ui_SceneEditDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QLineEdit *SceneNameLineEdit;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *SceneEditDialog ) {
            if ( SceneEditDialog->objectName().isEmpty() ) {
                SceneEditDialog->setObjectName ( QString::fromUtf8 ( "SceneEditDialog" ) );
            }
            SceneEditDialog->resize ( 400, 65 );
            verticalLayout = new QVBoxLayout ( SceneEditDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( SceneEditDialog );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            SceneNameLineEdit = new QLineEdit ( SceneEditDialog );
            SceneNameLineEdit->setObjectName ( QString::fromUtf8 ( "SceneNameLineEdit" ) );

            horizontalLayout->addWidget ( SceneNameLineEdit );


            verticalLayout->addLayout ( horizontalLayout );

            buttonBox = new QDialogButtonBox ( SceneEditDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Cancel | QDialogButtonBox::Ok );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( SceneEditDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), SceneEditDialog, SLOT ( accept() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), SceneEditDialog, SLOT ( reject() ) );
            QObject::connect ( SceneNameLineEdit, SIGNAL ( editingFinished() ), SceneEditDialog, SLOT ( parseName() ) );

            QMetaObject::connectSlotsByName ( SceneEditDialog );
        } // setupUi

        void retranslateUi ( QDialog *SceneEditDialog ) {
            SceneEditDialog->setWindowTitle ( QApplication::translate ( "SceneEditDialog", "Scene edit dialog", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "SceneEditDialog", "Name:", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class SceneEditDialog: public Ui_SceneEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEEDITDIALOG_H
