#ifndef _ROBOT_EVADE_H
#define _ROBOT_EVADE_H

#include "robot.h"

namespace robot {

    using namespace elma;

    //! Declare containing class before it is defined in robot.h
    class Robot;
    
    class Evade : public State {
        public:
        //! Build "evade" state
        Evade() : State("Evade") {}

        //! Perform actions required when switching from noise to evade state
        //! \param e The event that triggered the transition  
        void entry(const Event& e);

        //! 1. Detecting intruder's location: if the intruder is in 2x2 area from robot's location, robot will start escaping.
        //!    a. Check battery status: check battery whether can support robot to escape.
        //!    b. Escaping: useing 2x times speed ( 2 steps everytime ) to escape. The escape direction is ramdonly.
        //! 2. Reset to noise state: if the intruder is not in 2x2 area around robot's location, robot state will reset to noise state.
        void during();

        //! Perform actions required when switching from evade to finding or back to noise state
        //! \param e The event that triggered the transition
        void exit(const Event& e);
        
        Robot& robot();        
    };

}

#endif