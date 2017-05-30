//
//  Output.cpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-19.
//
//

#include "Output.h"
#include "cinder/app/App.h"

using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace ci::app;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    int Output::COUNT = 0;
    int Output::winOutCOUNT = 0;
    
    Output::Output( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModuleVideo(name+" "+ tools.to_roman(Output::COUNT), origin, size, 1, 1, true){
        this->mMainWinCtx = mMainWinCtx;
    }
    
    void Output::setup(){
        ModuleVideo::setup();
        mFbo = gl::Fbo::create(FBO_WIDTH,
                               FBO_HEIGHT,
                               gl::Fbo::Format()
                               .attachment(GL_COLOR_ATTACHMENT0,
                                           gl::Texture2d::create(FBO_WIDTH,
                                                                 FBO_HEIGHT)));
        //glDel
        //GLuint depthTextureId = mFbo->getDepthTexture()->getId();

        outputs['A'] = mFbo->getTexture2d( GL_COLOR_ATTACHMENT0 );
        setupShader();
        setupUI();
    }
    
    void Output::update(){
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModuleVideo::update();
        
        gl::pushMatrices();
        gl::ScopedViewport scpVp( ivec2( 0 ), mFbo->getSize() );
        gl::setMatrices( ModuleVideo::CAM );
        mFbo->bindFramebuffer();
        {
            gl::clear( ColorA(0, 0, 0, 0));
            gl::color(ColorA(1, 1, 1, 1));
            if(inputs['A']){
                gl::draw(inputs['A']);
            }
        }
        mFbo->unbindFramebuffer();
        
        gl::popMatrices();
    }
    
    void Output::setupUI(){
        
        ModuleVideo::setupUI();
        mUi->setColorBack(ColorAT<float>(vec4(.8f, .4f, .1f, .4f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        mUi->addButton("New Window", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 createOutputWindow();
                                                             }
                                                         });
        mUi->setMinified(false);
    }
    
    void Output::setupShader(){
        ModuleVideo::setupShader();
    }
    void Output::createOutputWindow(){
        string name = "output "+toString(winOutCOUNT++);
        windowCanvas[name] = WindowCanvas::create(name);
        app::WindowRef window = windowCanvas[name]->getWindow();
        mMainWinCtx->makeCurrent();
        window->getSignalClose().connect( [this, window] {
            windowCanvas.erase(window->getTitle());
        });
        window->getSignalDraw().connect( [this, window] {
            gl::draw(outputs['A'], Rectf(vec2(0, 0), window->getSize()));
        });
    }
}