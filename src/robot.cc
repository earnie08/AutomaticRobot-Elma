#include <iostream>
#include "robot.h"

using namespace elma;
using namespace robot;

Robot::Robot(MapInfo *mpinfo): StateMachine("Robot"), _map(mpinfo) {
    setTransitions();
}

Robot::Robot(string name, MapInfo *mpinfo, Battery *battery, int intruder, int proximity) : StateMachine(name), _map(mpinfo), _battery(*battery), _intruderArea(intruder), _proximityArea(proximity) {
    setTransitions();
}

void Robot::setTransitions(){
    set_initial(off);
    add_transition("start/stop", off, wander);
    add_transition("start/stop", wander, off);
    add_transition("intruder detected", wander, noise);
    add_transition("battery low", wander, finding);

    add_transition("proximity warning", noise, evade);
    add_transition("reset", noise, wander);
    add_transition("battery low", noise, finding);

    add_transition("reset", evade, noise);
    add_transition("battery low", evade, finding);

    add_transition("found charge station", finding, charging);

    add_transition("battery full", charging, wander);
}
bool Robot::batteryDetection(){
    int steps = abs(_map->getChargeStation().first - _map->getRobotPosition().first) + abs(_map->getChargeStation().second - _map->getRobotPosition().second);
    
    if((steps+2)*_battery.getConsume() >= _battery.getStatus() - _battery.getConsume())
        return true;
    else 
        return false;
}

bool Robot::intruderDetection(){
    int R_x = _map->getRobotPosition().first;
    int R_y = _map->getRobotPosition().second;
    int I_x = _map->getIntruderPosition().first;
    int I_y = _map->getIntruderPosition().second;

    if(abs(R_x - I_x) <= _intruderArea && abs(R_y - I_y) <= _intruderArea)
        return true;
    else
        return false;
}

bool Robot::proximityDetection(){
    int R_x = _map->getRobotPosition().first;
    int R_y = _map->getRobotPosition().second;
    int I_x = _map->getIntruderPosition().first;
    int I_y = _map->getIntruderPosition().second;

    if(abs(R_x - I_x) <= _proximityArea && abs(R_y - I_y) <= _proximityArea)
        return true;
    else
        return false;
}

void Robot::wandering(int steps){
    int x = _map->getRobotPosition().first;
    int y = _map->getRobotPosition().second;
    bool end = false;

    while(!end){
        int direction = rand() % 4 + 1;
        switch(direction){
            case 1:
                end = _map->setRobotLocation(x-steps, y);
                break;
            case 2:
                end = _map->setRobotLocation(x, y-steps);
                break;
            case 3:
                end = _map->setRobotLocation(x, y+steps);
                break;
            case 4:
                end = _map->setRobotLocation(x+steps, y);
                break;
        }
    }
    _map->cleanSymbol(x,y);
    _battery.consume();
}

vector<string> Robot::getStatus(){
    vector<string> v;
    string s = "";

    if(_status == charge_battery)
        s = "Robot Position: [" + to_string(_map->getChargeStation().first) + "," + to_string(_map->getChargeStation().second) + "]";
    else
        s = "Robot Position: [" + to_string(_map->getRobotPosition().first) + "," + to_string(_map->getRobotPosition().second) + "]";
    v.push_back(s);

    s = "Battery: " + to_string(_battery.getStatus());
    v.push_back(s);

    s = "Battery Consume Rate: " + to_string(_battery.getConsume());
    v.push_back(s);

    switch(_status){
        case 0:
            s = "Robot Status: Off";
            v.push_back(s);
            break;
        case 1:
            s = "Robot Status: Wandering";
            v.push_back(s);
            break;
        case 2:
            s = "Robot Status: Intruder Detected.";
            v.push_back(s);
            s = "Robot stop and  Making Noise!!!!";
            v.push_back(s);
            break;
        case 3:
            s = "Robot Status: Evading. Intruder Approaching!!!!";
            v.push_back(s);
            s = "Robot escaping: Speed up 2x times!";
            v.push_back(s);
            break;
        case 4:
            s = "Robot Status: Finding Charge Sation";
            v.push_back(s);
            break;
        case 5:
            s = "Robot Status: Charging";
            v.push_back(s);
            break;
    }
    return v;
}

void Robot::printStatus(){
    _map->printMap();
    cout << "Current Position: " << _map->getRobotPosition().first << "," << _map->getRobotPosition().second << "\n";
    cout << "Charge Station: " << _map->getChargeStation().first << "," << _map->getChargeStation().second << "\n";
    cout << "Battery: " << _battery.getStatus() << "\n";
    cout << "Battery Consume Rate: " << _battery.getConsume() << "\n";
    cout << "Status: " << _status << "\n\n";
}