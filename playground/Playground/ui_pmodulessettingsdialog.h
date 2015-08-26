/********************************************************************************
** Form generated from reading UI file 'pmodulessettingsdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PMODULESSETTINGSDIALOG_H
#define UI_PMODULESSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PModulesSettingsDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QListWidget *ItemListWidget;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *PModulesSettingsDialog ) {
            if ( PModulesSettingsDialog->objectName().isEmpty() ) {
                PModulesSettingsDialog->setObjectName ( QString::fromUtf8 ( "PModulesSettingsDialog" ) );
            }
            PModulesSettingsDialog->resize ( 285, 245 );
            verticalLayout = new QVBoxLayout ( PModulesSettingsDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            horizontalLayout->setSizeConstraint ( QLayout::SetMinimumSize );
            ItemListWidget = new QListWidget ( PModulesSettingsDialog );
            QIcon icon;
            icon.addFile ( QString::fromUtf8 ( ":/images/preferences-system.png" ), QSize(), QIcon::Normal, QIcon::Off );
            QListWidgetItem *__qlistwidgetitem = new QListWidgetItem ( ItemListWidget );
            __qlistwidgetitem->setIcon ( icon );
            QIcon icon1;
            icon1.addFile ( QString::fromUtf8 ( ":/images/modules.png" ), QSize(), QIcon::Normal, QIcon::Off );
            QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem ( ItemListWidget );
            __qlistwidgetitem1->setIcon ( icon1 );
            QIcon icon2;
            icon2.addFile ( QString::fromUtf8 ( ":/images/document-open-folder.png" ), QSize(), QIcon::Normal, QIcon::Off );
            QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem ( ItemListWidget );
            __qlistwidgetitem2->setIcon ( icon2 );
            ItemListWidget->setObjectName ( QString::fromUtf8 ( "ItemListWidget" ) );
            QSizePolicy sizePolicy ( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
            sizePolicy.setHorizontalStretch ( 0 );
            sizePolicy.setVerticalStretch ( 0 );
            sizePolicy.setHeightForWidth ( ItemListWidget->sizePolicy().hasHeightForWidth() );
            ItemListWidget->setSizePolicy ( sizePolicy );
            ItemListWidget->setIconSize ( QSize ( 32, 32 ) );

            horizontalLayout->addWidget ( ItemListWidget );


            verticalLayout->addLayout ( horizontalLayout );

            buttonBox = new QDialogButtonBox ( PModulesSettingsDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Ok );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( PModulesSettingsDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), PModulesSettingsDialog, SLOT ( accept() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), PModulesSettingsDialog, SLOT ( reject() ) );

            QMetaObject::connectSlotsByName ( PModulesSettingsDialog );
        } // setupUi

        void retranslateUi ( QDialog *PModulesSettingsDialog ) {
            PModulesSettingsDialog->setWindowTitle ( QApplication::translate ( "PModulesSettingsDialog", "Settings", 0, QApplication::UnicodeUTF8 ) );

            const bool __sortingEnabled = ItemListWidget->isSortingEnabled();
            ItemListWidget->setSortingEnabled ( false );
            QListWidgetItem *___qlistwidgetitem = ItemListWidget->item ( 0 );
            ___qlistwidgetitem->setText ( QApplication::translate ( "PModulesSettingsDialog", "General", 0, QApplication::UnicodeUTF8 ) );
            QListWidgetItem *___qlistwidgetitem1 = ItemListWidget->item ( 1 );
            ___qlistwidgetitem1->setText ( QApplication::translate ( "PModulesSettingsDialog", "Modules", 0, QApplication::UnicodeUTF8 ) );
            QListWidgetItem *___qlistwidgetitem2 = ItemListWidget->item ( 2 );
            ___qlistwidgetitem2->setText ( QApplication::translate ( "PModulesSettingsDialog", "Assets", 0, QApplication::UnicodeUTF8 ) );
            ItemListWidget->setSortingEnabled ( __sortingEnabled );

        } // retranslateUi

};

namespace Ui {
    class PModulesSettingsDialog: public Ui_PModulesSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PMODULESSETTINGSDIALOG_H
