//
//  PianoInput.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-04.
//
//

#ifndef PianoInput_hpp
#define PianoInput_hpp

#include "ModulePiano.h"
#include "cinder/Serial.h"
#include "cinder/Log.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class PianoInput : public ModulePiano{
        gl::Context * mMainWinCtx;
        SerialRef	mSerial;
        
        PianoInput(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
    public:
        const static unsigned int NOTE_ON = 0x90;
        const static unsigned int NOTE_OFF = 0x80;
        const static unsigned int NOTE_NULL = 0x00;
        const static unsigned int CHANNEL_LEN = 0x0f;
        
        NotesetRef playingNotes;
        
        ~PianoInput(){
        }
        static int COUNT;
        typedef std::shared_ptr<class PianoInput> PianoInputRef;
        static PianoInputRef singleton;
        static PianoInputRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            if(!singleton){
                PianoInput::COUNT++;
                singleton =  PianoInputRef( new PianoInput( name, origin, vec2(200, 200), mMainWinCtx ) );
            }
            return singleton;
        }
        
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class PianoInput> PianoInputRef;
}



#endif /* PianoInput_hpp */
