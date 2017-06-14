//
//  Delay.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-06-01.
//
//

#ifndef Delay_hpp
#define Delay_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Delay : public ModuleVideo{
        gl::Context * mMainWinCtx;
        static const int MAX_TEX = 10;
        static const int MAX_IMG_PER_TEX = 12;
        static const int MAX_BUFFER = MAX_TEX * MAX_IMG_PER_TEX;
        float bufferLen = 1.f;
        struct DelayData {
            int bufferLen = 1;
            bool modifierActive = false;
            int cursor = 0 ;
            float part = 1.0f/MAX_IMG_PER_TEX;
            float width = 1.0f/(FBO_WIDTH*MAX_IMG_PER_TEX);
            float height = 1.0f/FBO_HEIGHT;
        } data;
        CameraPersp         CAM2 = CameraPersp(ModuleVideo::FBO_WIDTH * MAX_IMG_PER_TEX, ModuleVideo::FBO_HEIGHT, -60.0f, 1, 1000 );
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        vector<gl::FboRef>  mFboBuffer;
        gl::GlslProgRef     mShader;
        
        cinder::gl::TextureRef    testTex;

        Delay(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        static int COUNT;
        ~Delay(){
            data.~DelayData();
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class Delay> DelayRef;
        
        static DelayRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Delay::COUNT++;
            return DelayRef( new Delay( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Delay> DelayRef;
}


#endif /* Delay_hpp */
