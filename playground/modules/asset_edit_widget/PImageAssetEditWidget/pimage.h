#ifndef PIMAGE_H
#define PIMAGE_H

#include <QWidget>

#include <PlaygroundSDK/passeteditwidget.h>

namespace Ui {
    class Pimage;
}

class BImageAsset;

class Pimage : public PAssetEditWidget {
        Q_OBJECT

    public:
        explicit Pimage ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project );
        virtual ~Pimage();

        virtual void ok();
        virtual void apply();
        virtual void cancle();
        virtual void restore();

    protected:
        void changeEvent ( QEvent *e );

    private:
        Ui::Pimage *ui;
        BImageAsset *pcImageAsset;

    private slots:
};

#endif // PIMAGE_H
