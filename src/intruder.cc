#include <iostream>
#include "intruder.h"

using namespace elma;

void Intruder::init(){
    watch("intruder", [this](Event& e) {
        if(running)
            running = false;
        else
            running = true;
    });
}
void Intruder::update(){
    if(running){
        if(mp_info.getIntruderPosition().first != -99)
            mp_info.cleanSymbol(mp_info.getIntruderPosition().first, mp_info.getIntruderPosition().second);
        int x,y;
        do{
            x = rand() % (mp_info.getMapSize()-1)/2;
            y = rand() % (mp_info.getMapSize()-1)/2;
        }while(!mp_info.setIntruderLocation(x,y));
    }
}