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
    contextMenu = SuperCanvas::create("context menu");
    contextMenu->setSize(vec2(ModuleCommon::WIDTH, 300));
    contextMenu->addButton("Matte", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addMatte(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addButton("OSCILLATOR", false)->setCallback(
                                                             [this](bool a) {
                                                                 if(a){
                                                                     addOscillator(contextMenu->getOrigin());
                                                                 }
                                                             });
    contextMenu->addButton("Cloud", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addCloud(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addSpacer(false);
    
    contextMenu->addButton("Mosher", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addMosher(contextMenu->getOrigin());
                                                             }
                                                         });
    
    contextMenu->addButton("Splitter", false)->setCallback(
                                                           [this](bool a) {
                                                               if(a){
                                                                   addSpliter(contextMenu->getOrigin());
                                                               }
                                                           });
    
    contextMenu->addButton("Crossfader", false)->setCallback(
                                                             [this](bool a) {
                                                                 if(a){
                                                                     addCrossfader(contextMenu->getOrigin());
                                                                 }
                                                             });
    
    contextMenu->addSpacer(false);
    
    contextMenu->addButton("Tile", false)->setCallback(
                                                       [this](bool a) {
                                                           if(a){
                                                               addTile(contextMenu->getOrigin());
                                                           }
                                                       });
    contextMenu->addButton("Color Adjustement", false)->setCallback(
                                                                    [this](bool a) {
                                                                        if(a){
                                                                            addColorAdjustement(contextMenu->getOrigin());
                                                                        }
                                                                    });

    contextMenu->addButton("Invert", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addInvert(contextMenu->getOrigin());
                                                             }
                                                         });

    contextMenu->addSpacer();
    
    contextMenu->addButton("LFO", false)->setCallback(
                                                      [this](bool a) {
                                                          if(a){
                                                              addLfos(contextMenu->getOrigin());
                                                          }
                                                      });
    contextMenu->addButton("FFT", false)->setCallback(
                                                      [this](bool a) {
                                                          if(a){
                                                              addFft(contextMenu->getOrigin());
                                                          }
                                                      });
    
    contextMenu->addSpacer();
    
    contextMenu->addButton("Piano In", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addPianoInput(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addButton("Piano Splitter", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addHandSplitter(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addButton("Data extractor", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addPositionExtractor(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addButton("Display Note", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addNoteDisplayKeyboard(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->addButton("Display Octave", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addNoteDisplayOctave(contextMenu->getOrigin());
                                                            }
                                                        });
    contextMenu->setVisible(false);
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
    contextMenu->update();
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
    contextMenu->draw();
}