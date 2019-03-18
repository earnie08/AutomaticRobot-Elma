#ifndef _INTRUDER_H
#define _INTRUDER_H

#include <iostream>
#include "elma/elma.h"
#include "mapinfo.h" 

using namespace elma;

class Intruder : public Process{
    public:
        //! Constructor with map information
        Intruder(MapInfo& mpinfo) : Process("Intruder"), mp_info(mpinfo) {}

        //! Setting to watch event called "intruder". 
        void init();

        //! Do not override start() fmor intruder
        void start(){}

        //! Updating intruder's location. 
        //! The location is randomly on 2D array map.
        void update();

        //! Do not override stop() fmor intruder
        void stop(){}

    private:
        bool running = false;
        MapInfo& mp_info;
};
#endif