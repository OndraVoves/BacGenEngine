#include "../../include/scenes/sceneeditdialog.h"
#include "ui_sceneeditdialog.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QFile>

#include <BackGenEngine/bscene.h>
#include <BackGenEngine/bscenemanager.h>
#include <BackGenEngine/bproject.h>

#include <PlaygroundSDK/pactualproject.h>

SceneEditDialog::SceneEditDialog (  PActualProject *pc_actual_project, BackGenEngine::BScene *pc_actual_scene, QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::SceneEditDialog ), pcActualProject ( pc_actual_project ), pcScene ( pc_actual_scene ) {
    ui->setupUi ( this );

    ui->SceneNameLineEdit->setText ( pcScene->getName().constData() );

    connect ( this, SIGNAL ( accepted() ), this, SLOT ( changeData() ) );
}

SceneEditDialog::~SceneEditDialog() {
    delete ui;
}

void SceneEditDialog::keyPressEvent ( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Escape:
            break;

        default:
            QDialog::keyPressEvent ( event );
    }

}

void SceneEditDialog::parseName() {
    if ( pcScene->getName() == ui->SceneNameLineEdit->text().toStdString().c_str() ) {
        return;
    }

    if ( ui->SceneNameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Scene edit dialog" ), tr ( "Scene name is empty.\n Please set name." ), QMessageBox::Ok );
        ui->SceneNameLineEdit->setText ( pcScene->getName().constData() );
        return;
    }

    if ( pcActualProject->project()->getSceneManager().containScene ( ui->SceneNameLineEdit->text().toStdString().c_str() ) ) {
        QMessageBox::warning ( this, tr ( "Scene edit dialog" ), tr ( "Scene with this name is exist.\n Please set diferent name." ), QMessageBox::Ok );
        ui->SceneNameLineEdit->setText ( pcScene->getName().constData() );
        return;
    }


    // TODO: regexp

}

void SceneEditDialog::changeData() {
    if ( ui->SceneNameLineEdit->text() != pcScene->getName().constData() ) {
        QString scene_old_filename = QString ( "%1data/scenes/%2.scene" ).arg ( pcActualProject->project()->getBaseDir().constData() )
                                     .arg ( pcScene->getName().constData() );

        pcScene->setName ( ui->SceneNameLineEdit->text().toStdString().c_str() );

        // Remove file.
        QString scene_new_filename = QString ( "%1data/scenes/%2.scene" ).arg ( pcActualProject->project()->getBaseDir().constData() )
                                     .arg ( pcScene->getName().constData() );

        if ( QFile::exists ( scene_old_filename ) ) {
            QFile::rename ( scene_old_filename, scene_new_filename );
        }

    }
}
