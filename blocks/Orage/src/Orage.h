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
#include "SuperModule.h"


//#include "cinder/audio/audio.h"
namespace ogre {
    
    typedef std::shared_ptr<class Orage> OrageRef;
    
    class Orage/* : public Canvas */{
        gl::Context * mMainWinCtx;
        Orage(string name, gl::Context * mMainWinCtx);
        public:
            static OrageRef create( std::string name, gl::Context * mMainWinCtx)
            {
                OrageRef ref = OrageRef( new Orage( name, mMainWinCtx ) );
                ref->setup();
                return ref;
            }
            SuperCanvasRef  contextMenu;
            SuperCanvasRef  groupMenu;
            vector<ModuleRef> modules;
            vector<SuperModuleRef> groupedModules;
            SuperModuleRef selectedModules;
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
            SyphonInputRef addSyphonInput(vec2 origin);
            FreezerRef addFreezer(vec2 origin);

            OutputRef addOutput(vec2 origin);
        
            LfosRef addLfos(vec2 origin);
            FftRef addFft(vec2 origin);
        
            PianoInputRef addPianoInput(vec2 origin);
            HandSplitterRef addHandSplitter(vec2 origin);
            PositionExtractorRef addPositionExtractor(vec2 origin);
            NoteDisplayRef addNoteDisplayKeyboard(vec2 origin);
            NoteDisplayRef addNoteDisplayOctave(vec2 origin);
            DynamicAnalyserRef addDynamicAnalyser(vec2 origin);
            LastNoteExtractorRef addLastNoteExtractor(vec2 origin);
            /*
            
            
            
            KeyMixerRef addKeyMixer(vec2 origin);
            
            
            CellNoiseRef addCellNoise(vec2 origin);
            
            TrailRef addTrail(vec2 origin);*/
        
            void setup();
            void update();
            void draw(bool selectorActive, Rectf selector);
            void openContextMenu(vec2 position);
            void closeContextMenu();
            void openGroupMenu(vec2 position);
            void closeGroupMenu();
            ModuleRef isOnModule(vec2 location);
            void selectModuleByArea(Rectf selector);
            void resetSelectModule();
    };
}

#endif /* orage_hpp */
