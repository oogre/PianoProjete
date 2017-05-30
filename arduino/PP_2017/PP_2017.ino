///
/// @mainpage	PP_2017
///
/// @details	Description of the project
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Vincent Evrard
/// @author		ogre
/// @date		2017-05-23 18:48
/// @version	<#version#>
///
/// @copyright	(c) Vincent Evrard, 2017
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


///
/// @file		PP_2017.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Vincent Evrard
/// @author		ogre
/// @date		2017-05-23 18:48
/// @version	<#version#>
///
/// @copyright	(c) Vincent Evrard, 2017
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
///

#include "Arduino.h"
#include "arduino.h"
#include "CharlixBtn.h"

#define DEBUG_UNO 0

const uint8_t pins [] = { 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
CharlixButton cb(pins, 14);


void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Serial.flush();
    Serial.println("MIDI SERIAL 9600 : OK");
    pinMode(13, OUTPUT);
    for(unsigned i = 0 ; i < 3 ; i ++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }
    #if DEBUG_UNO
        //cb.initNotes();
    #else
        cb.init();
    #endif
}

long notecounter = 0;
void loop()
{

    
    #if DEBUG_UNO
    for(int i = 0 ; i < 86 ; i ++){
        if(notecounter%2==0)
        cb.noteOn(21+i, 10);
        else
        cb.noteOff(21+i, 10);
    }
    notecounter++;
    
    #else
        cb.update();
        cb.process();
    #endif

}