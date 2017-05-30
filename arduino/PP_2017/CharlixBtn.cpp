//
//  CharlixBtn.cpp
//  PP_2017
//
//  Created by Vincent Evrard on 2017-05-23.
//  Copyright © 2017 ogre. All rights reserved.
//

#include "CharlixBtn.h"


void CharlixButton::_initButtons()
{
    buttonLen = (_pinsLen * _pinsLen) - _pinsLen;
    buttons = (BUTTON *)malloc(buttonLen * sizeof(BUTTON));
    if (buttons==NULL)
    {
        #if DEBUG_STATE
            Serial.print("BUTTONS MEMORY ALLOC FAILED : ");
            Serial.println(buttonLen * sizeof(BUTTON));
            while(true);
        #endif
    }
    
    for (uint8_t k = 0; k < buttonLen; k++)
    {
        buttons[k] = BUTTON {
            k, false, false, false, {0, 0}//, millis(), millis()
        };
    }
    update();
    #if DEBUG_STATE
        Serial.println("BUTTONS : OK");
    #endif
}

void CharlixButton::_initNotes()
{
    noteLen = NOTE_LEN;
    
    notes = (NOTE *)malloc(noteLen * sizeof(NOTE));
    if (notes==NULL)
    {
        #if DEBUG_STATE
            Serial.print("NOTES MEMORY ALLOC FAILED : ");
            Serial.println(noteLen * sizeof(NOTE));
            while(true);
        #endif
    }
    
    for (uint8_t k = 0; k < noteLen; k++)
    {
        notes[k] = NOTE {
            k, (k + 21), false, false, nullptr//, NULL
        };
    }
    #if DEBUG_STATE
        Serial.println("NOTES : OK");
    #endif
}

void CharlixButton::_notesMapping()
{
    #if DEBUG_STATE
        Serial.println("NOTES MAPPING PROCESS : ");
    #endif
    
    uint8_t mappedNote = 0 ;
    BUTTON *btn_ptr = buttons;
    #if LOAD_MAPPING
        #if DEBUG_STATE
            Serial.println("LOAD MAPPING FROM EEPROM");
        #endif
        while(EEPROM.read(addr) != 255 && addr != EEPROM.length()){
            MAP_MEMORY_OBJ memObj;
            addr += EEPROM_readAnything(addr, memObj);
            notes[memObj.not_id].front = btn_ptr + memObj.btn_id;
            notes[memObj.not_id].front->mapped = true;
            #if DEBUG_STATE
                Serial.print("BUTTON : ");
                Serial.print(notes[memObj.not_id].front->id);
                Serial.print(" MAPPED AS FRONT TO NOTE : ");
                Serial.println(notes[memObj.not_id].midi);
            #endif
        }
    
    #else // !LOAD_MAPPING
        #if DEBUG_STATE
            Serial.println("PRESS EACH KEYS FROM LOW TO HIGH");
        #endif
        //clear EEPROM
        for (int i = 0 ; i < EEPROM.length() ; i++) {
            EEPROM.write(i, 255);
        }
        while(mappedNote < noteLen && addr != EEPROM.length())
        {
            update();
            for (uint8_t k = 0; k < buttonLen; k++)
            {
                if(buttons[k].stateChanged && buttons[k].state)
                {
                    //if(buttons[k].mapped){
                    notes[mappedNote].front = btn_ptr + k;
                    notes[mappedNote].front->mapped = true;
                    
                    MAP_MEMORY_OBJ memObj = {
                        notes[mappedNote].front->id,
                        notes[mappedNote].id
                    };
                    addr += EEPROM_writeAnything(addr, memObj);

                    #if DEBUG_STATE
                        Serial.print("BUTTON : ");
                        Serial.print(notes[mappedNote].front->id);
                        Serial.print(" MAPPED AS FRONT TO NOTE : ");
                        Serial.println(notes[mappedNote].midi);
                    #endif
                    mappedNote++;
                    // DISABLED NOTE
                    if(notes[mappedNote].midi == 23 )mappedNote++;
                    if(notes[mappedNote].midi == 49 )mappedNote++;
                    if(notes[mappedNote].midi == 82 )mappedNote++;
                }
            }
        }
    #endif // !LOAD_MAPPING
    #if DEBUG_STATE
        Serial.print("NOTES MAPPED !");
    #endif
}


