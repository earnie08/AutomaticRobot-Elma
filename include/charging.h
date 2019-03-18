#ifndef _ROBOT_CHARGIN_H
#define _ROBOT_CHARGIN_H

#include "robot.h"

namespace robot {

    using namespace elma;

    //! Declare containing class before it is defined in robot.h 
    class Robot;  
    
    class Charging : public State {
        public:
        //! Build "charging" state
        Charging() : State("Charging") {}

        //! Perform actions required when switching from finding to charging state
        //! \param e The event that triggered the transition  
        void entry(const Event& e);

        //! Charging battery before it comes to full status.
        void during();

        //! Perform actions required when switching from charging to wander state
        //! \param e The event that triggered the transition
        void exit(const Event& e);

        Robot& robot();        
    };
}

#endif