#include <iostream>
#include "intruder.h"

using namespace elma;

void Intruder::init(){
    watch("intruder", [this](Event& e) {
        if(_running)
            _running = false;
        else
            _running = true;
    });
}
void Intruder::update(){
    if(_running){
        if(_mp_info.getIntruderPosition().first != -99)
            _mp_info.cleanSymbol(_mp_info.getIntruderPosition().first, _mp_info.getIntruderPosition().second);
        int x,y;
        do{
            x = rand() % (_mp_info.getMapSize()-1)/2;
            y = rand() % (_mp_info.getMapSize()-1)/2;
        }while(!_mp_info.setIntruderLocation(x,y));
    }
}