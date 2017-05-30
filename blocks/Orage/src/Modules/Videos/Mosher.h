//
//  Mosher.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-20.
//
//

#ifndef Mosher_hpp
#define Mosher_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Mosher : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        struct MosherData {
            float map1  = .0f; //gain
            float map2  = .0f; //gain2
            float gain  = .0f; //gain3
            float x     = .0f;
            float y     = .0f;
        } data;
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        Mosher(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        static int COUNT;
        ~Mosher(){
            data.~MosherData();
            dataUbo.reset();
            mFbo.reset();
            mFbo2.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class Mosher> MosherRef;
        
        static MosherRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Mosher::COUNT++;
            return MosherRef( new Mosher( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Mosher> MosherRef;
}


#endif /* Mosher_hpp */
