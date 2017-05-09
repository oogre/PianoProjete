#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Orage.h"
#include "UI.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class PianoProjeteApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void PianoProjeteApp::setup()
{
}

void PianoProjeteApp::mouseDown( MouseEvent event )
{
}

void PianoProjeteApp::update()
{
}

void PianoProjeteApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( PianoProjeteApp, RendererGl )
