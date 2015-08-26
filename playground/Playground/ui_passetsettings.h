/********************************************************************************
** Form generated from reading UI file 'passetsettings.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSETSETTINGS_H
#define UI_PASSETSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PAssetSettings {
    public:
        QWidget *tab;
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QComboBox *comboBox;
        QHBoxLayout *horizontalLayout_4;
        QLabel *label_4;
        QComboBox *comboBox_2;
        QSpacerItem *verticalSpacer;
        QWidget *tab_2;
        QVBoxLayout *verticalLayout_2;
        QHBoxLayout *horizontalLayout_2;
        QLabel *label_2;
        QComboBox *AssetTypeComboBox;
        QHBoxLayout *horizontalLayout_3;
        QLabel *label_3;
        QLineEdit *ExternalEditorPathLineEdit;
        QSpacerItem *verticalSpacer_2;

        void setupUi ( QTabWidget *PAssetSettings ) {
            if ( PAssetSettings->objectName().isEmpty() ) {
                PAssetSettings->setObjectName ( QString::fromUtf8 ( "PAssetSettings" ) );
            }
            PAssetSettings->resize ( 284, 162 );
            tab = new QWidget();
            tab->setObjectName ( QString::fromUtf8 ( "tab" ) );
            verticalLayout = new QVBoxLayout ( tab );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( tab );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            comboBox = new QComboBox ( tab );
            comboBox->setObjectName ( QString::fromUtf8 ( "comboBox" ) );

            horizontalLayout->addWidget ( comboBox );


            verticalLayout->addLayout ( horizontalLayout );

            horizontalLayout_4 = new QHBoxLayout();
            horizontalLayout_4->setObjectName ( QString::fromUtf8 ( "horizontalLayout_4" ) );
            label_4 = new QLabel ( tab );
            label_4->setObjectName ( QString::fromUtf8 ( "label_4" ) );

            horizontalLayout_4->addWidget ( label_4 );

            comboBox_2 = new QComboBox ( tab );
            comboBox_2->setObjectName ( QString::fromUtf8 ( "comboBox_2" ) );

            horizontalLayout_4->addWidget ( comboBox_2 );


            verticalLayout->addLayout ( horizontalLayout_4 );

            verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

            verticalLayout->addItem ( verticalSpacer );

            PAssetSettings->addTab ( tab, QString() );
            tab_2 = new QWidget();
            tab_2->setObjectName ( QString::fromUtf8 ( "tab_2" ) );
            verticalLayout_2 = new QVBoxLayout ( tab_2 );
            verticalLayout_2->setObjectName ( QString::fromUtf8 ( "verticalLayout_2" ) );
            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName ( QString::fromUtf8 ( "horizontalLayout_2" ) );
            label_2 = new QLabel ( tab_2 );
            label_2->setObjectName ( QString::fromUtf8 ( "label_2" ) );

            horizontalLayout_2->addWidget ( label_2 );

            AssetTypeComboBox = new QComboBox ( tab_2 );
            AssetTypeComboBox->setObjectName ( QString::fromUtf8 ( "AssetTypeComboBox" ) );

            horizontalLayout_2->addWidget ( AssetTypeComboBox );


            verticalLayout_2->addLayout ( horizontalLayout_2 );

            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName ( QString::fromUtf8 ( "horizontalLayout_3" ) );
            label_3 = new QLabel ( tab_2 );
            label_3->setObjectName ( QString::fromUtf8 ( "label_3" ) );

            horizontalLayout_3->addWidget ( label_3 );

            ExternalEditorPathLineEdit = new QLineEdit ( tab_2 );
            ExternalEditorPathLineEdit->setObjectName ( QString::fromUtf8 ( "ExternalEditorPathLineEdit" ) );

            horizontalLayout_3->addWidget ( ExternalEditorPathLineEdit );


            verticalLayout_2->addLayout ( horizontalLayout_3 );

            verticalSpacer_2 = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

            verticalLayout_2->addItem ( verticalSpacer_2 );

            PAssetSettings->addTab ( tab_2, QString() );

            retranslateUi ( PAssetSettings );

            PAssetSettings->setCurrentIndex ( 0 );


            QMetaObject::connectSlotsByName ( PAssetSettings );
        } // setupUi

        void retranslateUi ( QTabWidget *PAssetSettings ) {
            PAssetSettings->setWindowTitle ( QApplication::translate ( "PAssetSettings", "TabWidget", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "PAssetSettings", "Double click:", 0, QApplication::UnicodeUTF8 ) );
            comboBox->clear();
            comboBox->insertItems ( 0, QStringList()
                                    << QApplication::translate ( "PAssetSettings", "Open in dock", 0, QApplication::UnicodeUTF8 )
                                    << QApplication::translate ( "PAssetSettings", "Open in external editor", 0, QApplication::UnicodeUTF8 )
                                  );
            label_4->setText ( QApplication::translate ( "PAssetSettings", "Edit dock position:", 0, QApplication::UnicodeUTF8 ) );
            comboBox_2->clear();
            comboBox_2->insertItems ( 0, QStringList()
                                      << QApplication::translate ( "PAssetSettings", "Top", 0, QApplication::UnicodeUTF8 )
                                      << QApplication::translate ( "PAssetSettings", "Bottom", 0, QApplication::UnicodeUTF8 )
                                      << QApplication::translate ( "PAssetSettings", "Left", 0, QApplication::UnicodeUTF8 )
                                      << QApplication::translate ( "PAssetSettings", "Right", 0, QApplication::UnicodeUTF8 )
                                      << QApplication::translate ( "PAssetSettings", "No docked", 0, QApplication::UnicodeUTF8 )
                                    );
            PAssetSettings->setTabText ( PAssetSettings->indexOf ( tab ), QApplication::translate ( "PAssetSettings", "General", 0, QApplication::UnicodeUTF8 ) );
            label_2->setText ( QApplication::translate ( "PAssetSettings", "Asset type:", 0, QApplication::UnicodeUTF8 ) );
            label_3->setText ( QApplication::translate ( "PAssetSettings", "Editor path:", 0, QApplication::UnicodeUTF8 ) );
            PAssetSettings->setTabText ( PAssetSettings->indexOf ( tab_2 ), QApplication::translate ( "PAssetSettings", "Editors", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PAssetSettings: public Ui_PAssetSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSETSETTINGS_H