void CharlixButton::update()
{
    for (uint8_t i = 0, c = 0 ; i < _pinsLen; i ++ )
    {
        for (uint8_t j = 0 ; j < _pinsLen ; j ++)
        {
            if (i != j ) {

            #if PULLUP
                //OutputLow(_pins[i]);
                InputPullup(_pins[i]);
                OutputLow(_pins[j]);
            #else
                OutputHigh(_pins[i]);
                InputNopullup(_pins[j]);
            #endif
            uint8_t btnCmp = c++;
            //    delay(1);
            bool state = digitalRead(_pins[j]);
            if (buttons[btnCmp].state != state)
            {
                //if(i>j){
                //Serial.println(String(btnCmp)+" : "+String(i)+" "+String(j));
                //}else{
                //Serial.println(String(btnCmp)+" : "+String(j)+" "+String(i));
                //}
                //buttons[btnCmp].address[0] = i;
                //buttons[btnCmp].address[1] = j;
                buttons[btnCmp].stateChanged = true;
                buttons[btnCmp].state       = state;
                //buttons[btnCmp].oldChangedTime  = buttons[btnCmp].changedTime;
                //buttons[btnCmp].changedTime     = millis();
            }
            else
            {
                buttons[btnCmp].stateChanged = false;
            }
            //Serial.println(String(i) + " : InputPullup - " + String(j) + " : OutputLow "  );
                //delay(100);
            
            #if PULLUP
                InputNopullup(_pins[i]);
                InputNopullup(_pins[j]);
            #else
                OutputLow(_pins[i]);
                OutputLow(_pins[j]);
            #endif
            }else{
                //Serial.println(String(i) + " - " + String(j) );
                //delay(1000);
            }
        }
    }
}


void CharlixButton::process()
{
    for (uint8_t k = 0; k < noteLen; k++)
    {
        if(notes[k].front!= nullptr){
            if(notes[k].front->state && notes[k].front->stateChanged){
                notes[k].front->stateChanged = false;
                noteOn(notes[k].midi, 10);
            }
            else if(!notes[k].front->state && notes[k].front->stateChanged){
                notes[k].front->stateChanged = false;
                noteOff(notes[k].midi, 10);
            }
        }
    }
}



void CharlixButton::processDebugUno()
{
    for (uint8_t k = 0; k < noteLen; k++)
    {
        if(notes[k].state && notes[k].stateChanged){
            notes[k].stateChanged = false;
            noteOn(notes[k].midi, 10);
        }
        else if(!notes[k].state && notes[k].stateChanged){
            notes[k].stateChanged = false;
            noteOff(notes[k].midi, 10);
        }
    }
}

void CharlixButton::noteOn(uint8_t pitch, uint8_t velocity)
{
    #if DEBUG_STATE
        Serial.print("NOTE : ");
        Serial.print(pitch);
        Serial.print(" VELOCITY : ");
        Serial.print(velocity);
        Serial.println(" ON");
    #endif
    #if MIDI
        Serial.write(0x90 + MIDI_CHANNEL);
        Serial.write(pitch);
        Serial.write(velocity);
    #endif
}

void CharlixButton::noteOff(uint8_t pitch, uint8_t velocity)
{
    #if DEBUG_STATE
        Serial.print("NOTE : ");
        Serial.print(pitch);
        Serial.print(" VELOCITY : ");
        Serial.print(velocity);
        Serial.println(" OFF");
    #endif
    #if MIDI
        Serial.write(0x80 + MIDI_CHANNEL);
        Serial.write(pitch);
        Serial.write(velocity);
    #endif
}