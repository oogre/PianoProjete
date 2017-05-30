//
//  Cloud.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-04-27.
//
//

#ifndef Cloud_hpp
#define Cloud_hpp


#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Cloud : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct CloudData {
            float redShift = 0.f;
            float blueShift = 0.f;
            float greenShift = 0.f;
            float lvl = 1.f;
            float move = 0.f;
            float u_time = 0.0f;
            float sizex = 1.0f;
            float sizey = 1.0f;
            float seedXX = 0.f;
            float seedYX = 0.f;
            float seedZX = 0.f;
            float seedXY = 0.f;
            float seedYY = 0.f;
            float seedZY = 0.f;
        } data;
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        
        
        Cloud(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
    public:
        static int COUNT;
        ~Cloud(){
            data.~CloudData();
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class Cloud> CloudRef;
        
        static CloudRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Cloud::COUNT++;
            return CloudRef( new Cloud( name, origin, vec2(WIDTH, 580),  mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Cloud> CloudRef;
}


#endif /* Cloud_hpp */
