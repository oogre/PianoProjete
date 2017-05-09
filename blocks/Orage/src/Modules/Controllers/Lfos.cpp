//
//  Lfos.cpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-22.
//
//

#include "Lfos.h"

using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    int Lfos::COUNT = 0;
    Lfos::Lfos( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModuleCommon(name+" "+ tools.to_roman(Lfos::COUNT), origin, size){
        this->mMainWinCtx = mMainWinCtx;
        
        
    }
    
    void Lfos::setup(){
        ModuleCommon::setup();
        setupUI();
        
    }
    
    void Lfos::update(){
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModuleCommon::update();
        float timer = getElapsedSeconds() * (30)  * 0.0166667f; //SEC * (BEAT/MIN) * 1 / 60
        

            if(!lfoDatas.active)return;
            float value = timer + (lfoDatas.delay * 0.1f);
            value *= lfoDatas.clk_multi / lfoDatas.clk_div;
            value = value - (long) value;
            float exp = 1.0f;
            if(lfoDatas.exp >= 5){
                exp = 1.0f / (lfoDatas.exp - 4.0f);
            }else{
                exp = abs(6.0f - lfoDatas.exp);
            }
            value = pow(value, exp);
            if(lfoDatas.reverse){
                value = 1.0f - value;
            }
            
            
            lfoDatas.saw = value;
            lfoDatas.sine = cos(value* 6.28);
            lfoDatas.rect = value>.5;
    }
    
    void Lfos::setupUI(){
        ModuleCommon::setupUI();
        mUi->setColorBack(ColorAT<float>(vec4(.1f, .2f, .3f, .4f)));
        //mUi->setColorFill(ColorAT<float>(vec4(.8f, .9f, 1.f, .6f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        string id = toString(COUNT);
        CanvasRef v = Canvas::create("LFO"+id, ci::app::getWindow());
        mUi->addSubViewDown(Toggle::create("active "+id, &(lfoDatas.active), Button::Format().label(true)));
        mUi->addSubViewEastOf(Toggle::create("reverse "+id, &(lfoDatas.reverse), Button::Format().label(true)), "active "+id);
        
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "delay "+id, &(lfoDatas.delay), 0, 10);
        tools.addSlider(mUi, "multi "+id, &(lfoDatas.clk_multi), 1, 20);
        tools.addSlider(mUi, "div "+id, &(lfoDatas.clk_div), 1, 20);
        tools.addSlider(mUi, "exp "+id, &(lfoDatas.exp), 1, 9);
            
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "saw "+id, &(lfoDatas.saw), 0, 1);
        tools.addSlider(mUi, "sine "+id, &(lfoDatas.sine), -1, 1);
        tools.addSlider(mUi, "rect "+id, &(lfoDatas.rect), 0, 1);
        
        mUi->setMinified(false);
    }
    
    
    
    
}