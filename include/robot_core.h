#ifndef _ROBOT_CORE_H
#define _ROBOT_CORE_H

#include <iostream>
#include "elma.h"
#include "mapinfo.h"
#include "battery.h"

using namespace elma;
typedef enum {
    off,
    running,
    making_noise,
    evading,
    finding,
    charging
} Status;

namespace robot{
    class Robot_Core : public Process{
        public:
        //!Construct
        //! \param mpinfo Map information from mapinfo.h
        Robot_Core(MapInfo *mpinfo):Process("Robot Core"){
            mp_info = mpinfo;
            mp_info->setRobotLocation(0,0);
            status = off;
            proximity = false;
            noise = false;
            x_first = true;
            printStatus();
        }

        //! Random next position when robot is wandering
        void wandering();

        //! Check if the distince between charge station and robot is longer than battery consume rate
        //! \return True: will out of battery ; False: can keep going
        bool batteryRunOut();
        
        //! Plan the path to charge station and check if the robot is in charge station
        //! \return True: robot is in charge station ; False: robot is not in charge station
        bool inChargeStation();

        //! Detecting intruder is around the robot and if it's too close to robot.
        //! \return True: intruder detected ; False: intruder not detected
        bool detecting();

        //! override init() for Robot
        void init();

        //! override init() for Robot
        void update();

        //! Do not override start() for Robot
        void start(){}

        //! Do not override start() for Robot
        void stop(){}

        private:
        Status status;
        bool noise, proximity, x_first;
        Battery battery;
        MapInfo *mp_info;

        //! Print the robot status, including: current position, charge station position, battery status and battery consume rate.
        void printStatus();
    };
}
#endif