#ifndef BEDITORCAMERACOMPONENT_H
#define BEDITORCAMERACOMPONENT_H

#include <BackGenEngine/babstractcameracomponent.h>
#include <BackGenEngine/blayer.h>
#include <BackGenEngine/babstractframebuffer.h>
#include <BackGenEngine/babstracttexture.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/brenderablecomponent.h>
#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bviewfrustrum.h>


#include <BoxE/BoxECore>

class BEditorCameraComponent : public BackGenEngine::BAbstractCameraComponent {
    public:
        typedef enum {
            Perspective = 0,
            Front,
            Back,
            Left,
            Right,
            Top,
            Bottom
        } EViewType;
    public:
        BEditorCameraComponent ( BackGenEngine::BScene *pc_scene );

        virtual ~BEditorCameraComponent();

        bool resize ( int width, int height );

        virtual void render( );

        virtual BackGenEngine::BAbstractTexture *getOutputTexture();

        void setViewType ( EViewType view_type );
        EViewType getViewType( ) const;

        BoxE::Math::BRay3f getRayFromScreen ( int x, int y );

        virtual BackGenEngine::BAbstractComponent *duplicate() const;

        void setNormalEditorLayer ( BackGenEngine::BLayer *pc_layer );

        const BackGenEngine::BViewFrustrum &getViewFrustrum() const;

        // MOVE
        void goFront();
        void goBack();
        void goLeft();
        void goRight();

        void rotate ( int x, int y );
    protected:
        void renderObject ( BackGenEngine::BObject *pc_object );
        void renderLayer ( BackGenEngine::BLayer *pc_layer );

        void renderNormalLayers( );
        void renderTransparentlLayers( );
        void renderGUILayers( );

    public:
        bool insertLayer ( BackGenEngine::BLayer *pc_layer );
        bool removeLayer ( BackGenEngine::BLayer *pc_layer );

    private:
        BackGenEngine::BAbstractFrameBuffer *pcFBO;
        BackGenEngine::BAbstractTexture *pcTexture;

        EViewType eViewType;

        BackGenEngine::BLayer *pcNormalEditorLayer;

        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > NormalLayersHash;
        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > TransparentLayersHash;
        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > GUILayersHash;


        bool insertLayer ( BackGenEngine::BLayer *pc_layer, BackGenEngine::BLayer::ELayerType type );

        /*!
         * On layer type changed.
         * \param layer Layer.
         * \param new_type New layer type.
         */
        void onLayerTypeChaned ( BackGenEngine::BLayer *layer, BackGenEngine::BLayer::ELayerType new_type );

        /*!
         * On layer name changed.
         * \param layer Layer.
         * \param new_name New name.
         */
        void onLayerNameChaned ( BackGenEngine::BLayer *layer, BoxE::Core::BAsciiString new_name  );


        BoxE::Math::BMatrix4x4f ModelViewMatrix;
        BoxE::Math::BMatrix4x4f PerspectiveMatrix;
        BackGenEngine::BViewFrustrum ViewFrustrum;

        void updateFrustrum();
        void updateMatrix();

        BoxE::Math::BVector3f Dir;
        BoxE::Math::BVector2f Angles;

};
#endif // BEDITORCAMERACOMPONENT_H

