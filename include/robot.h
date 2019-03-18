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

        //! Costructor 
        Robot(MapInfo *mpinfo);
        bool batteryDetection();
        bool intruderDetection(int R_x, int R_y, int I_x, int I_y);
        bool proximityDetection(int R_x, int R_y, int I_x, int I_y);
        void wandering(int x, int y, int steps);

        vector<string> getStatus();
        void printStatus();



        inline void setStatus(Status status) { _status = status; }
        inline MapInfo* getMap() { return _map; }
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
    };
}
#endif