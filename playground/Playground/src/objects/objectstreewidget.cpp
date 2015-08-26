#include "../../include/objects/objectstreewidget.h"

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/btagsmanager.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/btag.h>

#include <PlaygroundSDK/pactualproject.h>
#include "./include/mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDropEvent>
#include <QMessageBox>

ObjectsTreeWidget::ObjectsTreeWidget ( MainWindow *main_window, PActualProject *actual_project, QWidget *parent ) :
    QTreeWidget ( parent ), pcMainWindow ( main_window ), pcActualProject ( actual_project ) {
    headerItem()->setText ( 0, tr ( "Name" ) );

    setSelectionMode ( QAbstractItemView::SingleSelection );
    setAcceptDrops ( true );
    setDragEnabled ( true );
    setDropIndicatorShown ( true );
    setDragDropMode ( QTreeWidget::InternalMove );

    createActions();

    pcMenu = new QMenu ( tr ( "&Selected" ) );
    pcMenu->addAction ( pcActionDeleteObject );
    pcMenu->addAction ( pcActionDuplicateObject );
    pcMenu->setDisabled ( true );

    pcMainWindow->objectMenu()->addMenu ( pcMenu );

    disableMe();

    connect ( this,            SIGNAL ( itemActivated ( QTreeWidgetItem *, int ) ), this, SLOT ( objectActivated ( QTreeWidgetItem *, int ) ) );
    connect ( pcActualProject, SIGNAL ( objectChanged ( QString, BackGenEngine::BObject * ) ), this, SLOT ( updateObjectItem ( QString, BackGenEngine::BObject * ) ) );
    connect ( pcActualProject, SIGNAL ( sceneOpened ( BackGenEngine::BScene * ) ), this, SLOT ( sceneActivated ( BackGenEngine::BScene * ) ) );
}

ObjectsTreeWidget::~ObjectsTreeWidget() {
    pcMainWindow->objectMenu()->setDisabled ( true );
    deleteActions();

    delete pcMenu;
    pcMenu = 0;
}

void ObjectsTreeWidget::enableMe() {
    setEnabled ( true );
}

void ObjectsTreeWidget::disableMe() {
    setDisabled ( true );
}

void ObjectsTreeWidget::fillObjectTree() {
    clear();

    QTreeWidgetItem *pc_tmp_item = 0;
    BackGenEngine::BTag::bobject_hash_t::ConstIterator it = pcActualProject->actualScene()->getTagsManager().rootTag().constBegin();
    while ( it != pcActualProject->actualScene()->getTagsManager().rootTag().constEnd() ) {
        if ( ( *it )->getParent() != 0 ) {
            ++it;
            continue;
        }

        pc_tmp_item = new QTreeWidgetItem ( this );
        updateObjectItem ( ( *it ), pc_tmp_item );
        createObjectTreeItems ( ( *it ), pc_tmp_item );

        ++it;
    }
}

void ObjectsTreeWidget::dropEvent ( QDropEvent *event ) {
    ObjectsTreeWidget *source = qobject_cast< ObjectsTreeWidget * > ( event->source() );

    QTreeWidgetItem *draged = source->currentItem();
    QTreeWidgetItem *droped = itemAt ( event->pos() );

    BackGenEngine::BObject *pc_draged_object = ( BackGenEngine::BObject * ) draged->data ( 0, Qt::UserRole ).value<void *>();

    BackGenEngine::BObject *pc_droped_object = 0;

    if ( droped != 0 ) {
        pc_droped_object = ( BackGenEngine::BObject * ) droped->data ( 0, Qt::UserRole ).value<void *>();
    }

    if ( pc_draged_object == pc_droped_object ) {
        return;
    }

    pc_draged_object->setParent ( pc_droped_object );

    QTreeWidget::dropEvent ( event );
}

void ObjectsTreeWidget::createActions() {
    pcActionNewObject = new QAction ( QIcon ( ":/images/gameobject-add.png" ), tr ( "Create &new" ), this );
    pcMainWindow->objectMenu()->addAction ( pcActionNewObject );

    connect ( pcActionNewObject, SIGNAL ( activated() ), this, SLOT ( createNewObject() ) );

    pcActionDeleteObject = new QAction ( QIcon ( ":/images/gameobject-remove.png" ), tr ( "&Delete selected" ), this );
    connect ( pcActionDeleteObject, SIGNAL ( activated() ), this, SLOT ( deleteSelectedObject() ) );

    pcActionDuplicateObject = new QAction ( tr ( "Duplicate selected" ), this );
    connect ( pcActionDuplicateObject, SIGNAL ( activated() ), this, SLOT ( duplicateSelectedObject() ) );
}

void ObjectsTreeWidget::deleteActions() {
    delete pcActionNewObject;
    delete pcActionDeleteObject;
}

