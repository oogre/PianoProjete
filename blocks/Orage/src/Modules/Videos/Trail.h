//
//  Trail.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-03.
//
//

#ifndef Trail_hpp
#define Trail_hpp


#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Trail : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct TrailData {
            float amount  = 1.0f;
            float black  = 0.0f;
            float white  = 1.0f;
        } data;
        
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        Trail(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        ~Trail(){
            dataUbo.reset();
            mFbo.reset();
            mFbo2.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        static int COUNT;
        
        typedef std::shared_ptr<class Trail> TrailRef;
        
        static TrailRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Trail::COUNT++;
            return TrailRef( new Trail( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Trail> TrailRef;
}


#endif /* Trail_hpp */
