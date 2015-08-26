/********************************************************************************
** Form generated from reading UI file 'layersmanagerdialog.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYERSMANAGERDIALOG_H
#define UI_LAYERSMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_LayersManagerDialog {
    public:
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QVBoxLayout *verticalLayout_2;
        QListWidget *LayersListWidget;
        QHBoxLayout *horizontalLayout_2;
        QPushButton *AddLayerPushButton;
        QPushButton *removePushButton;
        QGroupBox *groupBox;
        QVBoxLayout *verticalLayout_4;
        QHBoxLayout *horizontalLayout_3;
        QLabel *label;
        QLineEdit *NameLineEdit;
        QHBoxLayout *horizontalLayout_4;
        QLabel *label_2;
        QComboBox *TypeComboBox;
        QSpacerItem *verticalSpacer;
        QDialogButtonBox *buttonBox;

        void setupUi ( QDialog *LayersManagerDialog ) {
            if ( LayersManagerDialog->objectName().isEmpty() ) {
                LayersManagerDialog->setObjectName ( QString::fromUtf8 ( "LayersManagerDialog" ) );
            }
            LayersManagerDialog->resize ( 517, 355 );
            QIcon icon;
            icon.addFile ( QString::fromUtf8 ( ":/images/document-multiple.png" ), QSize(), QIcon::Normal, QIcon::Off );
            LayersManagerDialog->setWindowIcon ( icon );
            verticalLayout = new QVBoxLayout ( LayersManagerDialog );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            verticalLayout_2 = new QVBoxLayout();
            verticalLayout_2->setObjectName ( QString::fromUtf8 ( "verticalLayout_2" ) );
            LayersListWidget = new QListWidget ( LayersManagerDialog );
            LayersListWidget->setObjectName ( QString::fromUtf8 ( "LayersListWidget" ) );

            verticalLayout_2->addWidget ( LayersListWidget );

            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName ( QString::fromUtf8 ( "horizontalLayout_2" ) );
            AddLayerPushButton = new QPushButton ( LayersManagerDialog );
            AddLayerPushButton->setObjectName ( QString::fromUtf8 ( "AddLayerPushButton" ) );
            QIcon icon1;
            icon1.addFile ( QString::fromUtf8 ( ":/images/list-add.png" ), QSize(), QIcon::Normal, QIcon::Off );
            AddLayerPushButton->setIcon ( icon1 );

            horizontalLayout_2->addWidget ( AddLayerPushButton );

            removePushButton = new QPushButton ( LayersManagerDialog );
            removePushButton->setObjectName ( QString::fromUtf8 ( "removePushButton" ) );
            removePushButton->setEnabled ( false );
            QIcon icon2;
            icon2.addFile ( QString::fromUtf8 ( ":/images/list-remove.png" ), QSize(), QIcon::Normal, QIcon::Off );
            removePushButton->setIcon ( icon2 );
            removePushButton->setCheckable ( false );

            horizontalLayout_2->addWidget ( removePushButton );


            verticalLayout_2->addLayout ( horizontalLayout_2 );


            horizontalLayout->addLayout ( verticalLayout_2 );

            groupBox = new QGroupBox ( LayersManagerDialog );
            groupBox->setObjectName ( QString::fromUtf8 ( "groupBox" ) );
            groupBox->setEnabled ( true );
            groupBox->setFlat ( false );
            groupBox->setCheckable ( false );
            verticalLayout_4 = new QVBoxLayout ( groupBox );
            verticalLayout_4->setObjectName ( QString::fromUtf8 ( "verticalLayout_4" ) );
            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName ( QString::fromUtf8 ( "horizontalLayout_3" ) );
            label = new QLabel ( groupBox );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout_3->addWidget ( label );

            NameLineEdit = new QLineEdit ( groupBox );
            NameLineEdit->setObjectName ( QString::fromUtf8 ( "NameLineEdit" ) );
            NameLineEdit->setEnabled ( false );

            horizontalLayout_3->addWidget ( NameLineEdit );


            verticalLayout_4->addLayout ( horizontalLayout_3 );

            horizontalLayout_4 = new QHBoxLayout();
            horizontalLayout_4->setObjectName ( QString::fromUtf8 ( "horizontalLayout_4" ) );
            label_2 = new QLabel ( groupBox );
            label_2->setObjectName ( QString::fromUtf8 ( "label_2" ) );

            horizontalLayout_4->addWidget ( label_2 );

            TypeComboBox = new QComboBox ( groupBox );
            TypeComboBox->setObjectName ( QString::fromUtf8 ( "TypeComboBox" ) );
            TypeComboBox->setEnabled ( false );

            horizontalLayout_4->addWidget ( TypeComboBox );


            verticalLayout_4->addLayout ( horizontalLayout_4 );

            verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

            verticalLayout_4->addItem ( verticalSpacer );


            horizontalLayout->addWidget ( groupBox );


            verticalLayout->addLayout ( horizontalLayout );

            buttonBox = new QDialogButtonBox ( LayersManagerDialog );
            buttonBox->setObjectName ( QString::fromUtf8 ( "buttonBox" ) );
            buttonBox->setOrientation ( Qt::Horizontal );
            buttonBox->setStandardButtons ( QDialogButtonBox::Close );

            verticalLayout->addWidget ( buttonBox );


            retranslateUi ( LayersManagerDialog );
            QObject::connect ( buttonBox, SIGNAL ( accepted() ), LayersManagerDialog, SLOT ( accept() ) );
            QObject::connect ( buttonBox, SIGNAL ( rejected() ), LayersManagerDialog, SLOT ( reject() ) );
            QObject::connect ( AddLayerPushButton, SIGNAL ( pressed() ), LayersManagerDialog, SLOT ( addNewLayer() ) );
            QObject::connect ( NameLineEdit, SIGNAL ( editingFinished() ), LayersManagerDialog, SLOT ( setName() ) );
            QObject::connect ( TypeComboBox, SIGNAL ( currentIndexChanged ( QString ) ), LayersManagerDialog, SLOT ( setType ( QString ) ) );
            QObject::connect ( removePushButton, SIGNAL ( pressed() ), LayersManagerDialog, SLOT ( removeLayer() ) );

            QMetaObject::connectSlotsByName ( LayersManagerDialog );
        } // setupUi

        void retranslateUi ( QDialog *LayersManagerDialog ) {
            LayersManagerDialog->setWindowTitle ( QApplication::translate ( "LayersManagerDialog", "Dialog", 0, QApplication::UnicodeUTF8 ) );
            AddLayerPushButton->setText ( QApplication::translate ( "LayersManagerDialog", "&Add layer", 0, QApplication::UnicodeUTF8 ) );
            removePushButton->setText ( QApplication::translate ( "LayersManagerDialog", "&Remove layer", 0, QApplication::UnicodeUTF8 ) );
            removePushButton->setShortcut ( QApplication::translate ( "LayersManagerDialog", "Del", 0, QApplication::UnicodeUTF8 ) );
            groupBox->setTitle ( QApplication::translate ( "LayersManagerDialog", "Layer propeties", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "LayersManagerDialog", "Name:", 0, QApplication::UnicodeUTF8 ) );
            label_2->setText ( QApplication::translate ( "LayersManagerDialog", "Type:", 0, QApplication::UnicodeUTF8 ) );
            TypeComboBox->clear();
            TypeComboBox->insertItems ( 0, QStringList()
                                        << QApplication::translate ( "LayersManagerDialog", "NORMAL", 0, QApplication::UnicodeUTF8 )
                                        << QApplication::translate ( "LayersManagerDialog", "TRANSPARENT", 0, QApplication::UnicodeUTF8 )
                                        << QApplication::translate ( "LayersManagerDialog", "GUI", 0, QApplication::UnicodeUTF8 )
                                      );
        } // retranslateUi

};

namespace Ui {
    class LayersManagerDialog: public Ui_LayersManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSMANAGERDIALOG_H