void ObjectsTreeWidget::updateObjectItem ( BackGenEngine::BObject *pc_object, QTreeWidgetItem *pc_item ) {
    pc_item->setIcon ( 0, QIcon ( ":/images/applications-toys.png" ) );
    pc_item->setText ( 0, pc_object->getName().constData() );
    pc_item->setData ( 0, Qt::UserRole, qVariantFromValue ( ( void * ) pc_object ) );

    /************
     * Tooltips *
     ************/
    QString tool_tip;

    //name
    tool_tip.append ( tr ( "<b>Name: </b>%1<br/>" ).arg ( pc_object->getName().constData() ) );

    //layer
    tool_tip.append ( tr ( "<b>Layer: </b>" ) );
    if ( pc_object->layer() ) {
        tool_tip.append ( QString ( "%1<br/>" ).arg ( pc_object->layer()->getName().constData() ) );
    } else {
        tool_tip.append ( tr ( "None<br/>" ) );
    }

    // tags
    tool_tip.append ( tr ( "<b>Tags:</b><br/>" ) );

    BackGenEngine::BObject::btags_hash_t::ConstIterator it = pc_object->tagsHash().constBegin();
    while ( it != pc_object->tagsHash().constEnd() ) {
        tool_tip.append ( QString ( "%1<br/>" ).arg ( it.key().constData() ) );
        ++it;
    }

    // Components.
    tool_tip.append ( tr ( "<b>Components: </b><br>" ) );
    BackGenEngine::BObject::component_vector_t::ConstIterator it2 = pc_object->getComponentVector().constBegin();
    while ( it2 != pc_object->getComponentVector().constEnd() ) {
        tool_tip.append ( QString ( "<img width=\"16\" height=\"16\" src=\"./images/components/%1.png\" /> %1<br/>" ).arg ( ( *it2 )->getName().constData() ) );
        ++it2;
    }

    pc_item->setToolTip ( 0, tool_tip );
}


void ObjectsTreeWidget::createObjectTreeItems ( BackGenEngine::BObject *pc_object, QTreeWidgetItem *pc_item ) {
    BackGenEngine::BObject::objects_list_t::ConstIterator it = pc_object->getObjectsList().constBegin();

    BackGenEngine::BObject *pc_tmp_object = 0;
    QTreeWidgetItem *pc_tmp_item = 0;
    while ( it != pc_object->getObjectsList().constEnd() ) {
        pc_tmp_object = ( *it );

        if ( pc_tmp_object == 0 ) {
            continue;
        }

        pc_tmp_item = new QTreeWidgetItem ( pc_item );

        updateObjectItem ( pc_tmp_object, pc_tmp_item );
        createObjectTreeItems ( pc_tmp_object, pc_tmp_item );

        ++it;
    }
}


void ObjectsTreeWidget::contextMenuEvent ( QContextMenuEvent *e ) {
    QMenu context_menu ( this );

    context_menu.addAction ( pcActionNewObject );

    if ( !selectedItems().isEmpty() ) {
        context_menu.addAction (  pcActionDeleteObject );
        context_menu.addAction (  pcActionDuplicateObject );
    }

    context_menu.exec ( e->globalPos() );
}

void ObjectsTreeWidget::createNewObject() {
    QString name ( "Object_1" );
    int i = 2;
    while ( pcActualProject->actualScene()->getTagsManager().rootTag().containObject ( name.toStdString().c_str() ) ) {
        name = QString ( "Object_%1" ).arg ( i );
        i++;
    }

    BackGenEngine::BObject *pc_new_object = new BackGenEngine::BObject ( name.toStdString().c_str(), 0 );
    pcActualProject->actualScene()->getTagsManager().rootTag().insertObject ( pc_new_object );

    QTreeWidgetItem *pc_new_item = new QTreeWidgetItem ( this );
    updateObjectItem ( pc_new_object, pc_new_item );
}

void ObjectsTreeWidget::deleteSelectedObject() {
    QTreeWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BObject *pc_object = ( BackGenEngine::BObject * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    int ret = QMessageBox::question ( this, tr ( "Do you really want..." ),
                                      tr ( "Do you really want to delete \"%1\" object?" ).arg ( pc_object->getName().constData() ),
                                      QMessageBox::Ok | QMessageBox::Cancel );

    if ( ret == QMessageBox::Cancel ) {
        return;
    }

    delete pc_object;
    delete pc_item;

    pcActualProject->activateObject ( 0 );
    pcMenu->setDisabled ( true );
    pcMainWindow->componentMenu()->setDisabled ( true );
}

void ObjectsTreeWidget::duplicateSelectedObject() {
    QTreeWidgetItem *pc_item = selectedItems().first();
    BackGenEngine::BObject *pc_selected_object = ( BackGenEngine::BObject * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    BackGenEngine::BObject *pc_duplicated_object = pc_selected_object->duplicate();

    if ( !pc_duplicated_object ) {
        return;
    }

    QTreeWidgetItem *pc_new_item = new QTreeWidgetItem ( pc_item->parent() );

    pcActualProject->actualScene()->getTagsManager().rootTag().insertObject ( pc_duplicated_object );
    updateObjectItem ( pc_duplicated_object, pc_new_item );
    createObjectTreeItems ( pc_duplicated_object, pc_new_item );

    if ( !pc_item->parent() ) {
        insertTopLevelItem ( 0, pc_new_item );
    }
}


void ObjectsTreeWidget::objectActivated ( QTreeWidgetItem *pc_item, int col ) {
    ( void ) col;

    BackGenEngine::BObject *pc_object = ( BackGenEngine::BObject * ) pc_item->data ( 0, Qt::UserRole ).value<void *>();

    pcMenu->setEnabled ( true );
    pcMainWindow->componentMenu()->setEnabled ( true );
    pcActualProject->activateObject ( pc_object );
}


void ObjectsTreeWidget::updateObjectItem ( QString old_name, BackGenEngine::BObject *pc_object ) {
    QList<QTreeWidgetItem *> items_list = findItems ( old_name, Qt::MatchCaseSensitive | Qt::MatchRecursive );
    if ( items_list.count() != 1 ) {
        return;
    }

    updateObjectItem ( pc_object, items_list.first() );
}

void ObjectsTreeWidget::sceneActivated ( BackGenEngine::BScene *pc_scene ) {
    pcActualProject->activateObject ( 0 );
    if ( pc_scene ) {
        fillObjectTree();
        enableMe();
    } else {
        clear();
        disableMe();
    }
}
