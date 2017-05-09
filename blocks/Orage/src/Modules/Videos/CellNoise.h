//
//  CellNoise.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-04-27.
//
//

#ifndef CellNoise_hpp
#define CellNoise_hpp


#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class CellNoise : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct CellNoiseData {
            float movex = .0f; //gain
            float movey = .0f; //gain
            float size = 1.0f; //gain
            float square = 1.0f; //gain
            float power = 1.0f;
        } data;
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        
        
        CellNoise(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
    public:
        
        ~CellNoise(){
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
        typedef std::shared_ptr<class CellNoise> CellNoiseRef;
        
        static CellNoiseRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            CellNoise::COUNT++;
            return CellNoiseRef( new CellNoise( name, origin, vec2(200, 580),  mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class CellNoise> CellNoiseRef;
}


#endif /* CellNoise_hpp */
