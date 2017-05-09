//
//  Spliter.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-20.
//
//

#ifndef Spliter_hpp
#define Spliter_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Spliter : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        Spliter(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
    public:
        
        ~Spliter(){
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
        typedef std::shared_ptr<class Spliter> SpliterRef;
        
        static SpliterRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Spliter::COUNT++;
            return SpliterRef( new Spliter( name, origin, vec2(200, 580),  mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Spliter> SpliterRef;
}



#endif /* Spliter_hpp */
