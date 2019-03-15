#ifndef _INTRUDER_H
#define _INTRUDER_H

#include <iostream>
#include "elma/elma.h"
#include "mapinfo.h" 

using namespace elma;

class Intruder : public Process{
    public:
        //! Constructor with map information
        Intruder(MapInfo *mpinfo) : Process("Intruder") { 
            mp_info = mpinfo;
        }

        //! Do not override start() for intruder
        void init(){}

        //! Do not override start() for intruder
        void start(){}

        //! override start() for intruder
        void update(){
            //mp_info->setIntruderLocation(4,3); 
            if(mp_info->getIntruderPosition().first != -99)
                mp_info->cleanSymbol(mp_info->getIntruderPosition().first, mp_info->getIntruderPosition().second);
            int x,y;
            do{
                x = rand() % (mp_info->getMapSize()-1)/2;
                y = rand() % (mp_info->getMapSize()-1)/2;
            }while(!mp_info->setIntruderLocation(x,y));
        }
        void stop(){}

    private:
        MapInfo *mp_info;
};
#endif