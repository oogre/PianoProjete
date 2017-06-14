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
    selectedModules = SuperModule::create();
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

CloudRef Orage::addCloud(vec2 origin){
    CloudRef ref = Cloud::create("Cloud", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}
OutputRef Orage::addOutput(vec2 origin){
    OutputRef ref = Output::create("Output", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

SyphonInputRef Orage::addSyphonInput(vec2 origin){
    SyphonInputRef ref = SyphonInput::create("Syphon", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

FreezerRef Orage::addFreezer(vec2 origin){
    FreezerRef ref = Freezer::create("Freezer", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

DelayRef Orage::addDelay(vec2 origin){
    DelayRef ref = Delay::create("Delay", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

ResizeRef Orage::addResize(vec2 origin){
    ResizeRef ref = Resize::create("Resize", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

BlurRef Orage::addBlur(vec2 origin){
    BlurRef ref = Blur::create("Blur", origin, mMainWinCtx);
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

DynamicAnalyserRef Orage::addDynamicAnalyser(vec2 origin){
    DynamicAnalyserRef ref = DynamicAnalyser::create("Dynamic Analyser", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}

LastNoteExtractorRef Orage::addLastNoteExtractor(vec2 origin){
    LastNoteExtractorRef ref = LastNoteExtractor::create("Note Hitory", origin, mMainWinCtx);
    ref->setup();
    modules.push_back(ref);
    return ref;
}




void Orage::setup(){
    /*
    groupMenu = SuperCanvas::create("group menu");
    groupMenu->setSize(vec2(ModuleCommon::WIDTH, 300));
    groupMenu->addButton("Group", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                
                                                                SuperModuleRef g = SuperModule::create();
                                                                g->modules = selectedModules->modules;
                                                                groupedModules.push_back(g);

                                                                selectedModules->clear([this](ModuleRef it) {
                                                                    it->selected = false;
                                                                });
                                                            }
                                                        });
    groupMenu->setVisible(false);
    */
    
    contextMenu = SuperCanvas::create("context menu");
    contextMenu->setSize(vec2(ModuleCommon::WIDTH, 300));
    
    contextMenu->addSpacer(false);
    contextMenu->addSpacer(false);

    
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
    contextMenu->addSpacer(false);
    
    contextMenu->addButton("Tile", false)->setCallback(
                                                       [this](bool a) {
                                                           if(a){
                                                               addTile(contextMenu->getOrigin());
                                                           }
                                                       });
    contextMenu->addButton("Freezer", false)->setCallback(
                                                          [this](bool a) {
                                                              if(a){
                                                                  addFreezer(contextMenu->getOrigin());
                                                              }
                                                          });

    contextMenu->addButton("Color Adjustement", false)->setCallback(
                                                                    [this](bool a) {
                                                                        if(a){
                                                                            addColorAdjustement(contextMenu->getOrigin());
                                                                        }
                                                                    });
    
    contextMenu->addButton("Delay", false)->setCallback(
                                                        [this](bool a) {
                                                            if(a){
                                                                addDelay(contextMenu->getOrigin());
                                                            }
                                                        });
    
    contextMenu->addButton("Resize", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addResize(contextMenu->getOrigin());
                                                             }
                                                         });
    
    contextMenu->addButton("Blur", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addBlur(contextMenu->getOrigin());
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
    contextMenu->addButton("Dynamic Analyser", false)->setCallback(
                                                                   [this](bool a) {
                                                                       if(a){
                                                                           addDynamicAnalyser(contextMenu->getOrigin());
                                                                       }
                                                                   });
    contextMenu->addButton("Note History", false)->setCallback(
                                                                   [this](bool a) {
                                                                       if(a){
                                                                           addLastNoteExtractor(contextMenu->getOrigin());
                                                                       }
                                                                   });
    
    contextMenu->addSpacer();
    
    contextMenu->addButton("Syphon", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addSyphonInput(contextMenu->getOrigin());
                                                             }
                                                         });
    contextMenu->addButton("Output", false)->setCallback(
                                                         [this](bool a) {
                                                             if(a){
                                                                 addOutput(contextMenu->getOrigin());
                                                             }
                                                         });
    
    
    contextMenu->setVisible(false);
    
    
    //addPianoInput(vec2(0, 0));

    addOutput(vec2(getWindowWidth() - ModuleCommon::WIDTH*2, getWindowHeight() - 305));
    
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
    /*
    selectedModules->update();
    
    auto it2 = groupedModules.begin();
    for(; it2 != groupedModules.end() ; it2 ++){
        (*it2)->update();
    }*/
    contextMenu->update();
    //groupMenu->update();
    
}


void Orage::draw(bool selectorActive, Rectf selector){
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
    //groupMenu->draw();
    
    if(selectorActive){
        gl::color(1.0, 0.9, 0.8, 0.3);
        gl::drawSolidRect( selector );
        gl::color(1.0, 0.9, 0.8, 0.9);
        gl::drawStrokedRect( selector );
    }
}

ModuleRef Orage::isOnModule(vec2 location){
    auto it = modules.begin();
    auto end = modules.end();
    for(; it != end ; it ++){
        if((*it)->mUi->isHit(location)){
            return (*it);
        }
    }
    return nullptr;
}


void Orage::selectModuleByArea(Rectf selector){
    resetSelectModule();
    auto it = modules.begin();
    auto end = modules.end();
    for(; it != end ; it ++){
        Rectf * r = (*it)->mUi->getBoundsRef();
        if(r->intersects(selector)){
            selectedModules->addModule(*it, [it]() {
                                            (*it)->selected = true;
                                        });
        }
    }
}
void Orage::resetSelectModule(){
    selectedModules->clear([this](ModuleRef it) {
        it->selected = false;
    });
}

void Orage::openContextMenu(vec2 position){
    contextMenu->setOrigin(position);
    contextMenu->setVisible(true);
}
void Orage::closeContextMenu(){
    if(contextMenu->isVisible()){
        contextMenu->setVisible(false);
    }
}

void Orage::openGroupMenu(vec2 position){
    groupMenu->setOrigin(position);
    groupMenu->setVisible(true);
}
void Orage::closeGroupMenu(){
    if(groupMenu->isVisible()){
        groupMenu->setVisible(false);
    }
}