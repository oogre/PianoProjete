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
            float bri  = 1.0f;
            float sat  = 1.0f;
            float con  = 1.0f;
        } data;
        
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        ColorAdjustement(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        ~ColorAdjustement(){
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
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
