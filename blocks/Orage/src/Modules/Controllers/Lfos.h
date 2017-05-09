//
//  Lfos.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-22.
//
//

#ifndef Lfos_hpp
#define Lfos_hpp

#include "ModuleBase.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Lfos : public ModuleCommon{
        
        gl::Context * mMainWinCtx;
        
        struct LfoData {
            bool active = true;
            bool reverse = false;
            float delay = 0.f;
            float clk_multi = 1;
            float clk_div = 1;
            float exp = 5;
            float saw = .0f;
            float sine = .0f;
            float rect = .0f;
        }lfoDatas;
        
        
        Lfos(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        
        ~Lfos(){
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
        typedef std::shared_ptr<class Lfos> LfosRef;
        
        static LfosRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Lfos::COUNT++;
            return LfosRef( new Lfos( name, origin, vec2(WIDTH*0.8, 280), mMainWinCtx ) );
        }
        
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Lfos> LfosRef;
}

#endif /* Lfos_hpp */
