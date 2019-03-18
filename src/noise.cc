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
    if(robot().intruderDetection()){
        if(robot().proximityDetection())
            emit(Event("proximity warning"));
        else{
            robot().getBattery()->consume();
            if(robot().batteryDetection())
                emit(Event("battery low"));
        }
    }
    else
        emit(Event("reset"));
} 

void Noise::exit(const Event& e) {
    if(e.name() != "proximity warning")
        robot().getBattery()->setConsume(robot().getBattery()->getConsumeRate());
    else robot().getBattery()->consume();
}