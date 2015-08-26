/********************************************************************************
** Form generated from reading UI file 'newprojectdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOG_H
#define UI_NEWPROJECTDIALOG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QLineEdit *ProjectNameLineEdit;
        QHBoxLayout *horizontalLayout_2;
        QLabel *label_2;
        QLineEdit *ProjectDirLineEdit;
        QPushButton *SelectDirButton;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *NewProjectDialog ) {
            if ( NewProjectDialog->objectName().isEmpty() ) {
                NewProjectDialog->setObjectName ( QString::fromUtf8 ( "NewProjectDialog" ) );
            }
            NewProjectDialog->resize ( 275, 122 );
            verticalLayout = new QVBoxLayout ( NewProjectDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( NewProjectDialog );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            ProjectNameLineEdit = new QLineEdit ( NewProjectDialog );
            ProjectNameLineEdit->setObjectName ( QString::fromUtf8 ( "ProjectNameLineEdit" ) );

            horizontalLayout->addWidget ( ProjectNameLineEdit );


            verticalLayout->addLayout ( horizontalLayout );

            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName ( QString::fromUtf8 ( "horizontalLayout_2" ) );
            label_2 = new QLabel ( NewProjectDialog );
            label_2->setObjectName ( QString::fromUtf8 ( "label_2" ) );

            horizontalLayout_2->addWidget ( label_2 );

            ProjectDirLineEdit = new QLineEdit ( NewProjectDialog );
            ProjectDirLineEdit->setObjectName ( QString::fromUtf8 ( "ProjectDirLineEdit" ) );

            horizontalLayout_2->addWidget ( ProjectDirLineEdit );

            SelectDirButton = new QPushButton ( NewProjectDialog );
            SelectDirButton->setObjectName ( QString::fromUtf8 ( "SelectDirButton" ) );
            QIcon icon;
            icon.addFile ( QString::fromUtf8 ( ":/images/folder.png" ), QSize(), QIcon::Normal, QIcon::Off );
            SelectDirButton->setIcon ( icon );

            horizontalLayout_2->addWidget ( SelectDirButton );


            verticalLayout->addLayout ( horizontalLayout_2 );

            buttonBox = new QDialogButtonBox ( NewProjectDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Cancel | QDialogButtonBox::Ok );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( NewProjectDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), NewProjectDialog, SLOT ( createProject() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), NewProjectDialog, SLOT ( reject() ) );
            QObject::connect ( SelectDirButton, SIGNAL ( clicked() ), NewProjectDialog, SLOT ( openDir() ) );

            QMetaObject::connectSlotsByName ( NewProjectDialog );
        } // setupUi

        void retranslateUi ( QDialog *NewProjectDialog ) {
            NewProjectDialog->setWindowTitle ( QApplication::translate ( "NewProjectDialog", "Create new project", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "NewProjectDialog", "Project name:", 0, QApplication::UnicodeUTF8 ) );
            label_2->setText ( QApplication::translate ( "NewProjectDialog", "Project dir:", 0, QApplication::UnicodeUTF8 ) );
            SelectDirButton->setText ( QString() );
        } // retranslateUi

};

namespace Ui {
    class NewProjectDialog: public Ui_NewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOG_H
