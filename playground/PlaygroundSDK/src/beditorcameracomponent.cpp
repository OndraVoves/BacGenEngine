#include "../include/beditorcameracomponent.h"

#include "bopenglframebuffer.h"
#include "bopengltexture.h"
#include "bopenglrenderer.h"

#include <BoxE/BoxECore>

#include <BTransformationComponent.h>

BEditorCameraComponent::BEditorCameraComponent ( BackGenEngine::BScene *pc_scene )
    : BAbstractCameraComponent ( pc_scene ), pcFBO ( 0 ), pcTexture ( 0 ), eViewType ( Perspective ), Dir ( 0.0f, 0.0f, -1.0f ), Angles ( -90, 0 ) {
    BackGenEngine::BAbstractRenderer *pc_renderer = getScene()->getRenderer();

    pcFBO =  pc_renderer->createFramebuffer();
}

BEditorCameraComponent::~BEditorCameraComponent() {
}

bool BEditorCameraComponent::resize ( int width, int height ) {
    if ( pcTexture ) {
        delete pcTexture;
    }

    getScene()->getRenderer()->onScreenChanged ( BoxE::Math::BVector3f ( width, height, 0 ), false );

    pcTexture = getScene()->getRenderer()->createTexture ( width, height, false, BOpenGLTexture::FT_BILINEAR, BOpenGLTexture::TF_RGBA8, BOpenGLTexture::TF_RGBA, 0  );

    pcFBO->attachColor0Texture ( pcTexture );
}

void BEditorCameraComponent::render( ) {
    updateMatrix();

    pcFBO->begin();

    getScene()->getRenderer()->beginRender ( true, true, BoxE::Math::BVector3f ( 0.172549f, 0.447059f, 0.780392f ) );

    renderNormalLayers();
    renderTransparentlLayers();
    renderGUILayers();

    getScene()->getRenderer()->endRender( );
    pcFBO->end();
}

BackGenEngine::BAbstractTexture *BEditorCameraComponent::getOutputTexture() {
    return pcTexture;
}

void BEditorCameraComponent::setViewType ( EViewType view_type ) {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();
    switch ( view_type ) {
        case Perspective:
            break;

        case Front:
            pc_transform->rotation().setXYZ ( 0.0f, 0.0f, 0.0f );
            break;

        case Back:
            pc_transform->rotation().setXYZ ( 0.0f, 180.0f, 0.0f );
            break;

        case Left:
            pc_transform->rotation().setXYZ ( 0.0f, 270.0f, 0.0f );
            break;

        case Right:
            pc_transform->rotation().setXYZ ( 0.0f, 90.0f, 0.0f );
            break;

        case Top:
            pc_transform->rotation().setXYZ ( 90.0f, 0.0f, 0.0f );
            break;

        case Bottom:
            pc_transform->rotation().setXYZ ( 270.0f, 0.0f, 0.0f );
            break;
    }

    eViewType = view_type;
}

BEditorCameraComponent::EViewType BEditorCameraComponent::getViewType( ) const {
    return eViewType;
}

BoxE::Math::BRay3f BEditorCameraComponent::getRayFromScreen ( int x, int y ) {
    BoxE::Math::BVector3f farLeftUp = ViewFrustrum.getFarLeftUp();
    BoxE::Math::BVector3f leftright = ViewFrustrum.getFarRightUp() - farLeftUp;
    BoxE::Math::BVector3f updown = ViewFrustrum.getFarLeftDown() - farLeftUp;

    float dx = ( float ) x / pcTexture->width();
    float dy = ( float ) y / pcTexture->height();

    // ortho if


    BoxE::Math::BVector3f dir = ( farLeftUp + ( leftright * dx ) + ( updown * dy ) );
    dir.normalize();

    return BoxE::Math::BRay3f ( getOwnerObject()->getComponent<BTransformationComponent>()->position(),
                                dir );
}

BackGenEngine::BAbstractComponent  *BEditorCameraComponent::duplicate() const {
    return 0;
}


void BEditorCameraComponent::setNormalEditorLayer ( BackGenEngine::BLayer *pc_layer ) {
    pcNormalEditorLayer = pc_layer;
}

const BackGenEngine::BViewFrustrum &BEditorCameraComponent::getViewFrustrum() const {
    return ViewFrustrum;
}

