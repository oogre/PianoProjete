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
    void update() override;
    void draw() override;
    
    void keyUp( KeyEvent event) override;
    
    void addOscillator();
    void addTile();
    //void addSyphonInput();
    void addMosher();
    void addMatte();
    void addFft();
    void addSpliter();
    void addCrossfader();
    void addLfos();
    void addKeyMixer();
    void addColorAdjustement();
    void addInvert();
    void addCellNoise();
    void addCloud();
    //void addOutput();
    void addTrail();

};

void PianoProjeteApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1920, 1440 );
    //settings->setFullScreen( true );
    //settings->setBorderless();
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

void PianoProjeteApp::keyUp( KeyEvent event){
    wires.keyUp(event);
}

void PianoProjeteApp::addOscillator(){
    orage->addOscillator(vec2(0, 0));
}

void PianoProjeteApp::addTile(){
    orage->addTile(vec2(0, 0));
}

void PianoProjeteApp::addMosher(){
    orage->addMosher(vec2(0, 0));
}

void PianoProjeteApp::addMatte(){
    orage->addMatte(vec2(0, 0));
}

void PianoProjeteApp::addSpliter(){
    orage->addSpliter(vec2(0, 0));
}
void PianoProjeteApp::addFft(){
    orage->addFft(vec2(0, 0));
}

void PianoProjeteApp::addCrossfader(){
    orage->addCrossfader(vec2(0, 0));
}

void PianoProjeteApp::addLfos(){
    orage->addLfos(vec2(0, 0));
}

void PianoProjeteApp::addKeyMixer(){
    //orage->addKeyMixer(vec2(0, 0));
}

void PianoProjeteApp::addColorAdjustement(){
    orage->addColorAdjustement(vec2(0, 0));
}

void PianoProjeteApp::addInvert(){
    orage->addInvert(vec2(0, 0));
}

void PianoProjeteApp::addCellNoise(){
    //orage->addCellNoise(vec2(0, 0));
}

void PianoProjeteApp::addCloud(){
    orage->addCloud(vec2(0, 0));
}

void PianoProjeteApp::addTrail(){
    // orage->addTrail(vec2(0, 0));
}


CINDER_APP( PianoProjeteApp, RendererGl, &PianoProjeteApp::prepareSettings )
