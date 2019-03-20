#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Evade:: robot() { return (Robot&) state_machine(); }

void Evade::entry(const Event& e) {
    robot().setStatus(evading);
    robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate()*2);
}

void Evade::during(){
    if(robot().proximityDetection()){
        if(robot().batteryDetection())
            emit(Event("battery low"));
        else{
            robot().wandering(2);
            robot().getBattery()->consume();
        }
    }
    else
        emit(Event("reset"));
}

void Evade::exit(const Event& e){
    if(e.name() == "reset"){
        robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate()/2);
        robot().getBattery()->consume();
    }
    else robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate());
}
