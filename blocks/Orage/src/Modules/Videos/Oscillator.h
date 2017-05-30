//
//  Oscillator.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-15.
//
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Oscillator : public ModuleVideo{
        gl::Context * mMainWinCtx;
        
        float trail = 1.0;
        
        struct OscillatorData {
            float freq = 60.f;
            float sync = .0f;
            float exp = 1.f;
            float phaseDx = .0f;
            float phaseDy = .0f;
            float modifier = .0f;
            bool reverse = false;
            float sine = .0f;
            float rect = .0f;
            float saw = 1.f;
            float tri = .0f;
            float noise = .0f;
        } data;
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo, mFbo2;
        gl::GlslProgRef     mShader;
        
        Oscillator(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        public:
        static int COUNT;
            ~Oscillator(){
                data.~OscillatorData();
                dataUbo.reset();
                mFbo.reset();
                mFbo2.reset();
                mShader.reset();
                mMainWinCtx = nullptr;
                

                
            }

            typedef std::shared_ptr<class Oscillator> OscillatorRef;
        
            static OscillatorRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
            {
                Oscillator::COUNT++;
                return OscillatorRef( new Oscillator( name, origin, vec2(WIDTH, 580), mMainWinCtx ) );
            }
            void setupShader() override;
            void setupUI() override;
            void setup() override;
            void update() override;
    };
    
    typedef std::shared_ptr<class Oscillator> OscillatorRef;
}

#endif /* Oscillator_hpp */
