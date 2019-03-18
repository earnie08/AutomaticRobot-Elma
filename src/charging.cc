#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Charging:: robot() { return (Robot&) state_machine(); }

void Charging::entry(const Event& e) {
    robot().setStatus(charge_battery);
    robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate()*2);
}

void Charging::during(){
    if(!robot().getBattery()->charge()){
        emit(Event("battery full"));
    }
}

void Charging::exit(const Event& e){
    robot().getMap()->setRobotLocation(robot().getMap()->getRobotPosition().first, robot().getMap()->getRobotPosition().second);
}