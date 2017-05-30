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
        bool firstUpdate = true;
        float defaultAlpha = 0.0f;
    public:
        bool selected = false;
        static cinder::gl::TextureRef     CLOSE;
        static const int WIDTH;
        int id ;
        bool shouldDestroy = false;
        string name;
        SuperCanvasRef mUiabove;
        SuperCanvasRef mUi;
        
        ~ModuleCommon(){
            wires.remove(name);
            //mUi->disable();
            mUi->clear();
            mUi.reset();
            mUi = nullptr;
        }
        ModuleCommon(std::string name, vec2 origin, vec2 size){
            id = ID++;
            this->name = name;
            if(!ModuleCommon::CLOSE){
                ModuleCommon::CLOSE = gl::Texture::create(loadImage(loadAsset("/textures/close.png")));
            }
            
            //mUiabove = SuperCanvas::create(name+"UP");
            //mUiabove->setSize(size);
            
            mUi = SuperCanvas::create(name);
            //mUiabove->addSubView(mUi);
            
            //mUiabove->addSubViewToHeader(mUi);
            mUi->setSize(size);
            mUi->setOrigin(origin);
            
            ButtonRef b = Button::create( "Destroy", &shouldDestroy, Button::Format().label(false).align(Alignment::RIGHT), ModuleCommon::CLOSE);
            b->setSize( vec2( 15, 15 ) );
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
        
        
        virtual void setupUI(){};
        virtual void setup(){};
        virtual void update(){
            if(firstUpdate){
                defaultAlpha = mUi->getColorBack().a;
                firstUpdate = false;
            }
            ColorA c = mUi->getColorBack();
            if(selected){
                c.a = defaultAlpha + 0.3;
            }else{
                c.a = defaultAlpha;
            }
            mUi->setColorBack(c);
            mUi->update();
        };
    };
    typedef std::shared_ptr<class ModuleCommon> ModuleRef;
    
    template<typename DataType>
    class ModuleBase : public ModuleCommon{
    public:
        
        map<char, DataType> inputs;
        map<char, DataType> outputs;
        int inputLen;
        int outputLen;
        vector<ButtonRef> inputBtns;
        vector<ButtonRef> outputBtns;
        
        ModuleBase(std::string name, vec2 origin, vec2 size, const int & nInput, const int & nOutput);
        ~ModuleBase(){
            auto itin = inputs.begin();
            while(itin != inputs.end()){
                itin->second.reset();
                itin->second = nullptr;
                itin++;
            }
            auto itout = outputs.begin();
            while(itout != outputs.end()){
                itout->second.reset();
                itout->second = nullptr;
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
