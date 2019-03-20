#ifndef _ROBOT_FINDING_H
#define _ROBOT_FINDING_H

#include "robot.h"

namespace robot {

    using namespace elma;

    //! Declare containing class before it is defined in robot.h 
    class Robot;
    
    class Finding : public State {
        public:
        //! Build "finding" state
        Finding() : State("Finding Charge Station") {}

        //! Perform actions required when switching from wandering to finding or evade to finding state
        //! \param e The event that triggered the transition  
        void entry(const Event& e);

        //! Robot will plan the route to charge station.
        //! The priority of the plan is to go x-axis first until robot has the same x-vaule as charge station 
        void during();
        
        //! Perform actions required when switching from finding to charging state
        //! \param e The event that triggered the transition
        void exit(const Event& e);
        
        //! Checking robot wether in charge station or not.
        //! \return True: robot is in charge station ; False: robot is not in charge station
        bool inChargeStation();
        
        Robot& robot();  

        private:
        bool _x_first = true;      
    };

}

#endif