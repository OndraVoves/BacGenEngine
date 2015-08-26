#include "pprojectsettingdialog.h"
#include "ui_pprojectsettingdialog.h"

#include <BackGenEngine/bproject.h>

#include <PlaygroundSDK/pactualproject.h>

#include <QMessageBox>

PProjectSettingDialog::PProjectSettingDialog ( PActualProject *pc_actual_project,  QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::PProjectSettingDialog ), pcActualProject ( pc_actual_project ) {
    ui->setupUi ( this );

    ui->NameLineEdit->setText ( pc_actual_project->project()->getName().constData() );

    connect ( ui->NameLineEdit, SIGNAL ( editingFinished() ), this, SLOT ( parseName() ) );
    connect ( this, SIGNAL ( accepted() ) , this, SLOT ( changeData() ) );
}

PProjectSettingDialog::~PProjectSettingDialog() {
    delete ui;
}

void PProjectSettingDialog::changeEvent ( QEvent *e ) {
    QDialog::changeEvent ( e );
    switch ( e->type() ) {
        case QEvent::LanguageChange:
            ui->retranslateUi ( this );
            break;
        default:
            break;
    }
}

void PProjectSettingDialog::parseName() {
    if ( ui->NameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Project setting" ),
                               tr ( "Project have empty name. Please set name." ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( pcActualProject->project()->getName().constData() );
        return;
    }
}

void PProjectSettingDialog::changeData() {
    pcActualProject->project()->setName ( ui->NameLineEdit->text().toStdString().c_str() );
}
