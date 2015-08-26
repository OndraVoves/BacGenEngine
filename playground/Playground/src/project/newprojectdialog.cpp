#include "../../include/project/newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include <PlaygroundSDK/pactualproject.h>

#include <QFileDialog>
#include <QMessageBox>

NewProjectDialog::NewProjectDialog ( PActualProject *actual_project, QWidget *parent )
    : QDialog ( parent ), ui ( new Ui::NewProjectDialog ), ActualProject ( actual_project )  {
    ui->setupUi ( this );

    connect ( this, SIGNAL ( accepted() ), this, SLOT ( createProject() ) );
}

NewProjectDialog::~NewProjectDialog() {
    delete ui;
}

QString NewProjectDialog::gameDir() const {
    return ui->ProjectDirLineEdit->text();
}

bool NewProjectDialog::parseName() {
    // Empty name.
    if ( ui->ProjectNameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "New project dialog" ),
                               tr ( "Project name is empty.\nPlease set name." ), QMessageBox::Ok );
        return false;
    }

    return true;
}

bool NewProjectDialog::parseDir() {
    // Empty dir.
    if ( ui->ProjectDirLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "New project dialog" ),
                               tr ( "Project dir is empty.\nPlease set path." ), QMessageBox::Ok );
        return false;
    }

    return true;
}

void NewProjectDialog::openDir() {
    ui->ProjectDirLineEdit->setText ( QFileDialog::getExistingDirectory ( this, tr ( "Select project top directory." ) ) );
}

void NewProjectDialog::createProject() {
    if ( parseName() && parseDir() ) {
        ActualProject->create ( ui->ProjectNameLineEdit->text() , ui->ProjectDirLineEdit->text() );
    }

    close();
}
