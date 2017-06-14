//
//  Output.hpp
//  PianoProjete
//
//  Created by Vincent Evrard on 2017-05-19.
//
//

#ifndef Output_hpp
#define Output_hpp


#include "ModuleVideo.h"
#include "cinder/qtime/AvfWriter.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Output : public ModuleVideo{
        gl::Context * mMainWinCtx;
        map <string, WindowCanvasRef> windowCanvas;
        gl::FboRef			mFbo;
        
        Output(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        qtime::MovieWriterRef mMovieExporter;
        qtime::MovieWriter::Format format;
        Surface8u	mInputImage;
    public:
        static int COUNT;
        static int winOutCOUNT;
        ~Output(){
            mFbo.reset();
            mMainWinCtx = nullptr;
        }
        
        typedef std::shared_ptr<class Output> OutputRef;
        
        static OutputRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Output::COUNT++;
            return OutputRef( new Output( name, origin, vec2(WIDTH*2, 580),  mMainWinCtx ) );
        }
        
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
        void createOutputWindow();
    };
    
    typedef std::shared_ptr<class Output> OutputRef;
}


#endif /* Output_hpp */
