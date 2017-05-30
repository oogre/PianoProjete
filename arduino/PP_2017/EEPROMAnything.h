//
//  EEPROMAnything.h
//  PP_2017
//
//  Created by Vincent Evrard on 2017-05-24.
//  Copyright © 2017 ogre. All rights reserved.
//

#ifndef EEPROMAnything_h
#define EEPROMAnything_h

#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
    return i;
}


#endif /* EEPROMAnything_h */
