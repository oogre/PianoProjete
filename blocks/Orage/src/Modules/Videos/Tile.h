//
//  Tile.hpp
//  orage
//
//  Created by Vincent Evrard on 2017-04-18.
//
//

#ifndef Tile_hpp
#define Tile_hpp

#include "ModuleVideo.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class Tile : public ModuleVideo{
        float _tileSizeX = .0f;
        float _tileSizeY = .0f;

        struct TileData {
            float tileSizeX = .0f;
            float tileSizeY = .0f;
            float tileRotation = .0f;
            float tileCenterX = .5f;
            float tileCenterY = .5f;
            float preRotation = .0f;
            float postRotation = .0f;
            float rotCenterX = .5f;
            float rotCenterY = .5f;
        } data;
        
        
        gl::UboRef          dataUbo;
        gl::FboRef			mFbo;
        gl::GlslProgRef     mShader;
        
        
        Tile(string name, vec2 origin, vec2 size, gl::Context * mMainWinCtx);
        
    public:
        
        ~Tile(){
            dataUbo.reset();
            mFbo.reset();
            mShader.reset();
            mMainWinCtx = nullptr;
            
        }
        
        static int COUNT;
        
        typedef std::shared_ptr<class Tile> TileRef;
        gl::Context * mMainWinCtx;
        static TileRef create( const std::string name, vec2 origin, gl::Context * mMainWinCtx)
        {
            Tile::COUNT++;
            return TileRef( new Tile( name, origin, vec2(200, 580), mMainWinCtx ) );
        }
        
        void setupShader() override;
        void setupUI() override;
        void setup() override;
        void update() override;
    };
    
    typedef std::shared_ptr<class Tile> TileRef;
}

#endif /* Tile_hpp */