void BEditorCameraComponent::goFront() {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();
    pc_transform->position() -= Dir * 0.1f;
}

void BEditorCameraComponent::goBack() {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();
    pc_transform->position() += Dir * 0.1f;
}

void BEditorCameraComponent::goLeft() {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();

    pc_transform->position() -= BoxE::Math::BVector3f::crossProduct ( BoxE::Math::BVector3f::UP, Dir ) * 0.1f;
}

void BEditorCameraComponent::goRight() {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();

    pc_transform->position() -= BoxE::Math::BVector3f::crossProduct ( Dir, BoxE::Math::BVector3f::UP ) * 0.1f;
}

void BEditorCameraComponent::rotate ( int x, int y ) {
    Angles.x ( Angles.x() + x * 0.1 );
    Angles.y ( Angles.y() + y * 0.1 );

    Dir.x ( cos ( BoxE::Math::bDeg2Rad ( Angles.x() ) ) );
    Dir.z ( sin ( BoxE::Math::bDeg2Rad ( Angles.x() ) ) );
    Dir.y ( -sin ( BoxE::Math::bDeg2Rad ( Angles.y() ) ) );

    Dir.normalize();
}

void BEditorCameraComponent::renderObject ( BackGenEngine::BObject *pc_object )  {
    BackGenEngine::BRenderableComponent *pc_component = pc_object->getComponent<BackGenEngine::BRenderableComponent>();
    if ( pc_component ) {
        pc_component->render();
    }
}

void BEditorCameraComponent::renderLayer ( BackGenEngine::BLayer *pc_layer ) {
    BackGenEngine::BLayer::bobject_hash_t::ConstIterator it = pc_layer->constBegin();
    while ( it != pc_layer->constEnd() ) {
        renderObject ( ( *it ) );
        ++it;
    }
}

void BEditorCameraComponent::renderNormalLayers( ) {
    getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_PROJECTION );
    getScene()->getRenderer()->setMatrix ( BOpenGLRenderer::MT_PROJECTION, PerspectiveMatrix );

    getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_WORLD );
    getScene()->getRenderer()->setMatrix (  BOpenGLRenderer::MT_WORLD, ModelViewMatrix );

    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = NormalLayersHash.constBegin();
    while ( it != NormalLayersHash.constEnd() ) {
        renderLayer ( ( *it ) );
        ++it;
    }

    glClear ( GL_DEPTH_BUFFER_BIT );

    renderLayer ( pcNormalEditorLayer );

    getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_WORLD  );
    getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_PROJECTION  );
}


void BEditorCameraComponent::renderTransparentlLayers( ) {
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = TransparentLayersHash.constBegin();

    while ( it != TransparentLayersHash.constEnd() ) {
        renderLayer ( ( *it ) );
        ++it;
    }
}

void BEditorCameraComponent::renderGUILayers( ) {
    getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_PROJECTION );
    //getScene()->getRenderer()->setMatrix ( BOpenGLRenderer::MT_PROJECTION, OrthoMatrix );

    getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_WORLD );
    getScene()->getRenderer()->loadIdentityMatrix ( BOpenGLRenderer::MT_WORLD );

    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = GUILayersHash.constBegin();
    while ( it != GUILayersHash.constEnd() ) {
        renderLayer ( ( *it ) );
        ++it;
    }

    getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_WORLD  );
    getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_PROJECTION  );
}

bool BEditorCameraComponent::insertLayer ( BackGenEngine::BLayer *pc_layer ) {
    switch ( pc_layer->getLayerType() ) {
        case BackGenEngine::BLayer::NORMAL:
            NormalLayersHash.insert ( pc_layer->getName(), pc_layer );
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            TransparentLayersHash.insert ( pc_layer->getName(), pc_layer );
            break;

        case BackGenEngine::BLayer::GUI:
            GUILayersHash.insert ( pc_layer->getName(), pc_layer );
            break;
    }

    pc_layer->onNameChanged().connect ( this, &BEditorCameraComponent::onLayerNameChaned );
    pc_layer->onLayerTypeChanged().connect ( this, &BEditorCameraComponent::onLayerTypeChaned );
}

