//
//  Config.cpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-05.
//
//

#include "Config.h"

namespace ogre {
    float Config::FAST_NOTE_RATE=0.025f;// 1 / 40
    float Config::MED_NOTE_RATE =0.03f;// 1 / 30
    float Config::SLOW_NOTE_RATE=0.1f;// 1 / 10

    float Config::CHORD_FORGET_RATE = 0.1f;
    float Config::NOTE_FORGET_RATE = 0.09f;

    char* Config::NOTE_NAME_TO_STRING[] = {
        (char*)"A",
        (char*)"A#",
        (char*)"B",
        (char*)"C",
        (char*)"C#",
        (char*)"D",
        (char*)"D#",
        (char*)"E",
        (char*)"F",
        (char*)"F#",
        (char*)"G",
        (char*)"G#"
    };

}
