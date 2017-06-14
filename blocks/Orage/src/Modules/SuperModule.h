//
//  SuperModule.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-17.
//
//

#ifndef SuperModule_hpp
#define SuperModule_hpp

#include "UI.h"

#include "Wires.h"
#include "Tools.h"

#include "Oscillator.h"
#include "Matte.h"
#include "Cloud.h"

#include "Tile.h"
#include "Spliter.h"
#include "ColorAdjustement.h"


#include "Mosher.h"
#include "Crossfader.h"

#include "Output.h"

#include "SyphonInput.h"

#include "Freezer.h"
#include "Delay.h"
#include "Resize.h"
#include "Blur.h"

//#include "KeyMixer.h"
//#include "CellNoise.h"

#include "Lfos.h"
#include "FFT.h"

#include "PianoInput.h"
#include "HandSplitter.h"
#include "PositionExtractor.h"
#include "NoteDisplay.h"
#include "DynamicAnalyser.h"
#include "LastNoteExtractor.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class SuperModule : public ModuleCommon{
        SuperModule();
        public :
        vector<ModuleRef> modules;
        ~SuperModule(){}
        typedef std::shared_ptr<class SuperModule> SuperModuleRef;
        static SuperModuleRef create( )
        {
            return SuperModuleRef( new SuperModule() );
        }

        virtual void update() override;
        void clear(const std::function<void( ModuleRef )> &callback);
        void addModule(ModuleRef module, const std::function<void( )> &callback);
    };
    typedef std::shared_ptr<class SuperModule> SuperModuleRef;
}

#endif /* SuperModule_hpp */
