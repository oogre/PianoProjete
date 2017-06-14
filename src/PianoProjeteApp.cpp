#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Orage.h"
#include "UI.h"


using namespace ci;
using namespace ci::app;
using namespace std;
using namespace ogre;

class PianoProjeteApp : public App {
    OrageRef        orage;
    double          lastclick = 0.0;
    ivec2           mMouseLoc;
    Rectf           mMouseSelector;
    bool            mMouseDrag = false;
    gl::Context   * mMainWinCtx;
  public:
    static void prepareSettings( Settings *settings );
    void setup() override;
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void update() override;
    void draw() override;
    
    void keyUp( KeyEvent event) override;
};

void PianoProjeteApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1920, 1200 );
    //settings->setWindowPos(0, 0);
   // settings->setFullScreen(true, FullScreenOptions().display(FullScreenOptions().getDisplay()));
}

void PianoProjeteApp::setup()
{
    mMainWinCtx = gl::Context::getCurrent();
    gl::clear(ColorAT<float>(0, 0, 0, 0));
    orage = Orage::create("Piano Projeté", mMainWinCtx);
}

void PianoProjeteApp::update()
{
    
}

void PianoProjeteApp::draw()
{
    if(mMainWinCtx != gl::Context::getCurrent()){
        return;
    }

    gl::clear(ColorAT<float>(0, 0, 0, 0));
    orage->update();
    orage->draw(mMouseDrag, mMouseSelector);
    wires.draw(mMouseLoc);
}

void PianoProjeteApp::mouseMove( MouseEvent event ) {
    if(mMainWinCtx != gl::Context::getCurrent()){
        return;
    }
    mMouseLoc = event.getPos();
}
void PianoProjeteApp::mouseDown( MouseEvent event ) {
    if(mMainWinCtx != gl::Context::getCurrent()){
        if(getElapsedSeconds()  - lastclick < 0.2){
            setFullScreen(!isFullScreen());
        }
        lastclick = getElapsedSeconds();
        return;
    }
    /*
    ModuleRef clicked = orage->isOnModule(event.getPos());
    if(clicked){
        mMouseDrag = false;
        if(event.isRightDown()){
            orage->openGroupMenu(event.getPos());
        }else{

        }
    }
    else{*/
        if(event.isRightDown()){
            orage->openContextMenu(event.getPos());
            //orage->resetSelectModule();
            mMouseDrag = false;
        }else{
            //mMouseDrag = true;
            mMouseSelector.y1 = mMouseSelector.y2 = event.getY();
            mMouseSelector.x1 = mMouseSelector.x2 = event.getX();
        }
    //}
    
    if(event.isLeftDown()){
        orage->closeContextMenu();
        //orage->closeGroupMenu();
    }
}
void PianoProjeteApp::mouseUp( MouseEvent event ) {
    if(mMainWinCtx != gl::Context::getCurrent()){
        return;
    }
    if(mMouseDrag){
        //orage->selectModuleByArea(mMouseSelector);
    }
    mMouseDrag = false;
};

void PianoProjeteApp::mouseDrag( MouseEvent event ) {
    if(mMainWinCtx != gl::Context::getCurrent()){
        return;
    }
    mMouseSelector.y2 = event.getY();
    mMouseSelector.x2 = event.getX();
};

void PianoProjeteApp::keyUp( KeyEvent event){
    if(mMainWinCtx != gl::Context::getCurrent()){
        return;
    }
    wires.keyUp(event);
}

CINDER_APP( PianoProjeteApp, RendererGl, &PianoProjeteApp::prepareSettings )
