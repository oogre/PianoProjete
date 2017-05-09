//
//  Crossfader.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-21.
//
//

#ifndef Crossfader_hpp
#define Crossfader_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Crossfader : public ModuleVideo{
        gl::Context * mMainWinCtx;
        map<char, gl::Texture2dRef> oldInputs;
        TextureViewRef inputA;
        TextureViewRef inputB;
        float crossfade = 0 ;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        Crossfader(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        
        ~Crossfader(){
            inputA.reset();
            inputB.reset();
            auto itin = oldInputs.begin();
            while(itin != oldInputs.end()){
                itin->second.reset();
                itin++;
            }
            oldInputs.clear();
            mFbo.reset();
            mFbo2.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        static int COUNT;
        
        typedef std::shared_ptr<class Crossfader> CrossfaderRef;
        
        static CrossfaderRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Crossfader::COUNT++;
            return CrossfaderRef( new Crossfader( name, origin, vec2(300, 500), mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Crossfader> CrossfaderRef;
}

#endif /* Crossfader_hpp */
