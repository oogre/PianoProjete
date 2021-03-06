//
//  WireCV.hpp
//  ORAGE2
//
//  Created by Vincent Evrard on 2017-04-25.
//
//

#ifndef WireCV_hpp
#define WireCV_hpp


#include "Wire.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;
using namespace std;

namespace ogre {

    
class WireCV : public Wire{
    SliderfRef slave;
    SliderfRef master;
    WireCV(SliderfRef slave, SliderfRef master, ButtonRef slaveBtn, ButtonRef masterBtn) : Wire(slaveBtn, masterBtn){
        this->slave = slave;
        this->master = master;
        master->setSlave(slave);
        slave->setSlave(master);
        _color = Color(1.0f,0.0f, 1.0f);
        _colorHighLigth = Color(1.0f,.0f, .0f);
    }
    public :
    ~WireCV(){
        master->removeSlave(slave);
        slave->removeSlave(master);
    }
    typedef std::shared_ptr<class WireCV> WireCVRef;
    static WireCVRef create(SliderfRef slave, SliderfRef master, ButtonRef slaveBtn, ButtonRef masterBtn)
    {
        return WireCVRef(new WireCV(slave, master, slaveBtn, masterBtn));
    }
};
typedef std::shared_ptr<class WireCV> WireCVRef;

}
#endif /* WireCV_hpp */
