#ifndef _ROBOT_OFF_H
#define _ROBOT_OFF_H

#include "robot.h"

namespace robot {

    using namespace elma;

    class Off : public State {
        public:
        //! Build "off" state
        Off() : State("Off") {}
        void entry(const Event& e) {}
        void during() {} 
        void exit(const Event& e){}
    };

}

#endif