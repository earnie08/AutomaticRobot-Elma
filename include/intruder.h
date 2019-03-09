#ifndef _INTRUDER_H
#define _INTRUDER_H

#include <iostream>
#include "elma.h"
#include "mapinfo.h" 

using namespace elma;

class Intruder : public Process{
    public:
        Intruder(MapInfo *mpinfo) : Process("Intruder") { 
            mp_info = mpinfo;
            mp_info.setIntruderLocation(1,3);
            mpinfo.printMap();
        }

        void init(){}
        void start(){}
        void update(){
            auto mp = mp_info.getMap();
            int x,y;
            do{
                x = rand() % (mp_info.getMapSize()-1)/2;
                y = rand() % (mp_info.getMapSize()-1)/2;
            }while(!mp_info.setIntruderLocation(x,y));
        }
        void stop(){}

    private:
        MapInfo *mp_info;
};
#endif