//
//  Freezer.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-29.
//
//

#ifndef Freezer_hpp
#define Freezer_hpp


#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Freezer : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct FreezerData {
            float amount  = 1.0f;
            float black  = 0.0f;
            float white  = 1.0f;
            bool selectorActive = false;
        } data;
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        Freezer(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        static int COUNT;
        ~Freezer(){
            data.~FreezerData();
            dataUbo.reset();
            mFbo.reset();
            mFbo2.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class Freezer> FreezerRef;
        
        static FreezerRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Freezer::COUNT++;
            return FreezerRef( new Freezer( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Freezer> FreezerRef;
}



#endif /* Freezer_hpp */
