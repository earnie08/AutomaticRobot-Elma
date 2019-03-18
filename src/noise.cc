#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot&Noise:: robot() { return (Robot&) state_machine(); }

void Noise::entry(const Event& e) {
    robot().setStatus(making_noise);
    robot().getBattery()->consume();
}
void Noise::during() {
    int R_x = robot().getMap()->getRobotPosition().first;
    int R_y = robot().getMap()->getRobotPosition().second;
    int I_x = robot().getMap()->getIntruderPosition().first;
    int I_y = robot().getMap()->getIntruderPosition().second;
    
    if(robot().intruderDetection(R_x, R_y, I_x, I_y)){
        if(robot().proximityDetection(R_x, R_y, I_x, I_y))
            emit(Event("proximity warning"));
        else{
            robot().getBattery()->consume();
            if(robot().batteryDetection())
                emit(Event("battery low"));
        }
    }
    else{
        emit(Event("reset"));
    }
} 

void Noise::exit(const Event& e) {
    if(e.name() != "proximity warning"){
        robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate());
    }
    else robot().getBattery()->consume();
}