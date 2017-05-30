//
//  DynamicAnalyser.cpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-29.
//
//

#include "DynamicAnalyser.h"


using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    int DynamicAnalyser::COUNT = 0;
    
    DynamicAnalyser::DynamicAnalyser( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModulePiano(name+" "+ tools.to_roman(DynamicAnalyser::COUNT), origin, size, 1, 0){
        this->mMainWinCtx = mMainWinCtx;
    }
    
    void DynamicAnalyser::setup(){
        ModulePiano::setupUI();
        setupUI();
    }
    
    
    void DynamicAnalyser::update(){
        
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModulePiano::update();
        
        if(!inputs['A']){
            return;
        };
        
        
        if(inputs['A']->length!=0){
            auto it = inputs['A']->notes.begin();
            auto end = inputs['A']->notes.end();
            int p = 0;
            float t = 0.f;
            float tm = 0.f;
            int c = 0;
            int cm = 0;
            for(; it != end ; it++){
                p += (*it)->num;
                t += (*it)->time();// * (*it)->norm; // => PLus une Note est aigue plus l'horloge bat vite
                tm += (*it)->time(true);// * (*it)->norm; // => PLus une Note est aigue plus l'horloge bat vite
                c += (*it)->playedCount;
                cm += (*it)->playedCountMem;
            }
            oldPosition = positionRate;
            positionRate = (float)p / (float)inputs['A']->length;
            timeRate = fract(t);
            timeMemRate = fract(tm);
            countRate = c % 10;
            countMemRate = cm % 10;
            
            if(t != 0){
                speedRate = max(0.0f, min((float)cm / (float)tm, (float)Config::MAX_SINGLE_NOTE_SPEED));
            }
            if(oldInputID != inputs['A']->ID){
                oldInputID = inputs['A']->ID;
                distRate = abs(positionRate - oldPosition);
            }
        }
        
        position += (positionRate - position) * inertie;
        time += (timeRate - time) * inertie;
        timeMem += (timeMemRate - timeMem) * inertie;
        count += (countRate - count) * inertie;
        countMem += (countMemRate - countMem) * inertie;
        speed += (speedRate - speed) * inertie;
        dist += (distRate - dist) * inertie;
        
    }
    
    void DynamicAnalyser::setupUI(){
        mUi->setColorBack(ColorAT<float>(vec4(.1f, .2f, .3f, .4f)));
        //mUi->setColorFill(ColorAT<float>(vec4(.8f, .9f, 1.f, .6f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        ModulePiano::setupUI();
        setupInput();
        setupOutput();
        
        tools.addSlider(mUi, "INERTIE", &inertie, 0, 1);
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "Position", &position, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "Dist", &dist, 0, Config::NOTE_LEN);
        
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "Count", &count, 0, 10);
        tools.addSlider(mUi, "Count Mem", &countMem, 0, 10);
        
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "Time", &time, 0, 1);
        tools.addSlider(mUi, "Time Mem", &timeMem, 0, 1);
        
        mUi->addSpacer(false);
        mUi->addSpacer(false);
        
        tools.addSlider(mUi, "Speed", &speed, 0, Config::MAX_SINGLE_NOTE_SPEED);
        
        mUi->setMinified(false);
    }
};