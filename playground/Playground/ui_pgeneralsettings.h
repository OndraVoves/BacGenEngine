/********************************************************************************
** Form generated from reading UI file 'pgeneralsettings.ui'
**
** Created:
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PGENERALSETTINGS_H
#define UI_PGENERALSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PGeneralSettings {
    public:
        QWidget *tab;
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QComboBox *TabPositionComboBox;
        QSpacerItem *verticalSpacer;

        void setupUi ( QTabWidget *PGeneralSettings ) {
            if ( PGeneralSettings->objectName().isEmpty() ) {
                PGeneralSettings->setObjectName ( QString::fromUtf8 ( "PGeneralSettings" ) );
            }
            PGeneralSettings->resize ( 400, 300 );
            PGeneralSettings->setUsesScrollButtons ( true );
            PGeneralSettings->setDocumentMode ( false );
            tab = new QWidget();
            tab->setObjectName ( QString::fromUtf8 ( "tab" ) );
            verticalLayout = new QVBoxLayout ( tab );
            verticalLayout->setObjectName ( QString::fromUtf8 ( "verticalLayout" ) );
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
            label = new QLabel ( tab );
            label->setObjectName ( QString::fromUtf8 ( "label" ) );

            horizontalLayout->addWidget ( label );

            TabPositionComboBox = new QComboBox ( tab );
            TabPositionComboBox->setObjectName ( QString::fromUtf8 ( "TabPositionComboBox" ) );

            horizontalLayout->addWidget ( TabPositionComboBox );


            verticalLayout->addLayout ( horizontalLayout );

            verticalSpacer = new QSpacerItem ( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

            verticalLayout->addItem ( verticalSpacer );

            PGeneralSettings->addTab ( tab, QString() );

            retranslateUi ( PGeneralSettings );

            QMetaObject::connectSlotsByName ( PGeneralSettings );
        } // setupUi

        void retranslateUi ( QTabWidget *PGeneralSettings ) {
            PGeneralSettings->setWindowTitle ( QApplication::translate ( "PGeneralSettings", "TabWidget", 0, QApplication::UnicodeUTF8 ) );
            label->setText ( QApplication::translate ( "PGeneralSettings", "Dock tab position:", 0, QApplication::UnicodeUTF8 ) );
            TabPositionComboBox->clear();
            TabPositionComboBox->insertItems ( 0, QStringList()
                                               << QApplication::translate ( "PGeneralSettings", "Top", 0, QApplication::UnicodeUTF8 )
                                               << QApplication::translate ( "PGeneralSettings", "Bottom", 0, QApplication::UnicodeUTF8 )
                                               << QApplication::translate ( "PGeneralSettings", "Left", 0, QApplication::UnicodeUTF8 )
                                               << QApplication::translate ( "PGeneralSettings", "Right", 0, QApplication::UnicodeUTF8 )
                                             );
            PGeneralSettings->setTabText ( PGeneralSettings->indexOf ( tab ), QApplication::translate ( "PGeneralSettings", "General", 0, QApplication::UnicodeUTF8 ) );
        } // retranslateUi

};

namespace Ui {
    class PGeneralSettings: public Ui_PGeneralSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PGENERALSETTINGS_H