bool BEditorCameraComponent::removeLayer ( BackGenEngine::BLayer *pc_layer ) {
    switch ( pc_layer->getLayerType() ) {
        case BackGenEngine::BLayer::NORMAL:
            if ( NormalLayersHash.contains ( pc_layer->getName() ) ) {
                NormalLayersHash.erase ( NormalLayersHash.find ( pc_layer->getName() ) );
            }
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            if ( TransparentLayersHash.contains ( pc_layer->getName() ) ) {
                TransparentLayersHash.erase ( TransparentLayersHash.find ( pc_layer->getName() ) );
            }
            break;

        case BackGenEngine::BLayer::GUI:
            if ( GUILayersHash.contains ( pc_layer->getName() ) ) {
                GUILayersHash.erase ( GUILayersHash.find ( pc_layer->getName() ) );
            }
            break;
    }

    pc_layer->onNameChanged().disconnect ( this, &BEditorCameraComponent::onLayerNameChaned );
    pc_layer->onLayerTypeChanged().disconnect ( this, &BEditorCameraComponent::onLayerTypeChaned );
}

bool BEditorCameraComponent::insertLayer ( BackGenEngine::BLayer *pc_layer, BackGenEngine::BLayer::ELayerType type ) {
    switch ( type ) {
        case BackGenEngine::BLayer::NORMAL:
            NormalLayersHash.insert ( pc_layer->getName(), pc_layer ) ;
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            TransparentLayersHash.insert ( pc_layer->getName(), pc_layer ) ;
            break;

        case BackGenEngine::BLayer::GUI:
            GUILayersHash.insert ( pc_layer->getName(), pc_layer ) ;
            break;
    }
}

void BEditorCameraComponent::onLayerTypeChaned ( BackGenEngine::BLayer *layer, BackGenEngine::BLayer::ELayerType new_type ) {
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::Iterator it = NormalLayersHash.begin();
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::Iterator it_end = NormalLayersHash.end();
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >* pc_hash;

    switch ( layer->getLayerType() ) {
        case BackGenEngine::BLayer::NORMAL:
            pc_hash = &NormalLayersHash;
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            it = TransparentLayersHash.begin();
            it_end = TransparentLayersHash.end();
            pc_hash = &TransparentLayersHash;
            break;

        case BackGenEngine::BLayer::GUI:
            it = GUILayersHash.begin();
            it_end = GUILayersHash.end();
            pc_hash = &GUILayersHash;
            break;
    }


    while ( it != it_end ) {
        if ( ( *it ) == layer ) {
            pc_hash->erase ( it );

            insertLayer ( layer, new_type );
            return;
        }
        it++;
    }
}

void BEditorCameraComponent::onLayerNameChaned ( BackGenEngine::BLayer *layer, BoxE::Core::BAsciiString new_name  ) {
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::Iterator it = NormalLayersHash.begin();
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::Iterator it_end = NormalLayersHash.end();
    BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >* pc_hash;

    switch ( layer->getLayerType() ) {
        case BackGenEngine::BLayer::NORMAL:
            pc_hash = &NormalLayersHash;
            break;

        case BackGenEngine::BLayer::TRANSPARENT:
            it = TransparentLayersHash.begin();
            it_end = TransparentLayersHash.end();
            pc_hash = &TransparentLayersHash;
            break;

        case BackGenEngine::BLayer::GUI:
            it = GUILayersHash.begin();
            it_end = GUILayersHash.end();
            pc_hash = &GUILayersHash;
            break;
    }


    while ( it != it_end ) {
        if ( ( *it ) == layer ) {
            pc_hash->erase ( it );
            pc_hash->insert ( new_name, layer );
            return;
        }
        it++;
    }
}
/// new code
void BEditorCameraComponent::updateFrustrum() {
    ViewFrustrum.fromMatrix ( PerspectiveMatrix * ModelViewMatrix );
}

void BEditorCameraComponent::updateMatrix() {
    if ( !pcTexture ) {
        return;
    }

    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();
    ModelViewMatrix.setLookAt ( pc_transform->position(), pc_transform->position() + Dir, BoxE::Math::BVector3f ( 0.0f, 1.0f, 0.0f ) );

    PerspectiveMatrix.setPerspective ( 45.0f, ( float ) pcTexture->width() / ( float ) pcTexture->height(), 0.01f, 1000.0f );

    updateFrustrum();
}
