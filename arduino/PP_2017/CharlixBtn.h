//
//  CharlixBtn.hpp
//  PP_2017
//
//  Created by Vincent Evrard on 2017-05-23.
//  Copyright © 2017 ogre. All rights reserved.
//

#ifndef CharlixBtn_hpp
#define CharlixBtn_hpp

#include <Arduino.h>
#include <arduino.h>
#include <stdint.h>
#include "EEPROMAnything.h"

#define MIDI 1
#define MIDI_CHANNEL 1

#define DEBUG_LISTENER 0
#define DEBUG_STATE 0
#define LOAD_MAPPING 1
#define NOTE_LEN 85
#define PULLUP 0

typedef struct {
    uint8_t btn_id;
    uint8_t not_id;
} MAP_MEMORY_OBJ;

typedef struct {
    uint8_t id ;
    bool mapped;
    bool state;
    bool stateChanged;
    uint8_t address [2];
    //uint32_t changedTime;
    //uint32_t oldChangedTime;
} BUTTON;

typedef struct {
    uint8_t id ;
    uint8_t midi;
    bool state;
    bool stateChanged;
    BUTTON *front;
    //BUTTON *back;
} NOTE;

class CharlixButton
{
    public :
    CharlixButton(const uint8_t pins [], uint8_t pinLen){
        _pinsLen = pinLen;
        _pins = (uint8_t*) &pins[0];
    }
    void init(){
        for (uint8_t i = 0; i < _pinsLen; i ++ )
        {
            #if PULLUP
                InputNopullup(_pins[i]);
            #else
                OutputLow(_pins[i]);
            #endif
        }
        _initButtons();
        #if DEBUG_LISTENER
            while (true)
            {
                update();
            }
        #endif
        _initNotes();
        _notesMapping();
    }
    void update();
    void process();
    void processDebugUno();
    void noteOn(uint8_t pitch, uint8_t velocity);
    void noteOff(uint8_t pitch, uint8_t velocity);
    
    BUTTON *buttons;
    uint8_t buttonLen;
    
    NOTE *notes;
    uint8_t noteLen;
    void initNotes(){
        _initNotes();
    }
private:
    int addr = 0;
    void _initButtons();
    void _initNotes();
    void _notesMapping();
    
    uint8_t *_pins;
    uint8_t _pinsLen;
    uint8_t _maxNote;
    
    void InputPullup(uint8_t pin) {
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t *reg, *out;
        reg = portModeRegister(port);
        out = portOutputRegister(port);
        uint8_t oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out |= bit;
        SREG = oldSREG;
    }
    void OutputLow(uint8_t pin) {
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t *reg, *out;
        // JWS: can I let the optimizer do this?
        reg = portModeRegister(port);
        out = portOutputRegister(port);
        uint8_t oldSREG = SREG;
        cli();
        *reg |= bit;
        *out &= ~bit;
        SREG = oldSREG;
    }
    void OutputHigh(uint8_t pin) {
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t *reg, *out;
        // JWS: can I let the optimizer do this?
        reg = portModeRegister(port);
        out = portOutputRegister(port);
        uint8_t oldSREG = SREG;
        cli();
        *reg |= bit;
        *out |= bit;
        SREG = oldSREG;
    }
    void InputNopullup(uint8_t pin) {
        uint8_t bit = digitalPinToBitMask(pin);
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t *reg, *out;
        reg = portModeRegister(port);
        out = portOutputRegister(port);
        uint8_t oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out &= ~bit;
        SREG = oldSREG;
    }
};

#endif /* CharlixBtn_hpp */
