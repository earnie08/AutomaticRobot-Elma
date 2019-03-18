#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Wander:: robot() { return (Robot&) state_machine(); }

void Wander::entry(const Event& e) {
    if(e.name() == "start/stop")
        emit(Event("intruder"));
    robot().setStatus(running);
}

void Wander::during() {
    if(robot().intruderDetection()){
        emit(Event("intruder detected"));
    }
    else{
        if(robot().batteryDetection()){
            emit(Event("battery low"));
        }
        else{
            robot().wandering(1);
        }
    }
}

void Wander::exit(const Event& e){
    if(e.name() == "intruder detected")
        robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate() / 2);
    if(e.name() == "start/stop"){
        emit(Event("intruder"));
        robot().setStatus(stop);
    }
}