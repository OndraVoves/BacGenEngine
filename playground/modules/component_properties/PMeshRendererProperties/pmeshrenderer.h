#ifndef PMESHRENDERER_H
#define PMESHRENDERER_H

#include <PlaygroundSDK/pcomponentproperties.h>

namespace Ui {
    class PMeshRenderer;
}

class BMeshRendererComponent;

class PMeshRenderer : public PComponentProperties {
        Q_OBJECT

    public:
        explicit PMeshRenderer ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project );
        virtual ~PMeshRenderer();
        virtual void updateData();

    protected:
        void changeEvent ( QEvent *e );

    private:
        Ui::PMeshRenderer *ui;
        BMeshRendererComponent *pcComponent;

        void generateMaterialsItems();

    private slots:
        void materialAssetItemChanged ( int index );
        void changeTX ( int x );
        void changeTY ( int y );
};

#endif // PMESHRENDERER_H
