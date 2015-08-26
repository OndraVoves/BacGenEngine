#include "ptransformation.h"
#include "ui_ptransformation.h"

#include <PlaygroundSDK/modulesheader.h>
#include <limits>

#include <BTransformationComponent.h>

PTransformation::PTransformation ( BackGenEngine::BAbstractComponent *pc_component,  PActualProject *pc_actual_project ) :
    PComponentProperties ( pc_component, pc_actual_project ),
    ui ( new Ui::PTransformation ) {
    setObjectName (  "Transformation" );

    pcComponent = ( BTransformationComponent * ) pc_component;

    ui->setupUi ( this );

    /************
     * Positon. *
     ************/
    ui->PosXDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->PosYDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->PosZDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );

    /*************
     * Rotation. *
     *************/
    ui->RotXDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->RotYDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->RotZDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );

    /**********
     * Scale. *
     **********/
    ui->ScaXDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->ScaYDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );
    ui->ScaZDoubleSpinBox->setRange ( -std::numeric_limits<float>().max(), std::numeric_limits<float>().max() );

    updateData();
}

PTransformation::~PTransformation() {
    delete ui;
}

void PTransformation::updateData() {
    /************
     * Positon. *
     ************/
    ui->PosXDoubleSpinBox->setValue ( pcComponent->position().x() );
    ui->PosYDoubleSpinBox->setValue ( pcComponent->position().y() );
    ui->PosZDoubleSpinBox->setValue ( pcComponent->position().z() );


    /*************
     * Rotation. *
     *************/
    ui->RotXDoubleSpinBox->setValue ( pcComponent->rotation().x() );
    ui->RotYDoubleSpinBox->setValue ( pcComponent->rotation().y() );
    ui->RotZDoubleSpinBox->setValue ( pcComponent->rotation().z() );


    /**********
     * Scale. *
     **********/
    ui->ScaXDoubleSpinBox->setValue ( pcComponent->scale().x() );
    ui->ScaYDoubleSpinBox->setValue ( pcComponent->scale().y() );
    ui->ScaZDoubleSpinBox->setValue ( pcComponent->scale().z() );
}

void PTransformation::posXChanged ( double x ) {
    pcComponent->position().x ( x );
}

void PTransformation::posYChanged ( double y ) {
    pcComponent->position().y ( y );
}

void PTransformation::posZChanged ( double z ) {
    pcComponent->position().z ( z );
}

void PTransformation::rotXChanged ( double x ) {
    pcComponent->rotation().x ( x );
}

void PTransformation::rotYChanged ( double y ) {
    pcComponent->rotation().y ( y );
}

void PTransformation::rotZChanged ( double z ) {
    pcComponent->rotation().z ( z );
}

void PTransformation::scaXChanged ( double x ) {
    pcComponent->scale().x ( x );
}

void PTransformation::scaYChanged ( double y ) {
    pcComponent->scale().y ( y );
}

void PTransformation::scaZChanged ( double z ) {
    pcComponent->scale().z ( z );
}


extern "C" {
    PBASE_MODULE_HEADER ( COMPONENT_PROPERTIES, "Transformation", "0.0.1", "Ondra Voves" );
    PCOMPONENT_PROPERTIES_MODULE_HEADER ( "Transformation" );

    PComponentProperties *createComponentProperties ( BackGenEngine::BAbstractComponent *pc_component,  PActualProject *pc_actual_project  ) {
        return new PTransformation ( pc_component, pc_actual_project  );
    }
}
