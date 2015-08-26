#include <PlaygroundSDK/modulesheader.h>

#include <BackGenEngine/babstractasset.h>
#include <PlaygroundSDK/pactualproject.h>

#include <QTreeWidgetItem>

#include <QDebug>
#include <BImageAsset.h>

extern "C" {
    PBASE_MODULE_HEADER ( ASSET_ITEM_HELPER, "Image asset helper", "0.0.1", "Ondra Voves" );
    PASSET_ITEM_HELPER_MODULE_HEADER ( "Image" );

    void updateAssetItem ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QTreeWidgetItem *pc_item ) {
        BImageAsset *pc_image_asset = ( BImageAsset * ) pc_asset;
        pc_image_asset->use();

        QString tool_type;

        tool_type.append ( QString ( "<b>Size: </b> %1x%2" ).arg ( pc_image_asset->width() ).arg ( pc_image_asset->height() ) );

        pc_item->setToolTip ( 0, tool_type  );

        if ( pc_image_asset->pixels() ) {
            QImage image ( pc_image_asset->pixels(), pc_image_asset->width(), pc_image_asset->height(), QImage::Format_RGB888 );
            image = image.scaled ( 32, 32, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

            QPixmap pixmap;
            pixmap.convertFromImage ( image );
            pc_item->setIcon ( 0, QIcon ( pixmap ) );
        }

        pc_image_asset->unuse();
    }
}
