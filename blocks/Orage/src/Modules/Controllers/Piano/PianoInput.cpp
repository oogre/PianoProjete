//
//  PianoInput.cpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-04.
//
//

#include "PianoInput.h"

using namespace ogre;
using namespace cinder;
using namespace cinder::gl;
using namespace std;
using namespace reza::ui;

namespace ogre {
    
    PianoInputRef PianoInput::singleton = nullptr;
    int PianoInput::COUNT = 0;
    
    PianoInput::PianoInput( std::string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx ) : ModulePiano(name+" "+ tools.to_roman(PianoInput::COUNT), origin, size, 0, 1){
        this->mMainWinCtx = mMainWinCtx;
        
        playingNotes = Noteset::create();
        
        boost::dynamic_bitset<> _ID(Config::NOTE_LEN);
        _ID[Config::NOTE_LEN-1]=1;
        for(int i = 0 ; i < Config::NOTE_LEN ; i ++){
            Note n(i, &_ID);
            Data::notes.push_back(n);
            _ID>>=1;
        }
        
        
        outputs['A'] = playingNotes;
        
        try {
            Serial::Device dev = Serial::findDeviceByNameContains( "tty.usbmodem" );
            console() << "Device: " << dev.getName() << endl;
            mSerial = Serial::create( dev, 9600 );
            mSerial->flush();
        }
        catch( SerialExc &exc ) {
            CI_LOG_EXCEPTION( "coult not initialize the serial device", exc );
            //exit( -1 );
        }
        
    }
    
    void PianoInput::setup(){
        ModulePiano::setupUI();
        setupUI();
        
    }

    
    void PianoInput::update(){
        
        if(mMainWinCtx != gl::Context::getCurrent()){
            return;
        }
        ModulePiano::update();
        
        Byte in = 0, pitch = 0, velocity = 0;
        

        if(!mSerial){
            in = rand() % 2 == 1 ? NOTE_ON : NOTE_OFF;
            in += 1;
            pitch = ((rand() % Config::NOTE_LEN)) + Config::MIN_PITCH;
            if(Note * currentNote = Data::getNote(pitch)){
                if(currentNote->isPlayed){
                    in = NOTE_OFF + 1;
                }
            }
            //in = ci::app::getElapsedFrames() % 3 == 1 ? 0x81 : 0x91;
            //pitch = ((ci::app::getElapsedFrames()/3) % Config::NOTE_LEN) + Config::MIN_PITCH;
            
            velocity = 10;
        }
        else while(mSerial && mSerial->getNumBytesAvailable()>3) {
            in = mSerial->readByte();
            if ((in ^ NOTE_ON) <= CHANNEL_LEN || (in ^ NOTE_OFF) <= CHANNEL_LEN){
                pitch = mSerial->readByte();
                velocity = mSerial->readByte();
            }
        }
        
        
        if ((in ^ NOTE_ON) <= CHANNEL_LEN){
            if(Note * currentNote = Data::getNote(pitch)){
                if(currentNote->isPlayed)return;
                currentNote->playedAt = cinder::app::getElapsedSeconds();
                currentNote->playedCountMem = ++currentNote->playedCount;
                currentNote->isPlayed = true;
                playingNotes->addNote(currentNote);
                Data::noteTotal++;
                Data::noteOnCounter++;
                //cout<<"ADD "<<currentNote->ID.to_string()<<endl;
                //ofNotifyEvent(noteOnEvent, * currentNote, this);
            }
        }else if ((in ^ NOTE_OFF) <= CHANNEL_LEN){
            if(Note * currentNote = Data::getNote(pitch)){
                if(!currentNote->isPlayed)return;
                currentNote->isPlayed = false;
                currentNote->playedAt = cinder::app::getElapsedSeconds();
                if(currentNote->playedAt != 0){
                    currentNote->playedTimeMem = currentNote->playedTime += (cinder::app::getElapsedSeconds() - currentNote->playedAt);
                }
                currentNote->playedAt = 0;
                playingNotes->removeNote(currentNote);
                Data::noteOffCounter++;
                //ofNotifyEvent(noteOnEvent, * currentNote, this);
                //cout<<"REMOVE  "<<currentNote->ID.to_string()<<endl;
            }
        }
    }
    
    void PianoInput::setupUI(){
        mUi->setColorBack(ColorAT<float>(vec4(.1f, .2f, .3f, .4f)));
        //mUi->setColorFill(ColorAT<float>(vec4(.8f, .9f, 1.f, .6f)));
        mUi->setColorFillHighlight(ColorAT<float>(vec4(.1f, .9f, 1.f, 1.f)));
        
        ModulePiano::setupUI();
        setupInput();
        setupOutput();
        mUi->setMinified(true);
    }
};