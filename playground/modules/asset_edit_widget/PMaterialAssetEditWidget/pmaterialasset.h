#ifndef PMATERIALASSET_H
#define PMATERIALASSET_H


#include <PlaygroundSDK/passeteditwidget.h>

namespace Ui {
    class PMaterialAsset;
}

class BMaterialAsset;

class PMaterialAsset : public PAssetEditWidget {
        Q_OBJECT

    public:
        explicit PMaterialAsset ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project );
        virtual ~PMaterialAsset();

        virtual void ok();
        virtual void apply();
        virtual void cancle();
        virtual void restore();

    protected:
        void changeEvent ( QEvent *e );

    private:
        Ui::PMaterialAsset *ui;
        BMaterialAsset *pcMaterial;

    private:
        void generateUnitItems();
};

#endif // PMATERIALASSET_H
