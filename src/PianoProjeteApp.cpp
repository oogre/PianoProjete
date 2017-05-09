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
    gl::Context   * mMainWinCtx;
  public:
    static void prepareSettings( Settings *settings );
    void setup() override;
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    
    void keyUp( KeyEvent event) override;
};

void PianoProjeteApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 800, 600 );
    settings->setWindowPos(0, 0);
   // settings->setFullScreen(true, FullScreenOptions().display(FullScreenOptions().getDisplay()));
}

void PianoProjeteApp::setup()
{
    gl::clear(ColorAT<float>(0, 0, 0, 0));
    orage = Orage::create("Piano Projeté", gl::Context::getCurrent());
}

void PianoProjeteApp::update()
{
    orage->update();
}

void PianoProjeteApp::draw()
{
    gl::clear(ColorAT<float>(0, 0, 0, 0));
    orage->draw();
    wires.draw(mMouseLoc);
}

void PianoProjeteApp::mouseMove( MouseEvent event ) {
    mMouseLoc = event.getPos();
}
void PianoProjeteApp::mouseDown( MouseEvent event ) {
    if(event.isRightDown()){
        orage->contextMenu->setOrigin(event.getPos());
        orage->contextMenu->setVisible(true);
    }else{
        if(orage->contextMenu->isVisible()){
            orage->contextMenu->setVisible(false);
        }
    }
}


void PianoProjeteApp::keyUp( KeyEvent event){
    wires.keyUp(event);
}

CINDER_APP( PianoProjeteApp, RendererGl, &PianoProjeteApp::prepareSettings )
