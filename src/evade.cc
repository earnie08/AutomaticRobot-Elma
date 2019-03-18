#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Evade:: robot() { return (Robot&) state_machine(); }

void Evade::entry(const Event& e) {
    robot().setStatus(evading);
    cout << "Evading Enter\n";
}

void Evade::during(){
    int R_x = robot().getMap()->getRobotPosition().first;
    int R_y = robot().getMap()->getRobotPosition().second;
    int I_x = robot().getMap()->getIntruderPosition().first;
    int I_y = robot().getMap()->getIntruderPosition().second;

    if(robot().proximityDetection(R_x, R_y, I_x, I_y)){
        if(robot().batteryDetection()){
            emit(Event("battery low"));
        }
        else{
            robot().wandering(R_x, R_y, 2);
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
