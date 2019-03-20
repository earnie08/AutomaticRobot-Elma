#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"

#include "off.h"
#include "wander.h"
#include "noise.h"
#include "evade.h"
#include "finding.h"
#include "charging.h"
#include "mapinfo.h"
#include "battery.h"
#include "robot_interface.h"

using namespace elma;
using namespace std;

//! \file
namespace robot{
    typedef enum {
        stop,
        running,
        making_noise,
        evading,
        finding_station,
        charge_battery
    } Status;

    class Robot : public StateMachine {
    public:

        //! Costructor with map information
        Robot(MapInfo *mpinfo);

        //! Costructor with robot name, map information, intruder area, proximity area
        //! \param name The name of robot
        //! \param mpinfo MapInfo class
        //! \param battery Battery class
        //! \param intruder intruder detection area
        //! \param proximity proximity detection area
        Robot(string name, MapInfo *mpinfo, Battery *battery, int intruder, int proximity);

        //! Setting all the transitions.
        void setTransitions();

        //! Checking whether battery can support robot go to charge station.
        //! Reserved 2 steps for robot avoiding it need to detour when it bumpping into an intruder on it's route back to charge station)
        //! \return True: battery can't support it. False: battery can support it keep running.
        bool batteryDetection();
        
        //! Detecting intruder's location.
        //! \return True: if it's in 4x4 area from robot's location. False: not in 2x2 area
        bool intruderDetection();
        
        //! Detecting whether intruder's location is too close to robot.
        //! \return True: if it's in 2x2 area from robot's location. False: not in 2x2 area
        bool proximityDetection();
        
        //! Wandering aronud the 2D map. Set the new robot x and y value with random direction.
        //! \param steps how many steps for wandering (default: 1 step, evade: 2 steps)
        void wandering(int steps);

        //! Putting information into a string vector which is going to use on robot interface
        //! \return string vector including robot position, robot status and battery status 
        vector<string> getStatus();

        //! Print map information on terminal, including 2D array map, robot position, charge station, battery, battery consume rate and status
        void printStatus();

        //! Setting robot status.
        //! \param status: stop / running / making_noise / evading / finding_station / charge_battery
        inline void setStatus(Status status) { _status = status; }
        
        //! Getting map information
        //! \return MapInfo: map information
        inline MapInfo* getMap() { return _map; }
        
        //! Getting bettery information
        //! \return Battery: battery information
        inline Battery* getBattery() { return &_battery; }

    private:
        Off off;
        Wander wander;
        Noise noise;
        Evade evade;
        Finding finding;
        Charging charging;

        Battery _battery;
        MapInfo *_map;
        Status _status = robot::stop;

        int _intruderArea = 4, _proximityArea = 2;
    };
}
#endif