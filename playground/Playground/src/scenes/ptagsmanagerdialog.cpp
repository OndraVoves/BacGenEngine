#include "../../include/scenes/ptagsmanagerdialog.h"
#include "ui_ptagsmanagerdialog.h"

#include <PlaygroundSDK/pactualproject.h>

#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>

#include <BackGenEngine/bscene.h>
#include <BackGenEngine/btag.h>
#include <BackGenEngine/btagsmanager.h>

PTagsManagerDialog::PTagsManagerDialog ( BackGenEngine::BScene *pc_scene, PActualProject *pc_actual_project, QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::PTagsManagerDialog ), pcScene ( pc_scene ), pcActualTag ( 0 ), pcActualProject ( pc_actual_project ) {
    ui->setupUi ( this );

    fillTagsList();

    // TODO
    connect ( ui->TagsListWidget, SIGNAL ( itemActivated ( QListWidgetItem * ) ), this, SLOT ( tagActivated ( QListWidgetItem * ) ) );
}

PTagsManagerDialog::~PTagsManagerDialog() {
    delete ui;
}

void PTagsManagerDialog::keyPressEvent ( QKeyEvent *event ) {
    switch ( event->key() ) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            //case Qt::Key_Escape:
            break;

        default:
            QDialog::keyPressEvent ( event );
    }

}

void PTagsManagerDialog::fillTagsList() {
    BackGenEngine::BTagsManager::btag_hash_t::ConstIterator it =  pcScene->getTagsManager().tagsHash().constBegin();

    while ( it != pcScene->getTagsManager().tagsHash().constEnd() ) {
        QListWidgetItem *pc_new_item = new QListWidgetItem ( ui->TagsListWidget );
        updateTagItem ( ( *it ), pc_new_item );
        ++it;
    }
}

void PTagsManagerDialog::updateTagItem ( BackGenEngine::BTag *pc_tag, QListWidgetItem *pc_item ) {
    pc_item->setText ( pc_tag->getName().constData() );
    pc_item->setData ( Qt::UserRole, qVariantFromValue ( ( void * ) pc_tag ) );
    pc_item->setIcon ( QIcon ( ":/images/mail-tagged.png" ) );
}

void PTagsManagerDialog::newTag() {
    QString name ( "NewTag_1" );
    int i = 2;
    while ( pcScene->getTagsManager().containTag ( name.toStdString().c_str() ) ) {
        name = QString ( "NewTag_%1" ).arg ( i );
        i++;
    }

    BackGenEngine::BTag *pc_tag = pcScene->getTagsManager().createTag ( name.toStdString().c_str() );

    if ( !pc_tag ) {
        QMessageBox::critical ( this, tr ( "Tags manager" ), tr ( "Could not create tag." ), QMessageBox::Ok );
        return;
    }

    QListWidgetItem *pc_new_item = new QListWidgetItem ( ui->TagsListWidget );

    updateTagItem ( pc_tag, pc_new_item );
    pcActualProject->changeTagManager();
}

void PTagsManagerDialog::removeTag() {
    QListWidgetItem *pc_item = ui->TagsListWidget->selectedItems().first();
    BackGenEngine::BTag *pc_tag = ( BackGenEngine::BTag * ) pc_item->data ( Qt::UserRole ).value<void *>();

    int ret = QMessageBox::question ( this, tr ( "Do you really want..." ),
                                      tr ( "Do you really want to delete \"%1\" tag?" ).arg ( pc_tag->getName().constData() ),
                                      QMessageBox::Ok | QMessageBox::Cancel );

    if ( ret == QMessageBox::Cancel ) {
        return;
    }

    pcScene->getTagsManager().removeTag ( pc_tag );

    delete pc_tag;
    delete pc_item;

    ui->NameLineEdit->setText ( "" );
    ui->NameLineEdit->setDisabled ( true );
    ui->removeTagPushButton->setEnabled ( false );

    pcActualProject->changeTagManager();
}

void PTagsManagerDialog::setName() {
    QString old_name = pcActualTag->getName().constData();

    // No name changed.
    if ( old_name == ui->NameLineEdit->text().toStdString().c_str() ) {
        return;
    }

    if ( ui->NameLineEdit->text().isEmpty() ) {
        QMessageBox::warning ( this, tr ( "Tags manager" ),
                               tr ( "Tag name is empty.\nPleas set name" ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( old_name );
        return;
    }

    if ( pcScene->getTagsManager().containTag ( ui->NameLineEdit->text().toStdString().c_str() ) ) {
        QMessageBox::warning ( this, tr ( "Tags manager" ),
                               tr ( "tag with this name is exist.\nPleas set name" ), QMessageBox::Ok );

        ui->NameLineEdit->setText ( old_name );
        return;
    }

    QList<QListWidgetItem *> items_list = ui->TagsListWidget->findItems ( old_name, Qt::MatchCaseSensitive );
    if ( items_list.count() != 1 ) {
        return;
    }

    items_list.first()->setText ( ui->NameLineEdit->text() );


    pcActualTag->setName ( ui->NameLineEdit->text().toStdString().c_str() );
    pcActualProject->changeTagManager();
}

void PTagsManagerDialog::tagActivated ( QListWidgetItem *pc_item ) {
    pcActualTag = ( BackGenEngine::BTag * ) pc_item->data ( Qt::UserRole ).value<void *>();
    ui->NameLineEdit->setText ( pc_item->text() );
    ui->NameLineEdit->setEnabled ( true );
    ui->removeTagPushButton->setEnabled ( true );
}
