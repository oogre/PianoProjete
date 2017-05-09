//
//  PositionExtractor.cpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-07.
//
//

#include "PositionExtractor.h"



using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    int PositionExtractor::COUNT = 0;
    
    PositionExtractor::PositionExtractor( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModulePiano(name+" "+ tools.to_roman(PositionExtractor::COUNT), origin, size, 1, 0){
        this->mMainWinCtx = mMainWinCtx;
    }
    
    void PositionExtractor::setup(){
        ModulePiano::setupUI();
        setupUI();
    }
    
    
    void PositionExtractor::update(){
        
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModulePiano::update();
        
        if(!inputs['A']) return;
        
        //bitset<88> _max = bitsetTools.maximum(&(inputs['A']->ID));
        //bitset<88> _min = bitsetTools.minimum(&(inputs['A']->ID));
        boost::dynamic_bitset<> a = bitsetTools.average(&(inputs['A']->ID));
        //cout<<<<endl;
        
        averageRate = bitsetTools.normalize(&a);
        minRate = bitsetTools.min(&(inputs['A']->ID));
        maxRate = bitsetTools.max(&(inputs['A']->ID));
        middleRate = (minRate + maxRate) * 0.5;
        //diffRate = (averageRate - middleRate) * 4;
        
        countRate = (float)inputs['A']->length/(float)Config::NOTE_LEN;
        countOctaveRate = (float)inputs['A']->lengthOneOctave/(float)Config::OCTAVE_LEN;
        
        average += (averageRate - average)*0.1f;
        min += (minRate - min)*0.1f;
        max += (maxRate - max)*0.1f;
        middle += (middleRate - middle)*0.1f;
        //diff += (diffRate - diff)*0.1f;
        count += (countRate - count)*0.1f;
        countOctave += (countOctaveRate - countOctave)*0.1f;
    }
    
    void PositionExtractor::setupUI(){
        mUi->setColorBack(ColorAT<float>(vec4(.1f, .2f, .3f, .4f)));
        //mUi->setColorFill(ColorAT<float>(vec4(.8f, .9f, 1.f, .6f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        ModulePiano::setupUI();
        setupInput();
        setupOutput();
        
        tools.addSlider(mUi, "count", &count, 0, 1);
        tools.addSlider(mUi, "countOctave", &countOctave, 0, 1);
        tools.addSlider(mUi, "min", &min, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "average", &average, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "middle", &middle, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "max", &max, 0, Config::NOTE_LEN);
        tools.addSlider(mUi, "diff", &diff, -1, 1);
        
        mUi->setMinified(true);
    }
};