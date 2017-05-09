//
//  orage.cpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-15.
//
//

#include "Orage.h"

using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;

Orage::Orage(string name, /*AppCocoaView * parent, */gl::Context * mMainWinCtx){
    //this->parent = parent;
    this->mMainWinCtx = mMainWinCtx;
}

OscillatorRef Orage::addOscillator(vec2 origin){
    OscillatorRef ref = Oscillator::create("Oscillator", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

TileRef Orage::addTile(vec2 origin){
    TileRef ref = Tile::create("Tile", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

MosherRef Orage::addMosher(vec2 origin){
    MosherRef ref = Mosher::create("Mosher", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
MatteRef Orage::addMatte(vec2 origin){
    MatteRef ref = Matte::create("Matte", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
SpliterRef Orage::addSpliter(vec2 origin){
    SpliterRef ref = Spliter::create("Spliter", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
CrossfaderRef Orage::addCrossfader(vec2 origin){
    CrossfaderRef ref = Crossfader::create("Crossfader", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
ColorAdjustementRef Orage::addColorAdjustement(vec2 origin){
    ColorAdjustementRef ref = ColorAdjustement::create("BriSatCon", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
InvertRef Orage::addInvert(vec2 origin){
    InvertRef ref = Invert::create("Invert", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
CloudRef Orage::addCloud(vec2 origin){
    CloudRef ref = Cloud::create("Cloud", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

LfosRef Orage::addLfos(vec2 origin){
    LfosRef ref = Lfos::create("LFOS", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
FftRef Orage::addFft(vec2 origin){
    FftRef ref = Fft::create("FFT", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
/*




KeyMixerRef Orage::addKeyMixer(vec2 origin){
    KeyMixerRef ref = KeyMixer::create("KeyMixer", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}


CellNoiseRef Orage::addCellNoise(vec2 origin){
    CellNoiseRef ref = CellNoise::create("CellNoise", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

TrailRef Orage::addTrail(vec2 origin){
    TrailRef ref = Trail::create("Trail", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

*/

PianoInputRef Orage::addPianoInput(vec2 origin){
    if(!PianoInput::singleton){
        PianoInputRef ref = PianoInput::create("Piano In", origin, mMainWinCtx);
        ref->setup();
        modules.push_back(ref);
    }
    return PianoInput::singleton;
}

HandSplitterRef Orage::addHandSplitter(vec2 origin){
    HandSplitterRef ref = HandSplitter::create("Hand Splitter", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
PositionExtractorRef Orage::addPositionExtractor(vec2 origin){
    PositionExtractorRef ref = PositionExtractor::create("Position Extractor", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
NoteDisplayRef Orage::addNoteDisplayKeyboard(vec2 origin){
    NoteDisplayRef ref = NoteDisplay::create<Config::NOTE_LEN>("Note Keyboard", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}


NoteDisplayRef Orage::addNoteDisplayOctave(vec2 origin){
    NoteDisplayRef ref = NoteDisplay::create<Config::OCTAVE_LEN>("Note Octave", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}


void Orage::setup(){
    addPianoInput(vec2(0, 0));
    addHandSplitter(vec2(0, 200));
    addPositionExtractor(vec2(300, 0));
    addNoteDisplayKeyboard(vec2(600, 0));
    addNoteDisplayOctave(vec2(900, 0));
    addOscillator(vec2(1200, 0));
     addTile(vec2(1500, 0));
   // addOscillator(vec2(200, 0));
}

void Orage::update(){
    auto it = modules.begin();
    for(; it != modules.end() ; ){
        if((*it)->shouldDestroy){
            (*it).reset();
            it = modules.erase(it);
        }else{
            (*it)->update();
            it ++;
        }
    }
}


void Orage::draw(){
    if(debug){
        //gl::draw(debug, Area(0, 0, 100, 100));
    }
    
    auto it = modules.begin();
    auto end = modules.end();
    for(; it != end ; it ++){
        (*it)->mUi->update();
        (*it)->mUi->draw();
    }
}