#ifndef PTEXTUREASSET_H
#define PTEXTUREASSET_H

#include <PlaygroundSDK/passeteditwidget.h>

class BTextureAsset;

namespace Ui {
    class PTextureAsset;
}

class PTextureAsset : public PAssetEditWidget {
        Q_OBJECT

    public:
        explicit PTextureAsset ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project );
        virtual ~PTextureAsset();


        virtual void ok();
        virtual void apply();
        virtual void cancle();
        virtual void restore();

    protected:
        void changeEvent ( QEvent *e );

    private:
        Ui::PTextureAsset *ui;
        BTextureAsset *pcTexture;

    private:
        void generateImageAssetsItems();
};

#endif // PTEXTUREASSET_H
