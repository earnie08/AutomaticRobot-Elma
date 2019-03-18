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
    int R_x = robot().getMap()->getRobotPosition().first;
    int R_y = robot().getMap()->getRobotPosition().second;
    int I_x = robot().getMap()->getIntruderPosition().first;
    int I_y = robot().getMap()->getIntruderPosition().second;
    
    if(robot().intruderDetection(R_x, R_y, I_x, I_y)){
        emit(Event("intruder detected"));
    }
    else{
        if(robot().batteryDetection()){
            emit(Event("battery low"));
        }
        else{
            robot().wandering(R_x, R_y, 1);
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