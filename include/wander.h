#ifndef _ROBOT_WANDER_H
#define _ROBOT_WANDER_H

#include "robot.h"

namespace robot {

    using namespace elma;

    //! Declare containing class before it is defined in robot.h 
    class Robot;
    
    class Wander : public State {
        public:
        //! Build "wander" state
        Wander() : State("Wander") {}

        //! Perform actions required when switching from off to wander or to noise state
        //! \param e The event that triggered the transition  
        void entry(const Event& e);

        //! 1. Detecting intruder: if intruder is in the detection area (default is 4x4 area from robot).
        //! 2. Check battery status: go into battery low mode if battery can't support robot wandering anymore.
        //! 3. Wandering around the map: wandering around the 2D map randomly (only support 4 directions: up, left, right, down).
        void during();

        //! Perform actions required when switching from wander to off, to finding or to noise state
        //! \param e The event that triggered the transition  
        void exit(const Event& e);

        Robot& robot();        
    };

}

#endif