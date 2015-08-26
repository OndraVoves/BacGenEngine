
#include <cstdio>
#include <iostream>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <BoxECore/BoxECore>
#include <BoxECore/BoxECore>

#include <BackGenEngine/blogger.h>
#include <BackGenEngine/bbuttonaction.h>
#include <BackGenEngine/bactionmanager.h>
#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bproject.h>
#include <BackGenEngine/btag.h>
#include <BackGenEngine/btagsmanager.h>
#include <BackGenEngine/blayer.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/blayer.h>
#include <BackGenEngine/blayersmanager.h>
#include <BackGenEngine/bdynamicmodulesystem.h>
#include <BackGenEngine/bvertexbuffer.h>

#include <BoxECore/bvariant.h>
#include <BoxECore/bsettings.h>

#include "../../modules/renderer/opengl/bopengltexture.h"
#include "../../modules/renderer/opengl/bopenglrenderer.h"
#include "../../modules/renderer/opengl/bopenglframebuffer.h"
#include "../../modules/component/transformation/BTransformationComponent.h"
#include "../../modules/component/meshrenderer/BMeshRendererComponent.h"
#include "../../modules/asset/image/BImageAsset.h"
#include "../../modules/asset/texture/BTextureAsset.h"
#include "../../modules/asset/material/BMaterialAsset.h"

#include "bsdlwindow.h"
#include <BackGenEngine/babstractasset.h>

#include <BackGenEngine/babstractcameracomponent.h>

#include <BackGenEngine/brenderablecomponent.h>

#include <dirent.h>
#include <stdio.h>

class BBaseCameraComponent : public BackGenEngine::BAbstractCameraComponent {
    public:
        BBaseCameraComponent ( BackGenEngine::BScene *pc_scene ) : BAbstractCameraComponent ( pc_scene ), pcFBO ( 0 ), pcTexture ( 0 ) {
            BackGenEngine::BAbstractRenderer *pc_renderer = getScene()->getRenderer();

            pcFBO =  pc_renderer->createFramebuffer();
        }

        virtual ~BBaseCameraComponent() {
        }

        virtual BAbstractComponent *duplicate() const {
            return 0;
        }

        bool resize ( int width, int height ) {
            if ( pcTexture ) {
                delete pcTexture;
            }

            pcTexture = getScene()->getRenderer()->createTexture ( width, height, false, BOpenGLTexture::FT_BILINEAR, BOpenGLTexture::TF_RGBA8, BOpenGLTexture::TF_RGBA, 0  );

            pcFBO->attachColor0Texture ( pcTexture );

            //OrthoMatrix.setOrthographic ( 0, width, 0, height, 0.0f, 1.0f );
            OrthoMatrix.setPerspective ( 45.0f, 800.0f / 600.0f, 0.01, 100.0f  );
        }

        virtual void render( ) {
            pcFBO->begin();
            getScene()->getRenderer()->beginRender ( true, true, BoxE::Math::BVector3f ( 1.0f, 0.0f, 0.0f ) );
            renderNormalLayers();
            renderTransparentlLayers();
            renderGUILayers();
            getScene()->getRenderer()->endRender( );
            pcFBO->end();
        }

        virtual BackGenEngine::BAbstractTexture *getOutputTexture() {
            return pcTexture;
        }

    protected:
        void renderObject ( BackGenEngine::BObject *pc_object )  {
            BackGenEngine::BRenderableComponent *pc_component = pc_object->getComponent<BackGenEngine::BRenderableComponent>();
            if ( pc_component ) {
                pc_component->render();
            }
        }

        void renderLayer ( BackGenEngine::BLayer *pc_layer ) {
            BackGenEngine::BLayer::bobject_hash_t::ConstIterator it = pc_layer->constBegin();
            while ( it != pc_layer->constEnd() ) {
                renderObject ( ( *it ) );
                ++it;
            }
        }

        void renderNormalLayers( ) {
            BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = NormalLayersHash.constBegin();

            while ( it != NormalLayersHash.constEnd() ) {
                renderLayer ( ( *it ) );
                ++it;
            }

        }


        void renderTransparentlLayers( ) {
            BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = TransparentLayersHash.constBegin();

            while ( it != TransparentLayersHash.constEnd() ) {
                renderLayer ( ( *it ) );
                ++it;
            }
        }

        void renderGUILayers( ) {
            getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_PROJECTION );
            getScene()->getRenderer()->setMatrix ( BOpenGLRenderer::MT_PROJECTION, OrthoMatrix );

            BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * >::ConstIterator it = GUILayersHash.constBegin();
            while ( it != GUILayersHash.constEnd() ) {
                renderLayer ( ( *it ) );
                ++it;
            }
            getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_PROJECTION  );
        }

    public:
        bool insertLayer ( BackGenEngine::BLayer *pc_layer ) {
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
        }
    private:
        BackGenEngine::BAbstractFrameBuffer *pcFBO;
        BackGenEngine::BAbstractTexture *pcTexture;

        BoxE::Math::BMatrix4x4f OrthoMatrix;

        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > NormalLayersHash;
        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > TransparentLayersHash;
        BoxE::Core::BHash< BoxE::Core::BAsciiString, BackGenEngine::BLayer * > GUILayersHash;

};

class PokusRenderComponent : public BackGenEngine::BRenderableComponent {
    public:
        PokusRenderComponent ( BackGenEngine::BScene *pc_scene ) : BRenderableComponent ( pc_scene ), VertexBuffer ( 4 ) {
            VertexBuffer[0].getPosition() = BoxE::Math::BVector3f ( 0.0f, 0.0f, -2.0f );
            VertexBuffer[0].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f );

            VertexBuffer[1].getPosition() = BoxE::Math::BVector3f ( 1.0f, 0.0f, -2.0f );
            VertexBuffer[1].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f );

            VertexBuffer[2].getPosition() = BoxE::Math::BVector3f ( 1.0f, 1.0f, -2.0f );
            VertexBuffer[2].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f );

            VertexBuffer[3].getPosition() = BoxE::Math::BVector3f ( 0.0f, 1.0f, -2.0f );
            VertexBuffer[2].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f );

            aIndexBuffer = new int[4];
            aIndexBuffer[ 0 ] = 0;
            aIndexBuffer[ 1 ] = 1;
            aIndexBuffer[ 2 ] = 2;
            aIndexBuffer[ 3 ] = 3;
        }

        virtual ~PokusRenderComponent() {
        }

        virtual void render() {
            BoxE::Math::BMatrix4x4f mat ( BoxE::Math::BMatrix4x4f::IDENTITY ) ;
            mat.scale ( BoxE::Math::BVector3f ( 0.5f, 0.5f, 0.5f ) );
            glActiveTexture ( GL_TEXTURE0 );
            glColor3f ( 0.0f, 1.0f, 0.0f );
            glBindTexture ( GL_TEXTURE_2D, 0 );
            getScene()->getRenderer()->renderVB ( BOpenGLRenderer::PT_QUADS, VertexBuffer, aIndexBuffer, 1 );

            glColor3f ( 1.0f, 1.0f, 1.0f );
            getScene()->getRenderer()->pushMatrix ( BOpenGLRenderer::MT_WORLD );
            getScene()->getRenderer()->setMatrix ( BOpenGLRenderer::MT_WORLD, mat );
            glBindTexture ( GL_TEXTURE_2D, 1 );
            getScene()->getRenderer()->renderVB ( BOpenGLRenderer::PT_QUADS, VertexBuffer, aIndexBuffer, 1 );
            getScene()->getRenderer()->popMatrix ( BOpenGLRenderer::MT_WORLD );
            /*glBegin ( GL_TRIANGLES );
            glColor3f ( 1.0f, 1.0f, 0.0f );
            glVertex2i ( 0, 0 );
            glVertex2i ( 100, 0.00 );
            glVertex2i ( 100, 100 );

            glColor3f ( 0.0f, 1.0f, 1.0f );
            glVertex2i ( 100, 100 );
            glVertex2i ( 300, 100.00 );
            glVertex2i ( 300, 300 );

            glEnd();*/
        }

    private:
        BackGenEngine::BVertexBuffer VertexBuffer;
        int *aIndexBuffer;
};

void on_key_down ( BackGenEngine::BAbstractWindow::key_t key ) {
    std::cout << "key: " << key << std::endl;
}

void mouse ( int x, int y ) {
    std::cout << "mouse:  " << x << ", " << y << std::endl;
}

void mouse2 ( int x, int y ) {
    std::cout << "mouse2:  " << x << ", " << y << std::endl;
}

