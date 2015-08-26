#ifndef PDEFAULTEDITASSETWIDGET_H
#define PDEFAULTEDITASSETWIDGET_H

#include <QWidget>
#include <QAbstractButton>

#include <PlaygroundSDK/passeteditwidget.h>

namespace Ui {
    class PDefaultEditAssetWidget;
}

class PDefaultEditAssetWidget : public PAssetEditWidget {
        Q_OBJECT

    public:
        explicit PDefaultEditAssetWidget ( BackGenEngine::BAbstractAsset *pc_asset, PActualProject *pc_project, QWidget *parent = 0 );
        virtual ~PDefaultEditAssetWidget();
        virtual QLayout *getMainLayout();

        virtual void ok();
        virtual void apply();
        virtual void cancle();
        virtual void restore();

    private:
        Ui::PDefaultEditAssetWidget *ui;

        QString SuportedFormats;

        void generateSuportedFormats();

    private slots:
        bool parseName();
        void openFile();

};

#endif // PDEFAULTEDITASSETWIDGET_H
