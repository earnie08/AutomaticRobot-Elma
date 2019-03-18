#ifndef _ROBOT_NOISE_H
#define _ROBOT_NOISE_H

#include "robot.h"

namespace robot {

    using namespace elma;

    //! Declare containing class before it is defined in robot.h
    class Robot;
    
    class Noise : public State {
        public:
        //! Build "noise" state
        Noise() : State("Making Noise") {}

        //! Perform actions required when switching from wander or from evade to noise state
        //! \param e The event that triggered the transition  
        void entry(const Event& e);

        //! 1. Detecting intruder's location: if the intruder is in 4x4 area from robot's location, robot will stop wandering and make noise.
        //!     a. Checking whether intruder is in 2x2 area from robot's location. If it's too close, robot will go into evading state.
        //!     b. Checking battery status. If battery status can't support robot going back to station, robot will go into battery low mode.
        //! 2. Reset to wander state:
        void during();

        //! Perform actions required when switching from noise to evade or back to wander state
        //! \param e The event that triggered the transition
        void exit(const Event& e);

        Robot& robot();        
    };
}

#endif