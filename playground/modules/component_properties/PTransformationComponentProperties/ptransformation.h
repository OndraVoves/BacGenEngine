#ifndef PTRANSFORMATION_H
#define PTRANSFORMATION_H

#include <QWidget>

#include <PlaygroundSDK/pcomponentproperties.h>

namespace Ui {
    class PTransformation;
}

class BTransformationComponent;

class PTransformation : public PComponentProperties {
        Q_OBJECT

    public:
        explicit PTransformation ( BackGenEngine::BAbstractComponent *pc_component, PActualProject *pc_actual_project );
        virtual ~PTransformation();
        virtual void updateData();
    private:
        Ui::PTransformation *ui;
        BTransformationComponent *pcComponent;


    private slots:
        /************
         * Positon. *
         ************/
        void posXChanged ( double x );
        void posYChanged ( double y );
        void posZChanged ( double z );

        /*************
         * Rotation. *
         *************/
        void rotXChanged ( double x );
        void rotYChanged ( double y );
        void rotZChanged ( double z );

        /**********
         * Scale. *
         **********/
        void scaXChanged ( double x );
        void scaYChanged ( double y );
        void scaZChanged ( double z );
};

#endif // PTRANSFORMATION_H
