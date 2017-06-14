//
//  ColorAdjustement.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-23.
//
//

#ifndef ColorAdjustement_hpp
#define ColorAdjustement_hpp



#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class ColorAdjustement : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct ColorAdjustementData {
            float bri  = 0.0f;
            float sat  = 0.0f;
            float con  = 0.0f;
            float red  = 0.0f;
            float green  = 0.0f;
            float blue  = 0.0f;
        } data;
        
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        ColorAdjustement(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        static int COUNT;
        
        ~ColorAdjustement(){
            data.~ColorAdjustementData();
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class ColorAdjustement> ColorAdjustementRef;
        
        static ColorAdjustementRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            ColorAdjustement::COUNT++;
            return ColorAdjustementRef( new ColorAdjustement( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class ColorAdjustement> ColorAdjustementRef;
}


#endif /* ColorAdjustement_hpp */
