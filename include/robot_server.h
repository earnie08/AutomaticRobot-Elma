#ifndef _ROBOT_SERVER_H
#define _ROBOT_SERVER_H

#include <iostream>
#include "elma/elma.h"
#include "mapinfo.h"
#include "battery.h"
#include "json/json.h"
#include "httplib/httplib.h"

using namespace elma;
using namespace httplib;

namespace robot{
    class Robot_Server{
        public:

        Robot_Server(MapInfo *mpinfo, Battery *battery, Robot_Core *robotCore, Intruder *intruder){
            mp_info = mpinfo;
            this.battery = battery;
            this.robotCore = robotCore;
            this.intruder = intruder;
        }
        
        //! Open Server with get and post
        void Robot_Core::openPort(){
            Server svr;
            svr.Get(R"(/status)", [&](const Request& req, Response& res) {
                json result;
                result = { 
                    { "Robot Position",  mp_info->getRobotPosition() },
                    { "Intruder Position",  mp_info->getIntruderPosition() },
                    { "Charrge Station", mp_info->getChargeStation() },
                    { "Battery Status",  battery.getStatus() },
                    { "Battery Consume Rate", battery.getConsume() }
                };
                res.set_content(result.dump(), "json");
            });

            svr.Get(R"(/setting)", [&](const Request& req, Response& res) {
                json result;
                result = { 
                    { "Map Size",  (mp_info->getMapSize()-1)/2 },
                    { "Robot Initial Position",  mp_info->getRobotPosition() },
                    { "Charge Station", mp_info->getChargeStation() },
                    { "Battery Status",  battery.getStatus() },
                    { "Battery Consume Rate", battery.getConsume() }
                };
                res.set_content(result.dump(), "json");
            });

            svr.listen("0.0.0.0", 80);
        }

        private:
        MapInfo *mp_info;
        Battery *battery;
        Robot_Core *robotCoer;
        Intruder *intruder;
    };
    
}
#endif