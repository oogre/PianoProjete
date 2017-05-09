//
//  orage.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-15.
//
//

#ifndef orage_hpp
#define orage_hpp

#if defined( CINDER_MSW )
    namespace ogre {
        typedef uint8_t Byte;
    }

#endif

#include "UI.h"
#include "Wires.h"
#include "Tools.h"

#include "Oscillator.h"
#include "Matte.h"
#include "Cloud.h"

#include "Tile.h"
#include "Spliter.h"
#include "ColorAdjustement.h"
#include "Invert.h"

//#include "SyphonInput.h"
#include "Mosher.h"
#include "Crossfader.h"
//#include "Output.h"


#include "Lfos.h"
#include "FFT.h"

#include "PianoInput.h"
#include "HandSplitter.h"
#include "PositionExtractor.h"
#include "NoteDisplay.h"

/*

#include "KeyMixer.h"


#include "CellNoise.h"
#include "Trail.h"
 */

#include "cinder/audio/audio.h"
namespace ogre {
    
    typedef std::shared_ptr<class Orage> OrageRef;
    
    class Orage/* : public Canvas */{
        //AppCocoaView * parent;
        gl::Context * mMainWinCtx;
        Orage(string name, /*AppCocoaView * parent, */gl::Context * mMainWinCtx);
        public:
            static OrageRef create( std::string name, /*AppCocoaView * parent, */gl::Context * mMainWinCtx)
            {
                OrageRef ref = OrageRef( new Orage( name, /*parent,*/ mMainWinCtx ) );
                ref->setup();
                return ref;
            }
        
            vector<ModuleRef> modules;
        
            cinder::gl::Texture2dRef debug;
        
            OscillatorRef addOscillator(vec2 origin);
            TileRef addTile(vec2 origin);
            MosherRef addMosher(vec2 origin);
            MatteRef addMatte(vec2 origin);
            SpliterRef addSpliter(vec2 origin);
            CrossfaderRef addCrossfader(vec2 origin);
            ColorAdjustementRef addColorAdjustement(vec2 origin);
            InvertRef addInvert(vec2 origin);
            CloudRef addCloud(vec2 origin);
        
            LfosRef addLfos(vec2 origin);
            FftRef addFft(vec2 origin);
        
            PianoInputRef addPianoInput(vec2 origin);
            HandSplitterRef addHandSplitter(vec2 origin);
            PositionExtractorRef addPositionExtractor(vec2 origin);
            NoteDisplayRef addNoteDisplayKeyboard(vec2 origin);
            NoteDisplayRef addNoteDisplayOctave(vec2 origin);
            /*
            
            
            
            KeyMixerRef addKeyMixer(vec2 origin);
            
            
            CellNoiseRef addCellNoise(vec2 origin);
            
            TrailRef addTrail(vec2 origin);*/
        
            void setup();
            void update();
            void draw();
    };
}

#endif /* orage_hpp */
