//
//  Config.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-05-05.
//
//

#ifndef Config_hpp
#define Config_hpp

using namespace cinder;
using namespace cinder::gl;
using namespace std;

namespace ogre {
    
class Config{
    private:
        // Disallow creating an instance of this object
        Config() {}
    
    public :
        const static unsigned int MIN_PITCH = 21;
        const static unsigned int MAX_PITCH = 108;
        const static unsigned int NOTE_LEN = 88;
        const static unsigned int OCTAVE_LEN = 12;
    
        const static unsigned int MAX_DIST_PER_HAND = 13;
        const static unsigned int MAX_NOTE_PER_HAND = 5;
        const static unsigned int MAX_HAND = 5;
    
        static float FAST_NOTE_RATE;
        static float MED_NOTE_RATE;
        static float SLOW_NOTE_RATE;
    
        const static unsigned int MIN_NOTE_PER_CHORD = 3;
        const static unsigned int MAX_CHORD_MEMORY = 10;

        static float CHORD_FORGET_RATE;
        static float NOTE_FORGET_RATE;

        static char* NOTE_NAME_TO_STRING [];
    
        enum NOTE_NAME{
            A,  // LA
            A_,
            B,  // SI
            C,  // DO
            C_,
            D,  // RE
            D_,
            E,  // MI
            F,  // FA
            F_,
            G,  // SOL
            G_
        };
    };
};
//extern const Config config;

#endif /* Config_hpp */


