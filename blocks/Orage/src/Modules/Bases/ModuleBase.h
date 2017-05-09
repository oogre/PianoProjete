//
//  ModuleBase.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-05.
//
//

#ifndef ModuleBase_hpp
#define ModuleBase_hpp

#include "UI.h"
#include "Wires.h"
#include "Tools.h"
#include "Structs.h"
#include "Config.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {
    class ModuleCommon{
        static int ID;
    public:
        static cinder::gl::TextureRef     CLOSE;
        ~ModuleCommon(){
            wires.remove(name);
            mUi->disable();
            mUi->clear();
            mUi.reset();
        }
        ModuleCommon(std::string name, vec2 origin, vec2 size){
            id = ID++;
            this->name = name;
            if(!ModuleCommon::CLOSE){
                ModuleCommon::CLOSE = gl::Texture::create(loadImage(loadAsset("/textures/close.png")));
            }
            
            mUi = SuperCanvas::create(name);
            
            mUi->setOrigin(origin+vec2(0, 30));
            mUi->setSize(size);
            
            ButtonRef b = Button::create( "Destroy", &shouldDestroy, Button::Format().label(false).align(Alignment::RIGHT), ModuleCommon::CLOSE);
            b->setSize( vec2( 25, 25 ) );
            b->setColorBack(ColorA(0, 0, 0, 0));
            b->setColorBounds(ColorA(0, 0, 0, 0));
            b->setColorBoundsOutline(ColorA(0, 0, 0, 0));
            b->setColorFill(ColorA(0, 0, 0, 0));
            b->setColorFillHighlight(ColorA(0, 0, 0, 0));
            b->setColorOutline(ColorA(0, 0, 0, 0));
            b->setColorOutlineHighlight(ColorA(0, 0, 0, 0));
            mUi->addSubViewRight(b, Alignment::RIGHT);
            mUi->addSubViewToHeader(b);

        }
        int id ;
        bool shouldDestroy = false;
        string name;
        SuperCanvasRef mUi;
        
        
        virtual void setupUI(){};
        virtual void setup(){};
        virtual void update(){
            mUi->update();
        };
    };
    typedef std::shared_ptr<class ModuleCommon> ModuleRef;
    
    template<typename DataType>
    class ModuleBase : public ModuleCommon{
    public:
        
        map<char, DataType> inputs;
        map<char, DataType> outputs;
        
        vector<ButtonRef> inputBtns;
        vector<ButtonRef> outputBtns;
        
        ModuleBase(std::string name, vec2 origin, vec2 size, const int & nInput, const int & nOutput);
        ~ModuleBase(){
            auto itin = inputs.begin();
            while(itin != inputs.end()){
                itin->second.reset();
                itin++;
            }
            auto itout = outputs.begin();
            while(itout != outputs.end()){
                itout->second.reset();
                itout++;
            }
            inputs.clear();
            outputs.clear();
            inputBtns.clear();
            outputBtns.clear();
        }
        
        virtual void setupInput();
        virtual void setupOutput();
        virtual void setupUI() override;
        virtual void setup() override;
        virtual void update() override;
    };
    
    
}


#endif /* ModuleBase_hpp */
