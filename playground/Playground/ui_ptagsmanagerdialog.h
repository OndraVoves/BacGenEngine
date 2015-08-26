/********************************************************************************
** Form generated from reading UI file 'ptagsmanagerdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTAGSMANAGERDIALOG_H
#define UI_PTAGSMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PTagsManagerDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QVBoxLayout *verticalLayout_2;
        QListWidget *TagsListWidget;
        QHBoxLayout *horizontalLayout_2;
        QPushButton *addTagPushButton;
        QPushButton *removeTagPushButton;
        QGroupBox *groupBox;
        QVBoxLayout *verticalLayout_3;
        QHBoxLayout *horizontalLayout_3;
        QLabel *label;
        QLineEdit *NameLineEdit;
        QSpacerItem *verticalSpacer;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *PTagsManagerDialog ) {
            if ( PTagsManagerDialog->objectName().isEmpty() ) {
                PTagsManagerDialog->setObjectName ( QString::fromUtf8 ( "PTagsManagerDialog" ) );
            }
            PTagsManagerDialog->resize ( 512, 297 );
            QIcon icon;
            icon.addFile ( QString::fromUtf8 ( ":/images/mail-tagged.png" ), QSize(), QIcon::Normal, QIcon::Off );
            PTagsManagerDialog->setWindowIcon ( icon );
            verticalLayout = new QVBoxLayout ( PTagsManagerDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            verticalLayout_2 = new QVBoxLayout();
            verticalLayout_2->setObjectName ( QString::fromUtf8 ( "verticalLayout_2" ) );
            TagsListWidget = new QListWidget ( PTagsManagerDialog );
            TagsListWidget->setObjectName ( QString::fromUtf8 ( "TagsListWidget" ) );

            verticalLayout_2->addWidget ( TagsListWidget );

            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName ( QString::fromUtf8 ( "horizontalLayout_2" ) );
            addTagPushButton = new QPushButton ( PTagsManagerDialog );
            addTagPushButton->setObjectName ( QString::fromUtf8 ( "addTagPushButton" ) );
            QIcon icon1;
            icon1.addFile ( QString::fromUtf8 ( ":/images/list-add.png" ), QSize(), QIcon::Normal, QIcon::Off );
            addTagPushButton->setIcon ( icon1 );

            horizontalLayout_2->addWidget ( addTagPushButton );

            removeTagPushButton = new QPushButton ( PTagsManagerDialog );
            removeTagPushButton->setObjectName ( QString::fromUtf8 ( "removeTagPushButton" ) );
            removeTagPushButton->setEnabled ( false );
            QIcon icon2;
            icon2.addFile ( QString::fromUtf8 ( ":/images/list-remove.png" ), QSize(), QIcon::Normal, QIcon::Off );
            removeTagPushButton->setIcon ( icon2 );

            horizontalLayout_2->addWidget ( removeTagPushButton );


            verticalLayout_2->addLayout ( horizontalLayout_2 );


            horizontalLayout->addLayout ( verticalLayout_2 );

            groupBox = new QGroupBox ( PTagsManagerDialog );
            groupBox->setObjectName ( QString::fromUtf8 ( "groupBox" ) );
            verticalLayout_3 = new QVBoxLayout ( groupBox );
            verticalLayout_3->setObjectName ( QString::fromUtf8 ( "verticalLayout_3" ) );
            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName ( QString::fromUtf8 ( "horizontalLayout_3" ) );
            label = new QLabel ( groupBox );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout_3->addWidget ( label );

            NameLineEdit = new QLineEdit ( groupBox );
            NameLineEdit->setObjectName ( QString::fromUtf8 ( "NameLineEdit" ) );
            NameLineEdit->setEnabled ( false );

            horizontalLayout_3->addWidget ( NameLineEdit );


            verticalLayout_3->addLayout ( horizontalLayout_3 );

            verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

            verticalLayout_3->addItem ( verticalSpacer );


            horizontalLayout->addWidget ( groupBox );


            verticalLayout->addLayout ( horizontalLayout );

            buttonBox = new QDialogButtonBox ( PTagsManagerDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Close );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( PTagsManagerDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), PTagsManagerDialog, SLOT ( accept() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), PTagsManagerDialog, SLOT ( reject() ) );
            QObject::connect ( addTagPushButton, SIGNAL ( pressed() ), PTagsManagerDialog, SLOT ( newTag() ) );
            QObject::connect ( removeTagPushButton, SIGNAL ( pressed() ), PTagsManagerDialog, SLOT ( removeTag() ) );
            QObject::connect ( NameLineEdit, SIGNAL ( editingFinished() ), PTagsManagerDialog, SLOT ( setName() ) );

            QMetaObject::connectSlotsByName ( PTagsManagerDialog );
        } // setupUi

        void retranslateUi ( QDialog *PTagsManagerDialog ) {
            PTagsManagerDialog->setWindowTitle ( QApplication::translate ( "PTagsManagerDialog", "Tag manager", 0, QApplication::UnicodeUTF8 ) );
            addTagPushButton->setText ( QApplication::translate ( "PTagsManagerDialog", "&Add tag", 0, QApplication::UnicodeUTF8 ) );
            removeTagPushButton->setText ( QApplication::translate ( "PTagsManagerDialog", "&Remove tag", 0, QApplication::UnicodeUTF8 ) );
            groupBox->setTitle ( QApplication::translate ( "PTagsManagerDialog", "Tag properties", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "PTagsManagerDialog", "Name:", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PTagsManagerDialog: public Ui_PTagsManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTAGSMANAGERDIALOG_H
