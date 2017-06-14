//
//  Blur.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-06-10.
//
//

#ifndef Blur_hpp
#define Blur_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Blur : public ModuleVideo{

        struct BlurData {
            float amountX = .0f;
            float amountY = .0f;
            bool blurActive = false;
            float width = 1.0f/FBO_WIDTH;
            float height = 1.0f/FBO_HEIGHT;
        } data;
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        
        Blur(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        static int COUNT;
        
        ~Blur(){
            data.~BlurData();
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        
        typedef std::shared_ptr<class Blur> BlurRef;
        gl::Context * mMainWinCtx;
        static BlurRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Blur::COUNT++;
            return BlurRef( new Blur( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Blur> BlurRef;
}


#endif /* Blur_hpp */
