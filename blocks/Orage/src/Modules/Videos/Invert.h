//
//  Invert.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-04-26.
//
//

#ifndef Invert_hpp
#define Invert_hpp


#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Invert : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct InvertData {
            float red  = 1.0f;
            float green  = 1.0f;
            float blue  = 1.0f;
        } data;
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        Invert(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        ~Invert(){
            data.~InvertData();
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
        typedef std::shared_ptr<class Invert> InvertRef;
        
        static InvertRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Invert::COUNT++;
            return InvertRef( new Invert( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Invert> InvertRef;
}


#endif /* Invert_hpp */