int main (  int argc , char **argv ) {
#if 0
    BackGenEngine::BLogger logger;
    BackGenEngine::BDynamicModuleSystem dm ( &logger );

    dm.loadModule ( "../../modules/asset/image/BImageAsset" );

#endif

#if 0
    DIR *dh;//directory handle
    struct dirent *file;//a 'directory entity' AKA file
    dh = opendir ( "./" );
    while ( file = readdir ( dh ) ) {
        printf ( "%s\n", file->d_name );
    }

    return 0;
#endif

#if 0
    BoxE::Core::BSettings s;
    s.setValue ( "a", 'a' );

    std::cout << "a: " << s.value ( "a" ).value<char>();

#endif

    BoxE::Math::BMatrix4x4f m1;
    m1.setToIdentity();
    m1.rotateX ( 90 );

    BoxE::Math::BMatrix4x4f m2 ( m1.getInverse() );

    BoxE::Math::BMatrix4x4f m3 ( m1 * m2 );


#if 0
    BackGenEngine::BLogger logger;
    BackGenEngine::BActionManager actionm;
    BackGenEngine::BDynamicModuleSystem mod_sys ( &logger );

    mod_sys.loadModule ( "../../modules/component/transformation/BTransformationComponent" );
    mod_sys.loadModule ( "../../modules/component/meshrenderer/BMeshRendererComponent" );
    mod_sys.loadModule ( "../../modules/component/cubemesh/BCubeMesh" );
    mod_sys.loadModule ( "../../modules/asset/image/BImageAsset" );
    mod_sys.loadModule ( "../../modules/asset/texture/BTextureAsset" );
    mod_sys.loadModule ( "../../modules/asset/material/BMaterialAsset" );
    mod_sys.loadModule ( "../../modules/asset_loader/image_tga/TGAloader" );
    mod_sys.loadModule ( "../../modules/asset_loader/texture/Textureloader" );
    mod_sys.loadModule ( "../../modules/asset_saver/texture/TextureSaver" );

    BSDLWindow window ( "pokus", BackGenEngine::BAbstractWindow::screen_resolution_t ( 800, 600, 0 ), 32, false, &logger );
    window.init();
    window.show();

    BOpenGLRenderer renderer ( &logger );
    renderer.init();
    renderer.onScreenChanged ( BoxE::Math::BVector3f ( 800, 600 , 0 ), false );


    BackGenEngine::BProject project ( 0, &mod_sys, &logger );
    project.setBaseDir ( "/home/backgen/pokusgame/" );

    BackGenEngine::BScene scene ( &renderer, &logger );

    BackGenEngine::BLayer *pc_layer = scene.getLayersManager().createLayer ( "vrstva1", BackGenEngine::BLayer::GUI );


    //mod_sys.loadModule ( "../../modules/component/transformation/BTransformationComponent" );
    //project.setName ( "Testing" );

    //window.show();

    BackGenEngine::BObject *pc_triangles = new BackGenEngine::BObject ( "Object1", 0 );
    BackGenEngine::BAbstractComponent *pc_transform = mod_sys.createComponent ( "Transformation", &scene );
    ( ( BTransformationComponent * ) pc_transform )->position().setXYZ ( 0.0f, 0.0f, -5.0f );
    BackGenEngine::BAbstractComponent *pc_cubemesh = mod_sys.createComponent ( "CubeMesh", &scene );
    BackGenEngine::BAbstractComponent *pc_meshrenderer = mod_sys.createComponent ( "MeshRenderer", &scene );

    pc_triangles->insertComponent ( pc_transform );
    pc_triangles->insertComponent ( pc_cubemesh );
    pc_triangles->insertComponent ( pc_meshrenderer );


    /*    PokusRenderComponent *pc_rendr_comp = new PokusRenderComponent (  &scene );
        pc_triangles->insertComponent ( pc_rendr_comp );*/
    pc_layer->insertObject ( pc_triangles );


    BackGenEngine::BButtonAction quitAction ( "Quit", BackGenEngine::BAbstractWindow::BK_ESCAPE, &window );
    actionm.insert ( &quitAction );

    BackGenEngine::BActionManager::actions_hash_t::ConstIterator iter = actionm.constBegin();


    /*    BoxE::Math::BMatrix4x4f ortho;
        ortho.setOrthographic ( 0, 800, 0, 600, 0.0f, 1.0f );

        renderer.pushMatrix ( BOpenGLRenderer::MT_PROJECTION );
        renderer.setMatrix ( BOpenGLRenderer::MT_PROJECTION, ortho );*/


    BackGenEngine::BObject *pc_camera_object = new BackGenEngine::BObject ( "Camera", 0 );
    BBaseCameraComponent *pc_camera_component = new BBaseCameraComponent ( &scene );
    pc_camera_component->resize ( 800, 600 );
    pc_camera_component->insertLayer ( pc_layer );


    /*    glViewport ( 0, 0, 800, 600 );
        glMatrixMode ( GL_PROJECTION );
        glLoadIdentity();
        glOrtho ( 0, 800, 0, 600, -1, 1 );*/

    BImageAsset *pc_image = ( BImageAsset * ) mod_sys.createAsset ( "Image", &project, &renderer, &project.getAssetManager(), &logger );
    pc_image->setName ( "image1" );
    pc_image->setPath ( "skin.tga" );
    pc_image->use();

    BTextureAsset *pc_texture = ( BTextureAsset * ) mod_sys.createAsset ( "Texture", &project, &renderer, &project.getAssetManager(), &logger  );
    pc_texture->setImage ( pc_image );
    pc_texture->setMipmaping ( true );
    //pc_texture->setPath( "texture1.texture" );

    BMaterialAsset *pc_material = ( BMaterialAsset * ) mod_sys.createAsset ( "Material", &project, &renderer, &project.getAssetManager(), &logger  );
    pc_material->setTextureUnit ( 0, pc_texture );

    ( ( BMeshRendererComponent * ) pc_meshrenderer )->setMaterialAsset ( pc_material );
    ( ( BMeshRendererComponent * ) pc_meshrenderer )->setTiling ( BoxE::Math::BVector2f ( 2.0f, 2.0f ) );


    float i = 0;
    BoxE::Math::BMatrix4x4f rot;
    while ( !window.update() && quitAction.isUp() ) {
        i += 1;
        ( ( BTransformationComponent * ) pc_transform )->rotation().y ( i );

        pc_camera_component->render();

        renderer.beginRender ( true, true, BoxE::Math::BVector3f ( 0.0f, 0.0f, 0.0f ) );
        renderer.drawSreenTexture ( pc_camera_component->getOutputTexture() );
        //renderer.drawSreenTexture ( pc_texture->getTexture() );
        renderer.endRender();

        SDL_GL_SwapBuffers( );

//      renderer.popMatrix ( BOpenGLRenderer::MT_PROJECTION );
//renderer.popMatrix ( BOpenGLRenderer::MT_WORLD );
    };
#endif
    //BoxE::Math::BMatrix4x4f matrix( BoxE::Math::BMatrix4x4f::IDENTITY );

#if 0

    BackGenEngine::BObject obj1 ( "obj1" );
    BackGenEngine::BObject obj2 ( "obj2", &obj1 );
    BackGenEngine::BObject obj3 ( "obj3" );
    BackGenEngine::BObject obj4 ( "obj4", &obj1 );

    BackGenEngine::BObject::objects_list_t::ConstIterator it = obj1.constObjectsBegin();
    while ( it != obj1.constObjectsEnd() ) {
        std::cout << ( *it )->name() << std::endl;
        ++it;
    }


    obj1.name ( "OBJ1" );

    BackGenEngine::BLayersManager lm;

    BackGenEngine::BLayer layer1 ( "layer", BackGenEngine::BLayer::NORMAL );
    layer1.insertObject ( &obj1 );



    BackGenEngine::BLayer *layer2 = lm.createLayer ( "layer1", BackGenEngine::BLayer::NORMAL );

    if ( lm.removeLayer ( "layer1" ) ) {
        std::cout << obj1.layer()->name() << std::endl;
    }

    BackGenEngine::BTagsManager tm;
    BackGenEngine::BTag *tag1 = tm.createTag ( "tag1" );
    BackGenEngine::BTag *tag2 = tm.createTag ( "tag1" );

    tm.removeTag ( tag1 );

    if ( tm.containTag ( "tag1" ) ) {
        std::cout << "obsahuje" << std::endl;
    }

#endif

#if 0
    BackGenEngine::BLogger logger;
    BackGenEngine::BActionManager actionm;
    BSDLWindow window ( "TestApp", BackGenEngine::BAbstractWindow::screen_resolution_t ( 800, 600, 0 ), 32, false, &logger );
    window.init();
    window.show();

    window.onKeyDown().connect ( &on_key_down );
    window.onMouseMotion().connect ( &mouse );

    BackGenEngine::BButtonAction quitAction ( "Quit", BackGenEngine::BAbstractWindow::BK_ESCAPE, &window );
    actionm.insert ( &quitAction );

    BackGenEngine::BActionManager::actions_hash_t::ConstIterator iter = actionm.constBegin();

    while ( !window.update() && quitAction.isUp() ) {
    };

#endif

#if 0
    BoxE::Core::BLibrary SDL ( "SDL" );
    if ( !SDL.load() ) {
        std::cout << "ERROR: " << SDL.errorString().constData() << std::endl;
    }

    void *a = SDL.resolv ( "SDL_Init" );
    if ( !a ) {
        std::cout << "ERROR: " << SDL.errorString().constData() << std::endl;
    }
    //void* a = BoxE::Core::BLibrary::resolve( "/usr/lib/libSDL.so", "SDL_Init" );
#endif

#if 0

    BoxE::Core::BFile out2;
    out2.setFilename ( "a.txt" );
//  out2.open(BoxE::Core::BIODevice::WriteOnly);

    BoxE::Core::BTextStream stream ( &out2 );

//  stream << "1";

    out2.close();
    out2.open ( BoxE::Core::BIODevice::ReadOnly );

    std::cout << stream.readAll().constData() << std::endl;

#endif

    return 0;
}


